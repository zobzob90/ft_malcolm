/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:36:59 by eric              #+#    #+#             */
/*   Updated: 2026/03/15 11:03:02 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

int main(int ac, char *av[])
{
	if (ac < 5)
	{
		printf ("Wrong number of arguments\n");
		printf ("Usage: ./ft_malcom [ip] [mac adress] [target ip] [target mac adress]");
		return (1);
	}
	
}
