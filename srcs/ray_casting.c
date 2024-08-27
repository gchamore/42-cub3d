/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookops <tookops@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:37:13 by anferre           #+#    #+#             */
/*   Updated: 2024/08/26 02:55:49 by tookops          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_distance(float x0, float y0, float x1, float y1)
{
	return (sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
}
void	ft_draw_wall(t_img *img, int x, int line_height, int color)
{
	int y_start;
	int y_end;
	int i;

	i = 0;
	y_start = (WIN_HEIGTH / 2) - (line_height / 2);
	y_end = (WIN_HEIGTH / 2) + (line_height / 2);
	if (y_start < 0)
		y_start = 0;
	if (y_end >= WIN_HEIGTH)
		y_end = WIN_HEIGTH - 1;
	while (y_start < y_end)
	{
		while (i < 25)
		{
			ft_mpp(img, x + i, y_start, color);
			i++;
		}
		i = 0;
		y_start++;
	}
}

void	ft_cast_rays(t_cub *cub)
{
	int r;
	int mx;
	int my;
	int dof;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
	float dist_h;
	float dist_v;
	float dist_f;
	float x_h;
	float y_h;
	float x_v;
	float y_v;
	
	r = 0;
	ra = cub->player->angle - RAD * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	float player_pos_x = (cub->player->x_cur * cub->player->minimap_scale) + (cub->player->minimap_scale / 2);
    float player_pos_y = (cub->player->y_cur * cub->player->minimap_scale) + (cub->player->minimap_scale / 2);
	while (r < 60 )
	{
		//horizontal lines
		dof = 0;
		dist_h = 10000000;
		x_h = player_pos_x;
		y_h = player_pos_y;
		float aTan = -1 / tan(ra);
		if (ra > PI + TOL) //looking down
		{
			ry = (floor(player_pos_y / cub->player->minimap_scale) * cub->player->minimap_scale) - 0.0001; //offset to the top of the grid line
			rx = (player_pos_y - ry) * aTan + player_pos_x;
			yo = -cub->player->minimap_scale;
			xo = -yo * aTan;
		}
		else if (ra < PI - TOL) //looking up
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
		dist_v = 10000000;
		x_v = player_pos_x;
		y_v = player_pos_y;
		float nTan = -tan(ra);
		if (ra > SOUTH_ANGLE + TOL && ra < NORTH_ANGLE - TOL) //looking left
		{
			rx = (floor(player_pos_x / cub->player->minimap_scale) * cub->player->minimap_scale) - 0.0001; //offset to the top of the grid line
			ry = (player_pos_x - rx) * nTan + player_pos_y;
			xo = -cub->player->minimap_scale;
			yo = -xo * nTan;
		}
		else if (ra < SOUTH_ANGLE - TOL || ra > NORTH_ANGLE + TOL) //looking right
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
		if (dist_v < dist_h)
		{
			rx = x_v;
			ry = y_v;
			dist_f = dist_v;
		}
		if (dist_h < dist_v)
		{
			rx = x_h;
			ry = y_h;
			dist_f = dist_h;
		}
		// ft_draw_line(&cub->data->img, player_pos_x, player_pos_y, rx, ry, BLUE_COLOR);
		// draw 3D walls
		float ca = cub->player->angle - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		dist_f = dist_f * cos(ca);
		float line_height = (WIN_HEIGTH / dist_f) * 15;
		float line_offset = (WIN_HEIGTH / 2) - line_height / 2;
		ft_draw_wall(&cub->data->img, r * 25, line_height + line_offset , BLUE_COLOR);
		ra += RAD;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		r++;
	} 
	// printf("scale = %f\n", cub->player->minimap_scale);
	// printf("atan = %f\n", aTan);
	// printf("curr x = %f, y = %f \n", cub->player->x_cur, cub->player->y_cur);
	// printf ("angle = %f \n", cub->player->angle);
	// printf("starting: x = %f, y = %f, Final values: rx = %f, ry = %f\n", player_pos_x, player_pos_y, rx, ry);
}

