/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:37:13 by anferre           #+#    #+#             */
/*   Updated: 2024/08/22 15:31:51 by anferre          ###   ########.fr       */
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
	while (r < 1)
	{
		//horizontal lines
		dof = 0;
		float aTan = -1 / tan(cub->player->angle);
		if (cub->player->angle > PI) //looking down
		{
			ry = (((int)player_pos_y / cub->player->minimap_scale) * cub->player->minimap_scale) - 0.0001;
			rx = (player_pos_y - ry) * aTan + player_pos_x;
			yo = -cub->player->minimap_scale;
			xo = -yo * aTan;
		}
		else if (cub->player->angle < PI) //looking up
		{
			ry = (((int)player_pos_y / cub->player->minimap_scale) * cub->player->minimap_scale) + cub->player->minimap_scale; 
			rx = (player_pos_y - ry) * aTan + player_pos_x;
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
			mp = my* cub->parse->map_width + mx; //need to check if width and height are switched x / y 
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
	// ry += cub->player->minimap_scale / 2;
	printf("curr x = %f, y = %f \n", cub->player->x_cur, cub->player->y_cur);
	printf ("angle = %f \n", cub->player->angle);
	// float player_size = PLAYER_SIZE * cub->player->minimap_scale;
	printf("starting: x = %f, y = %f, Final values: rx = %f, ry = %f\n", player_pos_x, player_pos_y, rx, ry);
	ft_draw_line(&cub->data->img, player_pos_x, player_pos_y, rx, ry, BLUE_COLOR);
}

