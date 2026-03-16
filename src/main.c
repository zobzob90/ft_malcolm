/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:36:59 by eric              #+#    #+#             */
/*   Updated: 2026/03/16 12:55:59 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

int main(int ac, char *av[])
{
	t_entry src;
	t_entry dest;
	int		sockfd;
	char	ifname[IFNAMSIZ];
	uint8_t	if_ip[4];
	uint8_t	if_mac[6];
	
	if (parse_args(ac, av, &src, &dest) != 0)
		return (1);
	if (find_interface(ifname, if_ip, if_mac) < 0)
	{
		fprintf(stderr, "Could not find a suitable network interface\n");
		return (1);
	}
	printf("Using interface: %s\n", ifname);
	sockfd = create_socket(ifname);
	if (sockfd < 0)
		return (1);
	sniffing(sockfd);
	close (sockfd);
	return (0);
}
