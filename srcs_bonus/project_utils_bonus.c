/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:34:07 by tookops           #+#    #+#             */
/*   Updated: 2024/09/04 17:25:16 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

int	ft_is_wall(t_cub *cub, float x, float y)
{
	float	tol;

	tol = 0.1;
	x += 0.5;
	y += 0.5;
	if ((int)(x + tol) < 0 || (int)(y + tol) < 0 || \
	(size_t)(x + tol) >= cub->parse->map_width ||
		(size_t)(y + tol) >= cub->parse->map_height)
		return (1);
	if (cub->map[(int)(y + tol)][(int)(x + tol)].value == '1')
		return (1);
	if (cub->map[(int)(y - tol)][(int)(x + tol)].value == '1')
		return (1);
	if (cub->map[(int)(y + tol)][(int)(x - tol)].value == '1')
		return (1);
	if (cub->map[(int)(y - tol)][(int)(x - tol)].value == '1')
		return (1);
	return (0);
}

int	ft_is_path_clear(t_cub *cub, t_coord start, t_coord end)
{
	int		i;
	double	step;
	t_coord	d;
	t_coord	pos;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	step = fmax(fabs(d.x), fabs(d.y));
	d.x /= step;
	d.y /= step;
	pos.x = start.x;
	pos.y = start.y;
	i = 0;
	while (i <= step)
	{
		if ((d.x > 0 && ft_is_wall(cub, pos.x + 0.1, pos.y)) || \
		(d.x < 0 && ft_is_wall(cub, pos.x - 0.1, pos.y)) || \
		(d.y > 0 && ft_is_wall(cub, pos.x, pos.y + 0.1)) || \
		(d.y < 0 && ft_is_wall(cub, pos.x, pos.y - 0.1)))
			return (0);
		pos.x += d.x;
		pos.y += d.y;
		i++;
	}
	return (1);
}

void	ft_draw_tiles(t_cub *cub, float pos_x, float pos_y, int color)
{
	int	i;
	int	j;

	i = 1;
	while (i < cub->player->minimap_scale)
	{
		j = 1;
		while (j < cub->player->minimap_scale)
		{
			ft_mpp(&cub->data->img, pos_x + j, pos_y + i, color);
			j++;
		}
		i++;
	}
}

int	ft_exit_mlx(t_cub *cub)
{
	mlx_destroy_image(cub->data->mlx_ptr, cub->data->img.mlx_img);
	cub->data->img.mlx_img = NULL;
	mlx_destroy_window(cub->data->mlx_ptr, cub->data->win_ptr);
	cub->data->win_ptr = NULL;
	if (cub->texture)
	{
		if (cub->texture->img_ptr[NORTH])
			mlx_destroy_image(cub->data->mlx_ptr, cub->texture->img_ptr[NORTH]);
		if (cub->texture->img_ptr[SOUTH])
			mlx_destroy_image(cub->data->mlx_ptr, cub->texture->img_ptr[SOUTH]);
		if (cub->texture->img_ptr[WEST])
			mlx_destroy_image(cub->data->mlx_ptr, cub->texture->img_ptr[WEST]);
		if (cub->texture->img_ptr[EAST])
			mlx_destroy_image(cub->data->mlx_ptr, cub->texture->img_ptr[EAST]);
	}
	mlx_destroy_display(cub->data->mlx_ptr);
	free(cub->data->mlx_ptr);
	cub->data->mlx_ptr = NULL;
	ft_free_cub(cub);
	exit(EXIT_SUCCESS);
}
