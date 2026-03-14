/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:16:37 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/05 12:39:51 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	size_t			i;
	unsigned char	*pointeur;

	i = 0;
	pointeur = (unsigned char *)ptr;
	while (i < len)
	{
		pointeur[i] = (unsigned char) value;
		i++;
	}
	return (pointeur);
}

/*
int main()
{
	int i = 0;
	char buff[5];
	ft_memset(buff, '1', 5);
	while(i < sizeof(buff))
	{
		printf("%c\n", buff[i++]);
	}
	return (0);
}
*/