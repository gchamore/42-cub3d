/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookops <tookops@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:37:13 by anferre           #+#    #+#             */
/*   Updated: 2024/08/31 04:38:32 by tookops          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_distance(float x0, float y0, float x1, float y1)
{
	return (sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
}

int ft_rgb_to_int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}
void ft_draw_wall(t_cub *cub, int x, t_draw_wall *draw_wall)
{
    int y_start;
    int y_end;
	int y;
    int tex_y;
    int color;
    float step;
    float tex_pos;

	y = 0;
    y_start = (WIN_HEIGTH / 2) - (draw_wall->line_height / 2);
    y_end = (WIN_HEIGTH / 2) + (draw_wall->line_height / 2);
    if (y_start < 0)
        y_start = 0;
    if (y_end >= WIN_HEIGTH)
        y_end = WIN_HEIGTH - 1;
    step = 1.0 * cub->texture->height[draw_wall->dir] / draw_wall->line_height;
    tex_pos = (y_start - WIN_HEIGTH / 2 + draw_wall->line_height / 2) * step;
   	while (y < WIN_HEIGTH && y < y_end)
    {
		if (y <= y_start) // ceiling
			ft_mpp(&cub->data->img, x, y, ft_rgb_to_int(cub->parse->C));
		else if (y > y_start && y < y_end)
		{
        tex_y = (int)tex_pos % cub->texture->height[draw_wall->dir];
		tex_pos += step;
		color = *(int *)(cub->texture->addr[draw_wall->dir] + (tex_y * cub->texture->line_len[draw_wall->dir] + draw_wall->tex_x * (cub->texture->bpp[draw_wall->dir] / 8)));
		ft_mpp(&cub->data->img, x, y_start, color);
		y_start++;
		}
		else if ( y >= y_end) // floor
			ft_mpp(&cub->data->img, x, y, ft_rgb_to_int(cub->parse->F));
		y++;
    }
	y = y_end;
	while (y < WIN_HEIGTH)
	{
		ft_mpp(&cub->data->img, x, y, ft_rgb_to_int(cub->parse->F));
		y++;
	}
}
void	ft_check_limits(float *ra)
{
	if (*ra < 0)
		*ra += 2 * PI;
	if (*ra > 2 * PI)
		*ra -= 2 * PI;
}
void	ft_init_raycasting(t_cub *cub, t_raycasting **ray)
{
	*ray = malloc(sizeof(t_raycasting));
	if (!ray)
		return ;
	(*ray)->mx = 0;
	(*ray)->my = 0;
	(*ray)->dof = 0;
	if (cub->parse->map_height > cub->parse->map_width)
		(*ray)->max_dof = cub->parse->map_height + 1;
	else
		(*ray)->max_dof = cub->parse->map_width + 1;
	(*ray)->rx = 0.0f;
	(*ray)->ry = 0.0f;
	(*ray)->ra = cub->player->angle - RAD * 30;
	ft_check_limits(&((*ray)->ra));
	(*ray)->xo = 0.0f;
	(*ray)->yo = 0.0f;
	(*ray)->dist_h = 1000;
	(*ray)->dist_v = 1000;
	(*ray)->dist_f = 0.0f;
	(*ray)->x_v = 0.0f;
	(*ray)->y_v = 0.0f;
	(*ray)->player_x = cub->player->x_cur + 0.5;
	(*ray)->player_y = cub->player->y_cur + 0.5;
	(*ray)->x_h = (*ray)->player_x;
	(*ray)->y_h = (*ray)->player_y;
	(*ray)->aspect_ratio = (float)WIN_HEIGTH / (float)WIN_WIDTH;
	(*ray)->ray_step = (60.0 * RAD) / WIN_WIDTH;
	(*ray)->wall_hit_x = 0.0f;
	(*ray)->aTan = 0.0f;
	(*ray)->ca = 0.0f;
}

void	ft_init_structs_raycasting(t_raycasting **ray, t_draw_wall **draw_wall, t_cub *cub)
{
	ft_init_raycasting(cub, ray);
	*draw_wall = malloc(sizeof(t_draw_wall));
	if (!*draw_wall)
		return ;
	(*draw_wall)->y_start = 0;
	(*draw_wall)->y_end = 0;
	(*draw_wall)->y = 0;
	(*draw_wall)->tex_y = 0;
	(*draw_wall)->color = 0;
	(*draw_wall)->step = 0.0f;
	(*draw_wall)->tex_pos = 0.0f;
}

void	ft_horizontal_casting(t_cub *cub, t_raycasting *ray, t_draw_wall *draw_wall)
{
	// horizontal lines
		ray->dof = 0;
		ray->dist_h = 1000;
		ray->dist_f = 0;
		float aTan = -1 / tan(ray->ra);
		if (ray->ra > PI + TOL) // looking down
		{
			ray->ry = floor(ray->player_y) - 0.0001; // offset to the top of the grid line
			ray->rx = (ray->player_y - ray->ry) * aTan + ray->player_x;
			ray->yo = -1;
			ray->xo = -ray->yo * aTan;
		}
		else if (ray->ra < PI - TOL) // looking up
		{
			ray->ry = floor(ray->player_y) + 1.0; // offset to the bottom of the grid line
			ray->rx = (ray->player_y - ray->ry) * aTan + ray->player_x;
			ray->yo = 1;
			ray->xo = -ray->yo * aTan;
		}
		else if (fabs(ray->ra) < TOL || fabs(ray->ra - 2 * PI) < TOL) // East
		{
			ray->ry = ray->player_y;
			ray->rx = floor(ray->player_x) + 1.0;
			ray->dist_f = (ray->rx - ray->player_x) / fabs(cos(ray->ra));
			ray->wall_hit_x = fmod(ray->ry, 1.0f);
			draw_wall->dir = EAST;
			ray->dof = ray->max_dof;
		}
		else if (fabs(ray->ra - PI) < TOL) // West
		{
			ray->ry = ray->player_y;
			ray->rx = floor(ray->player_x);
			ray->dist_f = (ray->rx - ray->player_x) / fabs(cos(ray->ra));
			ray->wall_hit_x = fmod(ray->ry, 1.0f);
			draw_wall->dir = WEST;
			ray->dof = ray->max_dof;
		}
		while (ray->dof < ray->max_dof)
		{
			ray->mx = (int)(ray->rx);
			ray->my = (int)(ray->ry);
			if (ray->mx >= 0 && (size_t)ray->mx < cub->parse->map_width && ray->my >= 0 && (size_t)ray->my < cub->parse->map_height && cub->map[ray->my][ray->mx].value == '1')
			{
				ray->x_h = ray->rx;
				ray->y_h = ray->ry;
				ray->dist_h = ft_distance(ray->player_x, ray->player_y, ray->x_h, ray->y_h);
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

void	ft_vertical_casting(t_cub *cub, t_raycasting *ray, t_draw_wall *draw_wall)
{
	// vertical lines
		ray->dof = 0;
		ray->dist_v = 1000;
		ray->x_v = ray->player_x;
		ray->y_v = ray->player_y;
		float nTan = -tan(ray->ra);
		if (ray->ra > SOUTH_ANGLE + TOL  && ray->ra < NORTH_ANGLE - TOL) // looking left
		{
			ray->rx = floor(ray->player_x) - 0.0001; // offset to the top of the grid line
			ray->ry = (ray->player_x - ray->rx) * nTan + ray->player_y;
			ray->xo = -1;
			ray->yo = -ray->xo * nTan;
		}
		else if (ray->ra < SOUTH_ANGLE - TOL || ray->ra > NORTH_ANGLE + TOL) // looking right
		{
			ray->rx = floor(ray->player_x) + 1.0; // offset to the bottom of the grid line
			ray->ry = (ray->player_x - ray->rx) * nTan + ray->player_y;
			ray->xo = 1;
			ray->yo = -ray->xo * nTan;
		}
		else if (fabs(ray->ra - PI / 2) < TOL) // North
		{
			ray->rx = ray->player_x;
			ray->ry = floor(ray->player_y);
			ray->dist_f = (ray->player_y - ray->ry) / fabs(sin(ray->ra));
			draw_wall->dir = NORTH;
			ray->wall_hit_x = fmod(ray->rx, 1.0f);
			ray->dof = ray->max_dof;
		}
		else if (fabs(ray->ra - 3 * PI / 2) < TOL) // South
		{
			ray->rx = ray->player_x;
			ray->ry = floor(ray->player_y) + 1.0;
			ray->dist_f = (ray->player_y - ray->ry) / fabs(sin(ray->ra));
			draw_wall->dir = SOUTH;
			ray->wall_hit_x = fmod(ray->rx, 1.0f);
			ray->dof = ray->max_dof;
		}
		while (ray->dof < ray->max_dof)
		{
			ray->mx = (int)(ray->rx);
			ray->my = (int)(ray->ry);
			if (ray->mx >= 0 && (size_t)ray->mx < cub->parse->map_width &&ray->my >= 0 && (size_t)ray->my < cub->parse->map_height && cub->map[ray->my][ray->mx].value == '1')
			{
				ray->x_v = ray->rx;
				ray->y_v = ray->ry;
				ray->dist_v = ft_distance(ray->player_x, ray->player_y, ray->x_v, ray->y_v);
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

void	ft_dir_dist(t_raycasting *ray, t_draw_wall *draw_wall )
{
	if (ray->dist_v < ray->dist_h) // vertical hit E W
		{
			ray->rx = ray->x_v;
			ray->ry = ray->y_v;
			if (ray->ra > SOUTH_ANGLE || ray->ra < NORTH_ANGLE)
				draw_wall->dir = EAST;
			else
				draw_wall->dir = WEST;
			ray->dist_f = ray->dist_v;
			ray->wall_hit_x = fmod(ray->ry, 1.0f);
		}
		if (ray->dist_h <= ray->dist_v) // horizontal hit N S
		{
			ray->rx = ray->x_h;
			ray->ry = ray->y_h;
			if (ray->ra > WEST_ANGLE)
				draw_wall->dir = NORTH;
			else
				draw_wall->dir = SOUTH;
			ray->dist_f = ray->dist_h;
			ray->wall_hit_x = fmod(ray->rx, 1.0f);
		}
		if (isnan(ray->wall_hit_x))
			ray->wall_hit_x = 0.0f;
		ray->wall_hit_x -= floor(ray->wall_hit_x);
}

void	ft_cast_rays(t_cub *cub)
{
	int r;
	t_raycasting *ray;
	t_draw_wall *draw_wall;
	
	r = 0;
	ft_init_structs_raycasting(&ray, &draw_wall, cub);
	if (!ray || !draw_wall)
		return ;
	while (r < WIN_WIDTH)
	{
		ft_horizontal_casting(cub, ray, draw_wall);
		ft_vertical_casting(cub, ray, draw_wall);
		ft_dir_dist(ray, draw_wall);
		draw_wall->tex_x = (int)(ray->wall_hit_x * 64);
		if ((ray->dist_v < ray->dist_h && ray->ra > SOUTH_ANGLE + TOL && ray->ra < NORTH_ANGLE - TOL) ||
			(ray->dist_h < ray->dist_v && ray->ra > WEST_ANGLE + TOL))
			draw_wall->tex_x = cub->texture->width[draw_wall->dir] - draw_wall->tex_x - 1;
		ray->ca = cub->player->angle - ray->ra;
		ft_check_limits(&ray->ca);
		ray->dist_f = ray->dist_f * cos(ray->ca);
		ray->dist_f = ray->dist_f * ray->aspect_ratio;
		draw_wall->line_height = (WIN_HEIGTH / ray->dist_f);
		ft_draw_wall(cub, r, draw_wall);
		ray->ra += ray->ray_step;
		ft_check_limits(&ray->ra);
		r++;
	}
}

