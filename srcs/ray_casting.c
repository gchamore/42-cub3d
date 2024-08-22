/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:37:13 by anferre           #+#    #+#             */
/*   Updated: 2024/08/22 16:22:48 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_cast_rays(t_cub *cub)
{
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	float rx;
	float ry;
	float xo;
	float yo;

	float player_pos_x = (cub->player->x_cur * cub->player->minimap_scale) + (cub->player->minimap_scale / 2);
    float player_pos_y = (cub->player->y_cur * cub->player->minimap_scale) + (cub->player->minimap_scale / 2);
	r = 0;
	float dist_next_line;
	while (r < 1)
	{
		//horizontal lines
		dof = 0;
		float aTan = -1 / tan(cub->player->angle);
		if (cub->player->angle > PI) //looking down
		{
			dist_next_line = cub->player->minimap_scale - fmod(player_pos_y, cub->player->minimap_scale);
			// ry = ((player_pos_y / cub->player->minimap_scale) * cub->player->minimap_scale) - 0.0001;
			ry = player_pos_y + dist_next_line - 0.0001;
			rx = (ry - player_pos_y) * aTan + player_pos_x;
			yo = -cub->player->minimap_scale;
			xo = -yo * aTan;
		}
		else if (cub->player->angle < PI) //looking up
		{
			dist_next_line = fmod(player_pos_y, cub->player->minimap_scale);
			// ry = ((player_pos_y / cub->player->minimap_scale) * cub->player->minimap_scale) + cub->player->minimap_scale - 0.0001; 
			ry = player_pos_y - dist_next_line - 0.0001;
			rx = (ry - player_pos_y) * aTan + player_pos_x;
			yo = cub->player->minimap_scale;
			xo = -yo * aTan;
		}
		else //looking straight left or right
		{
			rx = player_pos_x;
			ry = player_pos_y;
			dof = 8;
		}
        // printf("Initial values: rx = %f, ry = %f, xo = %f, yo = %f\n", rx, ry, xo, yo);
		while (dof < 8)
		{
			mx = (int)(rx) / cub->player->minimap_scale;
			my = (int)(ry) / cub->player->minimap_scale;
			mp = my* cub->parse->map_width + mx;
			if ((size_t)mx < cub->parse->map_width && (size_t)my < cub->parse->map_height &&  mx >= 0 && my >= 0 && cub->map[my][mx].value == '1')
			{
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			} 
		}
		r++;
	}
	printf("dist_next_line = %f\n", dist_next_line);
	printf("curr x = %f, y = %f \n", cub->player->x_cur, cub->player->y_cur);
	printf ("angle = %f \n", cub->player->angle);
	printf("starting: x = %f, y = %f, Final values: rx = %f, ry = %f\n", player_pos_x, player_pos_y, rx, ry);
	ft_draw_line(&cub->data->img, player_pos_x, player_pos_y, rx, ry, BLUE_COLOR);
}

