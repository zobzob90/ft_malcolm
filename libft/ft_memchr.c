/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:34:28 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/12 14:54:24 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*pointeur;

	i = 0;
	pointeur = (unsigned char *)ptr;
	while (i < num)
	{
		if (pointeur[i] == (unsigned char)value)
			return ((void *)&pointeur[i]);
		i++;
	}
	return (NULL);
}

/*
int main()
{
	const char str[] = "Hello World";
	char *result = ft_memchr(str, 'W', 13);
	if(result != NULL)
	{
		printf("%c : caractere trouvee\n", *result);
		printf("%p : a l'adresse\n", result);
	}
}
*/