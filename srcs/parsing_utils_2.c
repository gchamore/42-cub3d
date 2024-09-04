/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:03 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 09:50:12 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Retourne 1 si c est un delimiteur, 0 sinon
int	ft_is_delimiter(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

// PERMET DE RECUPERER LES COULEURS RGB DANS C ET F
int	ft_extract_and_trim_value(char *str, int start, int end)
{
	char	*temp;
	int		value;
	char	*trimmed;

	temp = ft_strndup(str + start, end - start + 1);
	if (!temp)
		return (-1);
	trimmed = ft_strtrim(temp, " \t");
	free(temp);
	if (!trimmed || ft_strcmp(trimmed, "\n") == 0 || ft_strcmp(trimmed, "") == 0)
	{
		free(trimmed);
		return (-1);
	}
	value = ft_atoi(trimmed);
	free(trimmed);
	return (value);
}

void	ft_assign_rgb_value(t_rgb *rgb, int value_index, int value)
{
	if (value_index == 0)
		rgb->r = value;
	else if (value_index == 1)
		rgb->g = value;
	else if (value_index == 2)
		rgb->b = value;
}

t_rgb	ft_get_rgb(t_rgb rgb, char *str, int i, int start)
{
	int	value_index;
	int	value;
	int	end;

	value_index = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == ',' && str[i + 1] != '\0') || str[i + 1] == '\0')
		{
			if (str[i + 1] == '\0' && str[i] != ',')
				end = i;
			else
				end = i - 1;
			value = ft_extract_and_trim_value(str, start, end);
			if (value == -1)
				return (rgb);
			ft_assign_rgb_value(&rgb, value_index, value);
			value_index++;
			start = i + 1;
		}
		i++;
	}
	return (rgb);
}
// t_rgb	ft_get_rgb(t_rgb rgb, char *str)
// {
//     int i;
// 	int	start;
// 	int value_index;
//     char *tmp;
// 	char *temp;
// 	int j;
// 	int value;
// 	char *trimmed;

//     i = 0;
// 	tmp = str;
//     start = 0;
//     value_index = 0;
//     while (tmp[i] != '\0')
//     {
//         if ((tmp[i] == ',' && tmp[i + 1] != '\0') || tmp[i + 1] == '\0')
//         {
//             temp = malloc(i - start + 2);
// 			if (!temp)
// 				return (rgb);
//             j = 0;
//             while (start < i)
//             {
//                 temp[j++] = tmp[start++];
// 			}
// 			if (tmp[i + 1] == '\0' && tmp[i] != ',')
// 				temp[j++] = tmp[i];
// 			temp[j] = '\0';
// 			start = i + 1;
// 			trimmed = ft_strtrim(temp, " \t");
// 			if (ft_strcmp(trimmed, "\n") == 0 || ft_strcmp(trimmed, "") == 0)
// 				return (free(trimmed), free(temp), rgb);
// 			value = atoi(trimmed);
// 			free(trimmed);
// 			if (value_index == 0)
// 				rgb.r = value;
// 			else if (value_index == 1)
// 				rgb.g = value;
// 			else if (value_index == 2)
// 				rgb.b = value;
//             value_index++;
// 			free(temp);
//         }
//         i++;
//     }
// 	return (rgb);
// }
