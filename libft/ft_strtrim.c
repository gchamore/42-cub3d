/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:10:49 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/06 11:49:05 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_checkstarttrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	found;

	i = 0;
	j = 0;
	found = 1;
	while (s1[i] && found == 1)
	{
		j = 0;
		found = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				found = 1;
				i++;
				break ;
			}
			j++;
		}
	}
	return (i);
}

unsigned int	ft_checkendtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	found;

	i = ft_strlen(s1) - 1;
	j = 0;
	found = 1;
	while (s1[i] && found == 1)
	{
		j = 0;
		found = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				found = 1;
				i--;
				break ;
			}
			j++;
		}
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	starttrim;
	unsigned int	endtrim;
	unsigned int	i;
	char			*str;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set || set[i] == '\0')
		return (ft_strdup((char *)s1));
	starttrim = ft_checkstarttrim(s1, set);
	if (!(starttrim < ft_strlen(s1)))
		return (ft_strdup(""));
	endtrim = ft_checkendtrim(s1, set);
	str = (char *)malloc((endtrim - starttrim + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (starttrim < endtrim)
	{
		str[i] = s1[starttrim];
		i++;
		starttrim++;
	}
	str[i] = '\0';
	return (str);
}
//  returns an allocated copy of’s1’ with the characters specified
//  in ’set’ removed from the beginning and the end of the string
//if (!(starttrim < ft_strlen(s1))) means we only found set char in *s1

//	La fonction ft_strtrim prend une chaîne de caractères
//	s1 et supprime les caractères spécifiés dans l'ensemble
//	set du début et de la fin de la chaîne.
//	La fonction renvoie une nouvelle chaîne de caractères
//	résultante, avec les caractères indésirables supprimés.

// #include <stdio.h>
// #include <string.h>

// int main() 
// {
//     const char *s1 = "abcd";
//     const char *set = "";
//     char *str;

// 	str = ft_strtrim(s1, set);
//     printf("Chaîne originale: '%s'\n", s1);
//     printf("Chaîne après trim: '%s'\n", str);

//     free(str);

//     return 0;
// }