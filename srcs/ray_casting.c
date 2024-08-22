/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:37:13 by anferre           #+#    #+#             */
/*   Updated: 2024/08/22 14:47:17 by anferre          ###   ########.fr       */
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
	float ra;
	float xo;
	float yo;

	ra = cub->player->angle;
	r = 0;
	while (r < 1)
	{
		//horizontal lines
		dof = 0;
		float aTan = -1 / tan(ra);
		if (ra > PI) //looking down
		{
			ry = (((int)cub->player->y_cur / cub->player->minimap_scale) * cub->player->minimap_scale) - 0.0001;
			rx = (cub->player->y_cur - ry) * aTan + cub->player->x_cur;
			yo = -cub->player->minimap_scale;
			xo = -yo * aTan;
		}
		else if (ra < PI) //looking up
		{
			ry = (((int)cub->player->y_cur / cub->player->minimap_scale) * cub->player->minimap_scale) + cub->player->minimap_scale; 
			rx = (cub->player->y_cur - ry) * aTan + cub->player->x_cur;
			yo = cub->player->minimap_scale;
			xo = -yo * aTan;
		}
		else //looking straight left or right
		{
			rx = cub->player->x_cur;
			ry = cub->player->y_cur;
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
	printf("curr x = %f, y = %f \n", cub->player->x_cur, cub->player->y_cur);
	printf ("angle = %f \n", ra);
	// float player_size = PLAYER_SIZE * cub->player->minimap_scale;
	float player_pos_x = (cub->player->y_cur * cub->player->minimap_scale) + (cub->player->minimap_scale / 2);
    float player_pos_y = (cub->player->x_cur * cub->player->minimap_scale) + (cub->player->minimap_scale / 2);
	printf("starting: x = %f, y = %f, Final values: rx = %f, ry = %f\n", player_pos_x, player_pos_y, rx, ry);
	ft_draw_line(&cub->data->img, cub->player->x_cur, cub->player->y_cur, rx, ry, BLUE_COLOR);
}

