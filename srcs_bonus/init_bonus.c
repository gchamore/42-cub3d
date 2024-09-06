/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:20:35 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/06 12:12:33 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_create_cub(t_cub **cub)
{
	*cub = malloc(sizeof(t_cub));
	if (*cub)
	{
		(*cub)->player = malloc(sizeof(t_player));
		if (!(*cub)->player)
		{
			ft_free_cub(*cub);
			return ;
		}
		(*cub)->parse = malloc(sizeof(t_parse));
		if (!(*cub)->parse)
		{
			ft_free_cub(*cub);
			return ;
		}
		(*cub)->data = malloc(sizeof(t_data));
		if (!(*cub)->data)
		{
			ft_free_cub(*cub);
			return ;
		}
		(*cub)->texture = NULL;
		(*cub)->ray = NULL;
		(*cub)->draw_wall = NULL;
	}
}

void	ft_init_structs(t_cub *cub)
{
	cub->map = NULL;
	cub->i = 0;
	cub->fd = -1;
	cub->player->y_start = 0;
	cub->player->x_start = 0;
	cub->player->y_cur = 0;
	cub->player->x_cur = 0;
	cub->parse->map_height = 0;
	cub->parse->map_width = 0;
	cub->parse->tmp_height = 0;
	cub->parse->tmp_width = 0;
	cub->parse->total_height = 0;
	cub->parse->total_newline = 0;
	cub->parse->total_infos = 0;
	cub->parse->check_newline = 0;
	cub->parse->ct = 0;
	ft_init_info(cub);
}

void	ft_init_info(t_cub *cub)
{
	cub->parse->no = NULL;
	cub->parse->so = NULL;
	cub->parse->we = NULL;
	cub->parse->ea = NULL;
	cub->parse->f.b = -1;
	cub->parse->f.g = -1;
	cub->parse->f.r = -1;
	cub->parse->c.b = -1;
	cub->parse->c.g = -1;
	cub->parse->c.r = -1;
	cub->verif.no = 0;
	cub->verif.so = 0;
	cub->verif.we = 0;
	cub->verif.ea = 0;
	cub->verif.f = 0;
	cub->verif.c = 0;
	cub->player->dir = 0;
}

void	ft_init_map(t_cub *cub, size_t y, size_t x, char val)
{
	cub->map[y][x].value = val;
	cub->map[y][x].used = false;
	cub->map[y][x].count = 0;
	cub->map[y][x].count_0 = 0;
}

void	ft_init_cub_map(t_cub *cub)
{
	size_t	i;

	i = 0;
	cub->map = malloc(sizeof(t_cell *) * (cub->parse->map_height + 1));
	if (!cub->map)
		ft_error(cub, "Map Alloc failed", -1, -1);
	while (i <= cub->parse->map_height)
	{
		cub->map[i] = NULL;
		i++;
	}
}
