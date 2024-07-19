/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:03 by gchamore          #+#    #+#             */
/*   Updated: 2024/07/19 18:42:57 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Retourne 1 si c est un delimiteur, 0 sinon
int	ft_is_delimiter(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

// PERMET DE RECUPERER LES COULEURS RGB DANS C ET F
t_rgb	ft_get_rgb(t_rgb rgb, char *str)
{
    int i;
	int	start;
	int valueIndex;
    char *tmp;
	char *temp;
	int j;
	int value;
	char *trimmed;

    i = 0;
	tmp = str;
    start = 0;
    valueIndex = 0;
    while (tmp[i] != '\0')
    {
        if (tmp[i] == ',' || tmp[i + 1] == '\0')
        {
            temp = malloc(i - start + 2);
			if (!temp)
				return (rgb);
            j = 0;
            while (start < i)
            {
                temp[j++] = tmp[start++];
			}
			if (tmp[i + 1] == '\0' && tmp[i] != ',')
				temp[j++] = tmp[i];
			temp[j] = '\0';
			start = i + 1;
			trimmed = ft_strtrim(temp, " \t");
			value = atoi(trimmed);
			free(trimmed);
			if (valueIndex == 0)
				rgb.r = value;
			else if (valueIndex == 1)
				rgb.g = value;
			else if (valueIndex == 2)
				rgb.b = value;
            valueIndex++;
			free(temp);
        }
        i++;
    }
	return (rgb);
}