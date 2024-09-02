/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:15:51 by anferre           #+#    #+#             */
/*   Updated: 2024/09/02 07:50:35 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

int	ft_render(t_cub *cub)
{
	ft_cast_rays(cub);
	mlx_put_image_to_window(cub->data->mlx_ptr, cub->data->win_ptr, \
	cub->data->img.mlx_img, 0, 0);
	return (0);
}

int	ft_key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		ft_exit_mlx(cub);
	if (keycode == XK_w || keycode == XK_W)
		ft_handle_w(cub);
	if (keycode == XK_s || keycode == XK_S)
		ft_handle_s(cub);
	if (keycode == XK_a || keycode == XK_A)
		ft_handle_a(cub);
	if (keycode == XK_d || keycode == XK_D)
		ft_handle_d(cub);
	if (keycode == XK_Left || keycode == XK_Right)
		ft_handle_left_right(cub, keycode);
	cub->player->delta_x = cos(cub->player->angle);
	cub->player->delta_y = sin(cub->player->angle);
	ft_render(cub);
	return (0);
}

void	ft_init_player(t_cub *cub)
{
	cub->player->x_cur = cub->player->x_start;
	cub->player->y_cur = cub->player->y_start;
	if (cub->player->dir == 'N')
		cub->player->angle = NORTH_ANGLE;
	if (cub->player->dir == 'S')
		cub->player->angle = SOUTH_ANGLE;
	if (cub->player->dir == 'W')
		cub->player->angle = WEST_ANGLE;
	if (cub->player->dir == 'E')
		cub->player->angle = EAST_ANGLE;
	cub->player->delta_x = cos(cub->player->angle);
	cub->player->delta_y = sin(cub->player->angle);
}

void	ft_project(t_cub *cub)
{
	ft_init_player(cub);
	ft_init_structs_raycasting(&cub);
	ft_render(cub);
	mlx_hook(cub->data->win_ptr, KeyPress, KeyPressMask, ft_key_press, cub);
	mlx_hook(cub->data->win_ptr, 17, (1L << 17), ft_exit_mlx, cub);
	mlx_loop(cub->data->mlx_ptr);
}
