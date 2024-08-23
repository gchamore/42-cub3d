/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:24:45 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/23 13:26:38 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map(t_cell **map, int map_height)
{
	int	i;

	i = 0;
	if (map && map_height > 0)
	{
		while (i < map_height)
		{
			if (map[i])
			{
				free(map[i]);
				map[i] = NULL;
			}
			i++;
		}
		free(map);
		map = NULL;
	}
}

void	ft_free_cub(t_cub *cub)
{
	if (cub)
	{
		if (cub->map)
		{
			ft_free_map(cub->map, cub->parse->map_height);
			cub->map = NULL;
		}
		if (cub->data)
		{
			free(cub->data);
			cub->data = NULL;
		}
		if (cub->player)
		{
			free(cub->player);
			cub->player = NULL;
		}
		if (cub->parse)
		{
			if (cub->parse->NO)
			{
				free(cub->parse->NO);
				cub->parse->NO = NULL;
			}
			if (cub->parse->SO)
			{
				free(cub->parse->SO);
				cub->parse->SO = NULL;
			}
			if (cub->parse->WE)
			{
				free(cub->parse->WE);
				cub->parse->WE = NULL;
			}
			if (cub->parse->EA)
			{
				free(cub->parse->EA);
				cub->parse->EA = NULL;
			}
			free(cub->parse);
			cub->parse = NULL;
		}
		free(cub);
		cub = NULL;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i] != NULL)
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}