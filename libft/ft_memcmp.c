/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:01:13 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/08 12:04:42 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr, const	void *ptr2, size_t num)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)ptr;
	p2 = (unsigned char *)ptr2;
	while (i < num)
	{
		if (p1[i] < p2[i])
			return (-1);
		else if (p1[i] > p2[i])
			return (1);
		i++;
	}
	return (0);
}

/*
int main()
{
    char str1[] = "hello";
    char str2[] = "hella";

    int result = ft_memcmp(str1, str2, 5); // Comparer les 5 premiers octets
    if (result == 0) {
        printf("Les deux blocs de mémoire sont égaux.\n");
    } else if (result < 0) {
        printf("Le premier bloc de mémoire est inférieur au second.\n");
    } else {
        printf("Le premier bloc de mémoire est supérieur au second.\n");
    }

    return 0;
}
*/
