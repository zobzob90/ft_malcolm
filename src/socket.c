/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:43:56 by eric              #+#    #+#             */
/*   Updated: 2026/03/15 10:39:37 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malcolm.h>

// Recuperer l'adresse IP et MAC d'une interface reseau locale
// Prend en param, le nom de l'interface, un tableau pour stocker l'adresse IP et MAC

int	get_interface_info(const char *ifname, uint8_t *ip, uint8_t *mac)
{
	struct ifaddrs *ifaddr;
	struct ifaddrs *ifa;

	if (getifaddrs(&ifaddr) == -1)
		return (-1);
	ifa = ifaddr;
	while (ifa)
	{
		if (!ifa->ifa_addr || ft_strcmp(ifa->ifa_name, ifname) != 0)
			continue;
		if (ifa->ifa_addr->sa_family == AF_INET && ip)
		{
			struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
			ft_memcpy(ip, &sa->sin_addr, 4);
		}
		if (ifa->ifa_addr->sa_family == AF_PACKET && mac)
		{
			struct sockaddr_ll *s = (struct sockaddr_ll *)ifa->ifa_addr;
			ft_memcpy(mac, s->sll_addr, 6);
		}
		ifa = ifa->ifa_next;
	}
	freeifaddrs(ifaddr);
	return (0);
}

int	set_promiscuous_mode(int sockfd, const char *ifname)
{
	struct ifreq	ifr;
	
	ft_memset(&ifr, 0, sizeof(struct ifreq));
	ft_strlcpy(ifr.ifr_name, ifname, IFNAMSIZ);

	if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) == -1)
	{
		fprint(stderr, "ioctl SIOCGIFFLAGS failed\n");
		return (-1);
	}
	ifr.ifr_flags |= IFF_PROMISC;

	if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) == -1)
	{
		fprintf(stderr, "ioctl SIOCSIFFLAGS failed\n");
		return (-1);
	}
	return (0);
}

int	create_socket(const char *ifname)
{
	int	sockfd;

	sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sockfd < 0)
	{
		fprintf(stderr, "Error in socket creation\n");
		return (-1);
	}
	if (set_promiscuous_mode(sockfd, ifname) < 0)
	{
		fprintf(stderr, "Error in promiscuous mode\n");
		close (sockfd);
		return (-1);
	}
	return (sockfd);
}

ssize_t	receive_packet(int sockfd, void *buffer, size_t buflen)
{
	return (recvfrom(sockfd, buffer, buflen, 0, NULL, NULL));
}

void	sniffing(int sockfd)
{
	ssize_t len;
	uint8_t	buffer[BUFFER_SIZE];
	while (1)
	{
		len = receive_packet(sockfd, buffer, BUFFER_SIZE);
		if (len < 0)
		{
			fprintf(stderr, "Error in packet reception\n");
			break ;
		}
		if ((ssize_t)len < sizeof(t_ethernet))
			continue;
		t_ethernet *eth = (t_ethernet *)buffer;
		if (ntohs(eth->type) == 0x0806)
		{
			if ((ssize_t)len >= sizeof(t_ethernet) + sizeof(t_arp))
			{
				t_arp *arp = (t_arp *)(buffer + sizeof(t_ethernet));
				print_arp(arp);
			}
		}
	}
}
