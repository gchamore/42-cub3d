/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookops <tookops@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:34:07 by tookops           #+#    #+#             */
/*   Updated: 2024/09/02 17:13:06 by tookops          ###   ########.fr       */
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
	if (cub->texture->img_ptr[NORTH])
		mlx_destroy_image(cub->data->mlx_ptr, cub->texture->img_ptr[NORTH]);
	if (cub->texture->img_ptr[SOUTH])
		mlx_destroy_image(cub->data->mlx_ptr, cub->texture->img_ptr[SOUTH]);
	if (cub->texture->img_ptr[WEST])
		mlx_destroy_image(cub->data->mlx_ptr, cub->texture->img_ptr[WEST]);
	if (cub->texture->img_ptr[EAST])
		mlx_destroy_image(cub->data->mlx_ptr, cub->texture->img_ptr[EAST]);
	mlx_destroy_display(cub->data->mlx_ptr);
	free(cub->data->mlx_ptr);
	cub->data->mlx_ptr = NULL;
	ft_free_cub(cub);
	exit(EXIT_SUCCESS);
}

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_mouse(int x, int y, t_cub *cub)
{
	float	rotation_speed;
	long	cur_time;

	(void)y;
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGTH)
	{
		mlx_mouse_move(cub->data->mlx_ptr ,cub->data->win_ptr, (int)(WIN_WIDTH / 2), (int)(WIN_HEIGTH / 2));
		cub->player->mousse_x = WIN_WIDTH / 2;
		return (0);	
	}
	if (cub->player->mousse_x == -1)
	{
		cub->player->mousse_x = x;
		cub->player->last_render = ft_get_time();
		return (0);
	}
	rotation_speed = (x - cub->player->mousse_x) * 0.01;
	cub->player->mousse_x = x;
	cub->player->angle += rotation_speed;
	ft_check_limits(&cub->player->angle);
	cur_time = ft_get_time();
	if (cur_time - cub->player->last_render > 25)
	{
		ft_render(cub);
		cub->player->last_render = cur_time;
	}
	return (0);
}
