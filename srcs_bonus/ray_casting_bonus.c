/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:37:13 by anferre           #+#    #+#             */
/*   Updated: 2024/09/06 11:38:56 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_horizontal_casting(t_cub *cub, t_raycasting *ray, \
t_draw_wall *draw_wall)
{
	ray->dof = 0;
	ray->dist_h = 1000;
	ray->dist_f = 0;
	ray->atan = -1 / tan(ray->ra);
	if (ray->ra > PI + TOL)
	{
		ray->ry = floor(ray->player_y) - 0.0001;
		ray->rx = (ray->player_y - ray->ry) * ray->atan + ray->player_x;
		ray->yo = -1;
		ray->xo = -ray->yo * ray->atan;
	}
	else if (ray->ra < PI - TOL)
	{
		ray->ry = floor(ray->player_y) + 1.0;
		ray->rx = (ray->player_y - ray->ry) * ray->atan + ray->player_x;
		ray->yo = 1;
		ray->xo = -ray->yo * ray->atan;
	}
	else
		ft_angle_ew(ray, draw_wall);
	ft_ray_path_hor(cub, ray);
}

void	ft_vertical_casting(t_cub *cub, t_raycasting *ray, \
t_draw_wall *draw_wall)
{
	ray->dof = 0;
	ray->dist_v = 1000;
	ray->x_v = ray->player_x;
	ray->y_v = ray->player_y;
	ray->ntan = -tan(ray->ra);
	if (ray->ra > SOUTH_ANGLE + TOL && ray->ra < NORTH_ANGLE - TOL)
	{
		ray->rx = floor(ray->player_x) - 0.0001;
		ray->ry = (ray->player_x - ray->rx) * ray->ntan + ray->player_y;
		ray->xo = -1;
		ray->yo = -ray->xo * ray->ntan;
	}
	else if (ray->ra < SOUTH_ANGLE - TOL || ray->ra > NORTH_ANGLE + TOL)
	{
		ray->rx = floor(ray->player_x) + 1.0;
		ray->ry = (ray->player_x - ray->rx) * ray->ntan + ray->player_y;
		ray->xo = 1;
		ray->yo = -ray->xo * ray->ntan;
	}
	else
		ft_angle_ns(ray, draw_wall);
	ft_ray_path_ver(cub, ray);
}

void	ft_dist_v_smaller(t_raycasting	*ray, t_draw_wall *draw_wall, \
t_cub *cub)
{
	ray->rx = ray->x_v;
	ray->ry = ray->y_v;
	if (ray->ra > PI / 2 && ray->ra < 3 * PI / 2)
		draw_wall->dir = WEST;
	else
		draw_wall->dir = EAST;
	ray->dist_f = ray->dist_v;
	ray->wall_hit_x = fmod(ray->ry, 1.0f);
	cub->player->last_dist = ray->dist_f;
}

// get the shortest distance and the direction of the wall hit
void	ft_dir_dist(t_raycasting *ray, t_draw_wall *draw_wall, t_cub *cub)
{
	if (ft_is_intersection(ray))
		ray->dist_f = cub->player->last_dist;
	else if (ray->dist_v <= ray->dist_h)
		ft_dist_v_smaller(ray, draw_wall, cub);
	else
	{
		ray->rx = ray->x_h;
		ray->ry = ray->y_h;
		if (ray->ra > WEST_ANGLE)
			draw_wall->dir = NORTH;
		else
			draw_wall->dir = SOUTH;
		ray->dist_f = ray->dist_h;
		ray->wall_hit_x = fmod(ray->rx, 1.0f);
		cub->player->last_dist = ray->dist_f;
	}
	if (isnan(ray->wall_hit_x))
		ray->wall_hit_x = 0.0f;
	ray->wall_hit_x -= floor(ray->wall_hit_x);
}

void	ft_cast_rays(t_cub *cub)
{
	int				r;

	r = 0;
	if (cub->parse->map_height > cub->parse->map_width)
		cub->ray->max_dof = cub->parse->map_height + 1;
	else
		cub->ray->max_dof = cub->parse->map_width + 1;
	cub->ray->ra = cub->player->angle - RAD * 30;
	ft_check_limits(&(cub->ray->ra));
	cub->ray->player_x = cub->player->x_cur + 0.5;
	cub->ray->player_y = cub->player->y_cur + 0.5;
	while (r < WIN_WIDTH)
	{
		ft_horizontal_casting(cub, cub->ray, cub->draw_wall);
		ft_vertical_casting(cub, cub->ray, cub->draw_wall);
		ft_dir_dist(cub->ray, cub->draw_wall, cub);
		ft_calculate_tex_dist(cub, cub->ray, cub->draw_wall);
		ft_draw_wall(cub, r, cub->draw_wall);
		cub->ray->ra += cub->ray->ray_step;
		ft_check_limits(&cub->ray->ra);
		r++;
	}
}
