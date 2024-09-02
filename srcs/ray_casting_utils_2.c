/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:42:30 by tookops           #+#    #+#             */
/*   Updated: 2024/09/02 06:37:26 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_ray_path_hor(t_cub *cub, t_raycasting *ray)
{
	while (ray->dof < ray->max_dof)
	{
		ray->mx = (int)(ray->rx);
		ray->my = (int)(ray->ry);
		if (ray->mx >= 0 && (size_t)ray->mx < cub->parse->map_width && \
		ray->my >= 0 && (size_t)ray->my < cub->parse->map_height && \
		cub->map[ray->my][ray->mx].value == '1')
		{
			ray->x_h = ray->rx;
			ray->y_h = ray->ry;
			ray->dist_h = ft_distance(ray->player_x, ray->player_y, ray->x_h, \
			ray->y_h);
			ray->dof = ray->max_dof;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

void	ft_angle_ew(t_raycasting *ray, t_draw_wall *draw_wall)
{
	if (fabs(ray->ra) < TOL || fabs(ray->ra - 2 * PI) < TOL)
	{
		ray->ry = ray->player_y;
		ray->rx = floor(ray->player_x) + 1.0;
		ray->dist_f = (ray->rx - ray->player_x) / fabs(cos(ray->ra));
		ray->wall_hit_x = fmod(ray->ry, 1.0f);
		draw_wall->dir = EAST;
		ray->dof = ray->max_dof;
	}
	else if (fabs(ray->ra - PI) < TOL)
	{
		ray->ry = ray->player_y;
		ray->rx = floor(ray->player_x);
		ray->dist_f = (ray->rx - ray->player_x) / fabs(cos(ray->ra));
		ray->wall_hit_x = fmod(ray->ry, 1.0f);
		draw_wall->dir = WEST;
		ray->dof = ray->max_dof;
	}
}

void	ft_ray_path_ver(t_cub *cub, t_raycasting *ray)
{
	while (ray->dof < ray->max_dof)
	{
		ray->mx = (int)(ray->rx);
		ray->my = (int)(ray->ry);
		if (ray->mx >= 0 && (size_t)ray->mx < cub->parse->map_width && \
		ray->my >= 0 && (size_t)ray->my < cub->parse->map_height && \
		cub->map[ray->my][ray->mx].value == '1')
		{
			ray->x_v = ray->rx;
			ray->y_v = ray->ry;
			ray->dist_v = ft_distance(ray->player_x, ray->player_y, \
			ray->x_v, ray->y_v);
			ray->dof = ray->max_dof;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

//NORTH and SOUTH
void	ft_angle_ns(t_raycasting *ray, t_draw_wall *draw_wall)
{
	if (fabs(ray->ra - PI / 2) < TOL)
	{
		ray->rx = ray->player_x;
		ray->ry = floor(ray->player_y);
		ray->dist_f = (ray->player_y - ray->ry) / fabs(sin(ray->ra));
		draw_wall->dir = NORTH;
		ray->wall_hit_x = fmod(ray->rx, 1.0f);
		ray->dof = ray->max_dof;
	}
	else if (fabs(ray->ra - 3 * PI / 2) < TOL)
	{
		ray->rx = ray->player_x;
		ray->ry = floor(ray->player_y) + 1.0;
		ray->dist_f = (ray->player_y - ray->ry) / fabs(sin(ray->ra));
		draw_wall->dir = SOUTH;
		ray->wall_hit_x = fmod(ray->rx, 1.0f);
		ray->dof = ray->max_dof;
	}
}
