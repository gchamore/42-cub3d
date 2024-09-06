/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:24:45 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/06 11:26:38 by anferre          ###   ########.fr       */
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
	if (cub->parse->no)
		ft_free_pointer((void **)&cub->parse->no);
	if (cub->parse->so)
		ft_free_pointer((void **)&cub->parse->so);
	if (cub->parse->we)
		ft_free_pointer((void **)&cub->parse->we);
	if (cub->parse->ea)
		ft_free_pointer((void **)&cub->parse->ea);
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
		close(cub->fd);
		ft_free_pointer((void **)&cub);
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split && split[i])
	{
		while (split[i] != NULL)
		{
			free(split[i]);
			split[i] = NULL;
			i++;
		}
		free(split);
		split = NULL;
	}
}
