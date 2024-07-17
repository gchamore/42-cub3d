/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:37 by gchamore          #+#    #+#             */
/*   Updated: 2024/07/17 18:44:13 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_mod_split(char *str)
{
    int		i;
    char	**split;
    size_t	len;

	i = 0;
    len = ft_strlen(str);
    split = (char **)malloc(sizeof(char *) * (len + 1));
    if (!split)
        return (NULL);
    while (i < (int)len)
    {
        split[i] = (char *)malloc(sizeof(char) * 2);
        if (!split[i])
        {
            while (i-- > 0)
                free(split[i]);
            free(split);
            return (NULL);
        }
        split[i][0] = str[i];
        split[i][1] = '\0';
		i++;
    }
    split[len] = NULL;
    return (split);
}

void	*ft_verif_str(char **split, char *str)
{
	int	row;
	int	collum;

	row = 0;
	while (*str)
	{
		collum = 0;
		split[row] = (char *)malloc(sizeof(char) * (ft_one_word_len(str) + 1));
		if (!split[row])
			return (NULL);
		while (*str && !ft_is_delimiter(*str))
		{
			split[row][collum] = *str;
			str++;
			collum++;
		}
		while (*str && ft_is_delimiter(*str))
			str++;
		split[row][collum] = '\0';
		row++;
	}
	split[row] = NULL;
	return (split);
}
