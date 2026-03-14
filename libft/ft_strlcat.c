/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:08:58 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/07 09:21:36 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dest;
	size_t	len_src;

	if (!dest && size == 0)
		return (0);
	i = 0;
	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (len_dest < size -1 && size > 0)
	{
		while (src[i] && (len_dest + i) < (size - 1))
		{
			dest[len_dest + i] = src[i];
			i++;
		}
		dest[len_dest + i] = '\0';
	}
	if (size <= len_dest)
		len_dest = size;
	return (len_src + len_dest);
}

/*
int main()
{
	const char *src = "\n";
	char dest[20] = "\t";
	printf("%zu\n", ft_strlcat(dest, src, 15));
	printf("%s\n", dest);
}
*/