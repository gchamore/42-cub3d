/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookops <tookops@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:37:13 by anferre           #+#    #+#             */
/*   Updated: 2024/08/25 22:52:15 by tookops          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_distance(float x0, float y0, float x1, float y1)
{
	return (sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
}

void	ft_cast_rays(t_cub *cub)
{
	int r;
	int mx;
	int my;
	int dof;
	float rx;
	float ry;
	float xo;
	float yo;
	float dist_h;
	float dist_v;
	float x_h;
	float y_h;
	float x_v;
	float y_v;
	
	dist_h = 10000000;
	dist_v = 10000000;
	float player_pos_x = (cub->player->x_cur * cub->player->minimap_scale) + (cub->player->minimap_scale / 2);
    float player_pos_y = (cub->player->y_cur * cub->player->minimap_scale) + (cub->player->minimap_scale / 2);
	r = 0;
	float aTan = -1 / tan(cub->player->angle);
	float nTan = -tan(cub->player->angle);
	while (r < 1)
	{
		x_h = player_pos_x;
		y_h = player_pos_y;
		//horizontal lines
		dof = 0;
		if (cub->player->angle > PI + TOL) //looking down
		{
			ry = (floor(player_pos_y / cub->player->minimap_scale) * cub->player->minimap_scale) - 0.0001; //offset to the top of the grid line
			rx = (player_pos_y - ry) * aTan + player_pos_x;
			yo = -cub->player->minimap_scale;
			xo = -yo * aTan;
		}
		else if (cub->player->angle < PI - TOL) //looking up
		{
			ry = (floor(player_pos_y / cub->player->minimap_scale) * cub->player->minimap_scale) + cub->player->minimap_scale + 0.0001; //offset to the bottom of the grid line
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
			if (mx >= 0 && (size_t)mx < cub->parse->map_width && my >= 0 && (size_t)my < cub->parse->map_height && cub->map[my][mx].value == '1')
			{
				x_h = rx;
				y_h = ry;
				dist_h = ft_distance(player_pos_x, player_pos_y, x_h, y_h);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			} 
			// printf("Step %d: rx = %f, ry = %f, mx = %d, my = %d\n", dof, rx, ry, mx, my);
		}
		
		//vertical lines
		dof = 0;
		x_v = player_pos_x;
		y_v = player_pos_y;
		if (cub->player->angle > SOUTH_ANGLE + TOL && cub->player->angle < NORTH_ANGLE - TOL) //looking left
		{
			rx = (floor(player_pos_x / cub->player->minimap_scale) * cub->player->minimap_scale) - 0.0001; //offset to the top of the grid line
			ry = (player_pos_x - rx) * nTan + player_pos_y;
			xo = -cub->player->minimap_scale;
			yo = -xo * nTan;
		}
		else if (cub->player->angle < SOUTH_ANGLE - TOL || cub->player->angle > NORTH_ANGLE + TOL) //looking right
		{
			rx = (floor(player_pos_x / cub->player->minimap_scale) * cub->player->minimap_scale) + cub->player->minimap_scale + 0.0001; //offset to the bottom of the grid line
			ry = (player_pos_x - rx) * nTan + player_pos_y;
			xo = cub->player->minimap_scale;
			yo = -xo * nTan;
		}
		else //looking straight up or down
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
			if (mx >= 0 && (size_t)mx < cub->parse->map_width && my >= 0 && (size_t)my < cub->parse->map_height && cub->map[my][mx].value == '1')
			{
				x_v = rx;
				y_v = ry;
				dist_v = ft_distance(player_pos_x, player_pos_y, x_v, y_v);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			} 
			// printf("Step %d: angle %f rx = %f, ry = %f, mx = %d, my = %d\n", dof, cub->player->angle, rx, ry, mx, my);
		}
		r++;
		if (dist_v < dist_h)
		{
			rx = x_v;
			ry = y_v;
		}
		if (dist_h < dist_v)
		{
			rx = x_h;
			ry = y_h;
		}
	ft_draw_line(&cub->data->img, player_pos_x, player_pos_y, rx, ry, BLUE_COLOR);
	}
	// printf("scale = %f\n", cub->player->minimap_scale);
	// printf("atan = %f\n", aTan);
	// printf("curr x = %f, y = %f \n", cub->player->x_cur, cub->player->y_cur);
	// printf ("angle = %f \n", cub->player->angle);
	// printf("starting: x = %f, y = %f, Final values: rx = %f, ry = %f\n", player_pos_x, player_pos_y, rx, ry);
}

