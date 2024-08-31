/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookops <tookops@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:39:52 by tookops           #+#    #+#             */
/*   Updated: 2024/08/31 20:45:43 by tookops          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_handle_w(t_cub *cub)
{
	cub->player->x_cur += cub->player->delta_x * STEP_SIZE;
	cub->player->y_cur += cub->player->delta_y * STEP_SIZE;
}

void	ft_handle_s(t_cub *cub)
{
	cub->player->x_cur -= cub->player->delta_x * STEP_SIZE;
	cub->player->y_cur -= cub->player->delta_y * STEP_SIZE;
}

void	ft_handle_a(t_cub *cub)
{
	cub->player->x_cur += cub->player->delta_y * STEP_SIZE;
	cub->player->y_cur -= cub->player->delta_x * STEP_SIZE;
}

void	ft_handle_d(t_cub *cub)
{
	cub->player->x_cur -= cub->player->delta_y * STEP_SIZE;
	cub->player->y_cur += cub->player->delta_x * STEP_SIZE;
}

void	ft_handle_left_right(t_cub *cub, int keycode)
{
	if (keycode == XK_Left)
	{
		cub->player->angle -= ROTATION_SPEED;
		if (cub->player->angle < 0)
			cub->player->angle += 2 * PI;
	}
	if (keycode == XK_Right)
	{
		cub->player->angle += ROTATION_SPEED;
		if (cub->player->angle > 2 * PI)
			cub->player->angle -= 2 * PI;
	}
}
