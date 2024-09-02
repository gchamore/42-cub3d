/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:38:32 by tookops           #+#    #+#             */
/*   Updated: 2024/09/02 08:40:38 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_distance(float x0, float y0, float x1, float y1)
{
	return (sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
}

int	ft_rgb_to_int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

void	ft_check_limits(float *ra)
{
	if (*ra < 0)
		*ra += 2 * PI;
	if (*ra > 2 * PI)
		*ra -= 2 * PI;
}

void	ft_init_raycasting(t_cub **cub, t_raycasting *ray)
{
	ray = malloc(sizeof(t_raycasting));
	if (!ray)
		return ;
	if ((*cub)->parse->map_height > (*cub)->parse->map_width)
		ray->max_dof = (*cub)->parse->map_height + 1;
	else
		ray->max_dof = (*cub)->parse->map_width + 1;
	ray->rx = 0.0f;
	ray->ry = 0.0f;
	ray->ra = (*cub)->player->angle - RAD * 30;
	ft_check_limits(&(ray->ra));
	ray->xo = 0.0f;
	ray->yo = 0.0f;
	ray->dist_f = 0.0f;
	ray->x_v = 0.0f;
	ray->y_v = 0.0f;
	ray->player_x = (*cub)->player->x_cur + 0.5;
	ray->player_y = (*cub)->player->y_cur + 0.5;
	ray->x_h = ray->player_x;
	ray->y_h = ray->player_y;
	ray->aspect_ratio = (float)WIN_HEIGTH / (float)WIN_WIDTH;
	ray->ray_step = (60.0 * RAD) / WIN_WIDTH;
	ray->wall_hit_x = 0.0f;
	ray->ca = 0.0f;
	(*cub)->ray = ray;
}

void	ft_init_structs_raycasting(t_cub **cub)
{
	t_raycasting	*ray;
	t_draw_wall		*draw_wall;

	ray = NULL;
	ft_init_raycasting(cub, ray);
	draw_wall = malloc(sizeof(t_draw_wall));
	if (!draw_wall)
		return ;
	draw_wall->y_start = 0;
	draw_wall->y_end = 0;
	draw_wall->y = 0;
	draw_wall->tex_y = 0;
	draw_wall->color = 0;
	draw_wall->step = 0.0f;
	draw_wall->tex_pos = 0.0f;
	(*cub)->draw_wall = draw_wall;
}
