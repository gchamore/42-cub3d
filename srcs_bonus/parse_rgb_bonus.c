/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:03 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 15:50:18 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// PERMET DE RECUPERER LES COULEURS RGB DANS C ET F

char	*ft_verify_rgb(char *str)
{
	int		i;
	char	*trimmed;

	trimmed = ft_strtrim(str, " \t\n");
	if (!trimmed)
		return (NULL);
	free(str);
	if (trimmed[0] == '\0')
		return (free(trimmed), NULL);
	i = 0;
	while (trimmed[i])
	{
		if (trimmed[i] < '0' || trimmed[i] > '9' || ft_is_delimiter(trimmed[i]))
			return (free(trimmed), NULL);
		i++;
	}
	if (ft_strlen(trimmed) > 4)
		return (free(trimmed), NULL);
	return (trimmed);
}

t_rgb	ft_get_rgb(t_rgb rgb, char *str)
{
	char	**split;
	char	*temp;
	char	*temp2;
	char	*temp3;

	split = ft_split(str, ',');
	if (!split)
		return (rgb);
	if (!split[0] ||!split[1] || !split[2] || split[3])
		return (ft_free_split(split), rgb);
	temp = ft_verify_rgb(split[0]);
	temp2 = ft_verify_rgb(split[1]);
	temp3 = ft_verify_rgb(split[2]);
	if (!temp || !temp2 || !temp3)
		return (free(temp), free(temp2), free(temp3), free(split), rgb);
	rgb.r = ft_atoi(temp);
	rgb.g = ft_atoi(temp2);
	rgb.b = ft_atoi(temp3);
	return (free(temp), free(temp2), free(temp3), free(split), rgb);
}
