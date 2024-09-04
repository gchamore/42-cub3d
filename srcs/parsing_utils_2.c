/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:03 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 13:24:42 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Retourne 1 si c est un delimiteur, 0 sinon
int	ft_is_delimiter(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

// PERMET DE RECUPERER LES COULEURS RGB DANS C ET F
int	ft_extract_value(char *str, int start, int end)
{
    char *temp;
    int temp_index = 0;
    int new_value;
	int i;

    i = start;
    temp = (char *)malloc((end - start + 2) * sizeof(char));
    if (!temp)
        return (-1);
    while (i <= end)
    {
        if (!ft_is_delimiter(str[i]))
        {
            temp[temp_index] = str[i];
            temp_index++;
        }
		i++;
    }
    temp[temp_index] = '\0';
    new_value = ft_atoi(temp);
    free(temp);
    return (new_value);
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

int	ft_get_start(char *str, int i, int start)
{
	if (start == -1)
	{
		if (str[i] >= '0' && str[i] <= '9')
			start = i;
	}
	return (start);
}

int ft_get_end(char *str, int i, int start)
{
	int end;

	end = -1;
	if (start != -1)
	{
		if (str[i + 1] == '\0' || str[i + 1] == ',' || str[i + 1] == '\n')
			end = i;
	}
	return (end);
}

int	ft_extract(char *str, int start, int end)
{
	int value;

	value = 0;
	if (start != -1 && end != -1)
	{
		value = ft_extract_value(str, start, end);
		if (value == -1)
			ft_error(NULL, "Invalid RGB building", -1, -1);
	}
	return (value);
}

t_rgb	ft_get_rgb(t_rgb rgb, char *str, int i, int value_index)
{
	int	value;
	int start;
	int end;

	start = -1;
	end = -1;
	while (value_index <= 2)
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ',' && !ft_is_delimiter(str[i]) && str[i] != '\0')
			ft_error(NULL, "Invalid RGB building", -1, -1);
		else if ((str[i] >= '0' && str[i] <= '9') || ft_is_delimiter(str[i]))
		{
			start = ft_get_start(str, i, start);
			end = ft_get_end(str, i, start);
			value = ft_extract(str, start, end);
			if (start != -1 && end != -1)
				i = end;
		}
		else if (str[i] == ',' || str[i] == '\0' || str[i] == '\n')
		{
			ft_assign_rgb_value(&rgb, value_index, value);
			start = -1;
			end = -1;
			value_index++;
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
