/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:20:35 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/20 13:22:28 by gchamore         ###   ########.fr       */
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
    }
}

void	ft_init_structs(t_cub *cub)
{
	cub->map = NULL;
	cub->player->x_start = 0;
	cub->player->y_start = 0;
	cub->player->x_cur = 0;
	cub->player->y_cur = 0;
	cub->parse->NO = NULL;
	cub->parse->SO = NULL;
	cub->parse->WE = NULL;
	cub->parse->EA = NULL;
	cub->parse->map_height = 0;
	cub->parse->map_width = 0;
	cub->parse->total_height = 0;
	cub->parse->total_newline = 0;
	cub->parse->total_infos = 0;
	cub->parse->check_newline = 0;
	cub->parse->ct = 0;
	cub->parse->F.b = -1;
	cub->parse->F.g = -1;
	cub->parse->F.r = -1;
	cub->parse->C.b = -1;
	cub->parse->C.g = -1;
	cub->parse->C.r = -1;
	cub->player->dir = 0;
}