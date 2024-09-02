/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:40:10 by tookops           #+#    #+#             */
/*   Updated: 2024/09/02 10:39:59 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//get the texture x coordinate reversed if the wall is facing left or up
// corrected angle ca for fisheye aspect ratio to keep proportions
void	ft_calculate_tex_dist(t_cub *cub, t_raycasting *ray, \
t_draw_wall *draw_wall)
{
	draw_wall->tex_x = (int)(ray->wall_hit_x * 64);
	if ((ray->dist_v < ray->dist_h && ray->ra > SOUTH_ANGLE + TOL && \
	ray->ra < NORTH_ANGLE - TOL) || (ray->dist_h < ray->dist_v && \
	ray->ra > WEST_ANGLE + TOL))
		draw_wall->tex_x = cub->texture->width[draw_wall->dir] - \
		draw_wall->tex_x - 1;
	ray->ca = cub->player->angle - ray->ra;
	ft_check_limits(&ray->ca);
	ray->dist_f = ray->dist_f * cos(ray->ca);
	ray->dist_f = ray->dist_f * ray->aspect_ratio;
	draw_wall->line_height = (WIN_HEIGTH / ray->dist_f);
}

void	ft_calculate_texture(t_cub *cub, t_draw_wall *draw_wall)
{
	draw_wall->y_start = (WIN_HEIGTH / 2) - (draw_wall->line_height / 2);
	draw_wall->y_end = (WIN_HEIGTH / 2) + (draw_wall->line_height / 2);
	if (draw_wall->y_start < 0)
		draw_wall->y_start = 0;
	if (draw_wall->y_end >= WIN_HEIGTH)
		draw_wall->y_end = WIN_HEIGTH - 1;
	draw_wall->step = 1.0 * cub->texture->height[draw_wall->dir] / \
	draw_wall->line_height;
	draw_wall->tex_pos = (draw_wall->y_start - WIN_HEIGTH / 2 + \
	draw_wall->line_height / 2) * draw_wall->step;
}

void	ft_draw_wall(t_cub *cub, int x, t_draw_wall *draw_wall)
{
	int	y;

	ft_calculate_texture(cub, draw_wall);
	y = draw_wall->y_start;
	while (y >= draw_wall->y_start && y <= draw_wall->y_end)
	{
		draw_wall->tex_y = (int)(draw_wall->tex_pos) % \
		cub->texture->height[draw_wall->dir];
		draw_wall->tex_pos += draw_wall->step;
		draw_wall->color = *(int *)(cub->texture->addr[draw_wall->dir] + \
		(draw_wall->tex_y * cub->texture->line_len[draw_wall->dir] + \
		draw_wall->tex_x * (cub->texture->bpp[draw_wall->dir] / 8)));
		ft_mpp(&cub->data->img, x, y, draw_wall->color);
		y++;
	}
	y = 0;
	while (y < WIN_HEIGTH)
	{
		if (y < draw_wall->y_start)
			ft_mpp(&cub->data->img, x, y, ft_rgb_to_int(cub->parse->C));
		else if (y >= draw_wall->y_end)
			ft_mpp(&cub->data->img, x, y, ft_rgb_to_int(cub->parse->F));
		y++;
	}
}
