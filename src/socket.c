/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:43:56 by eric              #+#    #+#             */
/*   Updated: 2026/03/19 10:35:05 by eric             ###   ########.fr       */
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
		{
			ifa = ifa->ifa_next;
			continue;	
		}
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

int	find_interface(char ifname[IFNAMSIZ], uint8_t ip[4], uint8_t mac[6])
{
	struct ifaddrs *ifaddr;
	struct ifaddrs *ifa;

	if (getifaddrs(&ifaddr) == -1)
		return (-1);
	ifa = ifaddr;
	for (ifa = ifaddr; ifa; ifa = ifa->ifa_next)
	{
		if (!ifa->ifa_addr)
			continue;
		if (ifa->ifa_addr->sa_family != AF_INET)
            continue;
		if (!(ifa->ifa_flags & IFF_UP))
            continue;
        if (ifa->ifa_flags & IFF_LOOPBACK)
            continue;
        if (ifa->ifa_flags & IFF_NOARP)
            continue;
		
		ft_strlcpy(ifname, ifa->ifa_name, IFNAMSIZ);
		if (get_interface_info(ifname, ip, mac) == 0)
		{
			freeifaddrs(ifaddr);
			return (0);
		}	
	}
	freeifaddrs(ifaddr);
	return (-1);
}

int	set_promiscuous_mode(int sockfd, const char *ifname)
{
	struct ifreq	ifr;
	
	ft_memset(&ifr, 0, sizeof(struct ifreq));
	ft_strlcpy(ifr.ifr_name, ifname, IFNAMSIZ);

	if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) == -1)
	{
		fprintf(stderr, "ioctl SIOCGIFFLAGS failed\n");
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

int	is_arp_duplicated(t_entry *entry, uint8_t *ip, uint8_t *mac)
{
	uint8_t	zero_mac[6] = {0, 0, 0, 0, 0, 0};
	while (entry)
	{
		if (ft_memcmp(entry->ip, ip, 4) == 0)
		{
			// Ignorer les MAC vide (premiere detection)
			if (ft_memcmp(entry->mac, zero_mac, 6) == 0)
			{
				ft_memcpy(entry->mac, mac, 6);
				return (0);
			}
			if (ft_memcmp(entry->mac, mac, 6) != 0)
			{
				printf("\n⚠️  ARP SPOOFING DETECTED!\n");
				printf("	IP: ");
				print_ip(ip);
				printf(" changed MAC\n");
				printf("	Old MAC: ");
				print_mac(entry->mac);
				printf("\n	New MAC: ");
				print_mac(mac);
				printf("\n\n");
				ft_memcpy(entry->mac, mac, 6);
				return (1);
			}
			return (0);		// -> pas de changement
		}
		entry = entry->next;
	}
	return (0);	// -> premiere fois qu'on voit l'IP
}

void	sniffing(int sockfd)
{
	ssize_t 						len;
	uint8_t							buffer[BUFFER_SIZE];	
	t_entry							*arp_table;				// stocke les entree ARP dans t_entry
	
	extern volatile sig_atomic_t	g_signal;
	arp_table = NULL;
	
	while (!g_signal)
	{
		len = receive_packet(sockfd, buffer, BUFFER_SIZE);
		if (len < 0)
		{
			fprintf(stderr, "Error in packet reception\n");
			break ;
		}
		if ((size_t)len < sizeof(t_ethernet))
			continue;
		t_ethernet *eth = (t_ethernet *)buffer;
		if (ntohs(eth->type) == 0x0806)
		{
			if ((size_t)len >= sizeof(t_ethernet) + sizeof(t_arp))
			{
				t_arp *arp = (t_arp *)(buffer + sizeof(t_ethernet));
				print_arp(arp);
				if (!is_arp_duplicated(arp_table, arp->sender_ip, arp->sender_mac))
					arp_table = add_entry(&arp_table, arp->sender_ip, arp->sender_mac);
			}
		}
	}
	free_entry(arp_table);
}

ssize_t	send_arp_packet(int sockfd, const char *ifname, t_entry *sender, t_entry *target, uint16_t opcode)
{
	uint8_t				packet[sizeof(t_ethernet) + sizeof(t_arp)];
	t_ethernet			*eth;
	t_arp				*arp;
	struct sockaddr_ll	addr;
	int					ifindex;

	eth = (t_ethernet *)packet;
	ft_memcpy(eth->src_mac, sender->mac, 6);
	ft_memcpy(eth->dst_mac, target->mac, 6);
	eth->type = htons(0x0806);

	arp = (t_arp *)(packet + sizeof(t_ethernet));
	arp->htype = htons(1);
	arp->ptype = htons(0x0800);
	arp->hlen = 6;
	arp->plen = 4;
	arp->opcode = htons(opcode);
	ft_memcpy(arp->sender_mac, sender->mac, 6);
	ft_memcpy(arp->sender_ip, sender->ip, 4);
	ft_memcpy(arp->target_mac, target->mac, 6);
	ft_memcpy(arp->target_ip, target->ip, 4);

	ifindex = if_nametoindex(ifname);
	if (ifindex == 0)
		return (-1);
	ft_memset(&addr, 0, sizeof(addr));
	addr.sll_family = AF_PACKET;
	addr.sll_ifindex = ifindex;
	addr.sll_halen = 6;
	ft_memcpy(addr.sll_addr, target->mac, 6);
	
	return (sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&addr, sizeof(addr)));
}
