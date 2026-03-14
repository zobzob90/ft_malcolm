/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:43:56 by eric              #+#    #+#             */
/*   Updated: 2026/03/14 17:35:35 by eric             ###   ########.fr       */
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
		
	}
	freeifaddrs(ifaddr);
	return (0);
}
