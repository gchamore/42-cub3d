/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:15:51 by anferre           #+#    #+#             */
/*   Updated: 2024/08/19 16:29:03 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

void	ft_render_background(t_cub *cub, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGTH)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			ft_mpp(&cub->data->img, j, i, color);
			j++;
		}
		i++;
	}
}

void ft_draw_player(t_cub *cub)
{

	
	int pos_x = cub->x_cur * 64;
	int pos_y = cub->y_cur * 64;
	int half_size;
	int dx;
	int dy;
	
	half_size = 5;
	dx = -half_size;
	dy = -half_size;
	while (dy < half_size)
	{
		dx = -2;
		while (dx < half_size)
		{
			ft_mpp(&cub->data->img, pos_x + dx, pos_y + dy, BLUE_COLOR);
			dx++;
		}
		dy++;
	}
}

int	ft_render(t_cub *cub)
{
	ft_render_background(cub, GREY_COLOR);
	ft_draw_player(cub);
	mlx_put_image_to_window(cub->data->mlx_ptr, cub->data->win_ptr, cub->data->img.mlx_img, 0, 0);
	return (0);
}

int	ft_key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(cub->data->mlx_ptr, cub->data->win_ptr);
		cub->data->win_ptr = NULL;
		ft_free_cub(cub);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	ft_handle_red_cross(t_cub *cub)
{
	mlx_destroy_window(cub->data->mlx_ptr, cub->data->win_ptr);
	cub->data->win_ptr = NULL;
	ft_free_cub(cub);
	exit(EXIT_SUCCESS);
}

void	ft_project(t_cub *cub)
{
	cub->x_cur = 5; // a changer mettre start dans curr avant
	cub->y_cur = 1;
	mlx_loop_hook(cub->data->mlx_ptr, ft_render, cub);
	mlx_key_hook(cub->data->win_ptr, ft_key_press, cub);
	mlx_hook(cub->data->win_ptr, 17, (1L << 17), ft_handle_red_cross, cub);
	mlx_loop(cub->data->mlx_ptr);
}