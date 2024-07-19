/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:20:35 by gchamore          #+#    #+#             */
/*   Updated: 2024/07/19 14:45:45 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_create_cub(t_cub **cub)
{
    *cub = malloc(sizeof(t_cub));
    if (*cub)
    {
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
	cub->parse->NO = NULL;
	cub->parse->SO = NULL;
	cub->parse->WE = NULL;
	cub->parse->EA = NULL;
	cub->parse->map_height = 0;
	cub->parse->map_width = 0;
	cub->parse->total_height = 0;
	cub->parse->total_newline = 0;
	cub->parse->total_infos = 0;
	cub->parse->ct = 0;
	cub->parse->F.b = 0;
	cub->parse->F.g = 0;
	cub->parse->F.r = 0;
	cub->parse->C.b = 0;
	cub->parse->C.g = 0;
	cub->parse->C.r = 0;
}