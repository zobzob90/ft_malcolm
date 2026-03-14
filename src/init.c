/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 10:49:13 by eric              #+#    #+#             */
/*   Updated: 2026/03/14 10:54:57 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

t_entry *add_entry(t_entry **table, uint8_t *ip, uint8_t *mac)
{
	t_entry *new;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	ft_memcpy(new->ip, ip, 4);
	ft_memcpy(new->mac, mac, 6);
	new->next = *table;
	*table = new;
	return (new);
}
