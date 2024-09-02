/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:24:45 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/02 08:43:21 by anferre          ###   ########.fr       */
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
			free(map[i]);
			map[i] = NULL;
			i++;
		}
		free(map);
		map = NULL;
	}
}

void	ft_free_pointer(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_parse(t_cub *cub)
{
	if (cub->parse->NO)
		ft_free_pointer((void **)&cub->parse->NO);
	if (cub->parse->SO)
		ft_free_pointer((void **)&cub->parse->SO);
	if (cub->parse->WE)
		ft_free_pointer((void **)&cub->parse->WE);
	if (cub->parse->EA)
		ft_free_pointer((void **)&cub->parse->EA);
	ft_free_pointer((void **)&cub->parse);
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
			ft_free_pointer((void **)&cub->data);
		if (cub->player)
			ft_free_pointer((void **)&cub->player);
		if (cub->parse)
			ft_free_parse(cub);
		if (cub->texture)
			ft_free_pointer((void **)&cub->texture);
		if (cub->ray)
			ft_free_pointer((void **)&cub->ray);
		if (cub->draw_wall)
			ft_free_pointer((void **)&cub->draw_wall);
		ft_free_pointer((void **)&cub);
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
