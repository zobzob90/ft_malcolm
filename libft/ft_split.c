/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:43:57 by ertrigna          #+#    #+#             */
/*   Updated: 2024/11/12 16:26:52 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int		cw;
	size_t	i;

	cw = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			cw++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (cw);
}

static void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	ft_fill_tab(char *tab, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
}

static void	ft_setmem(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	compt;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			compt = 0;
			while (s[i + compt] && s[i + compt] != c)
				compt++;
			tab[j] = malloc(sizeof(char) * (compt + 1));
			if (!tab[j])
				return (ft_free_tab(tab));
			ft_fill_tab(tab[j], s + i, c);
			j++;
			i += compt;
		}
	}
	tab[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		cw;
	char	**tab;

	if (!s)
		return (NULL);
	cw = ft_count_words(s, c);
	tab = malloc(sizeof(char *) * (cw + 1));
	if (!tab)
		return (NULL);
	ft_setmem(tab, s, c);
	return (tab);
}

/*
int main(void)
{
	char *str = "ceci est un test pour split";
	int i = 0;
	char **tab = ft_split(str, ' ');

	while (tab && tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	ft_free_tab(tab);
	return (0);
}
*/