/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_key_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:39:52 by tookops           #+#    #+#             */
/*   Updated: 2024/09/02 09:22:52 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_handle_w(t_cub *cub)
{
	t_coord	new;
	t_coord	cur;
	
	new.x = cub->player->x_cur + cub->player->delta_x * STEP_SIZE;
	new.y = cub->player->y_cur + cub->player->delta_y * STEP_SIZE;
	cur.x = cub->player->x_cur;
	cur.y = cub->player->y_cur;
	if (ft_is_path_clear(cub, cur, new))
	{
		cub->player->x_cur = new.x;
		cub->player->y_cur = new.y;
	}
}

void	ft_handle_s(t_cub *cub)
{
	t_coord	new;
	t_coord	cur;
	
	new.x = cub->player->x_cur - cub->player->delta_x * STEP_SIZE;
	new.y = cub->player->y_cur - cub->player->delta_y * STEP_SIZE;
	cur.x = cub->player->x_cur;
	cur.y = cub->player->y_cur;
	if (ft_is_path_clear(cub, cur, new))
	{
		cub->player->x_cur = new.x;
		cub->player->y_cur = new.y;
	}
}

void	ft_handle_a(t_cub *cub)
{
	t_coord	new;
	t_coord	cur;
	
	new.x = cub->player->x_cur + cub->player->delta_y * STEP_SIZE;
	new.y = cub->player->y_cur - cub->player->delta_x * STEP_SIZE;
	cur.x = cub->player->x_cur;
	cur.y = cub->player->y_cur;
	if (ft_is_path_clear(cub, cur, new))
	{
		cub->player->x_cur = new.x;
		cub->player->y_cur = new.y;
	}
}

void	ft_handle_d(t_cub *cub)
{
	t_coord	new;
	t_coord	cur;
	
	new.x = cub->player->x_cur - cub->player->delta_y * STEP_SIZE;
	new.y = cub->player->y_cur + cub->player->delta_x * STEP_SIZE;
	cur.x = cub->player->x_cur;
	cur.y = cub->player->y_cur;
	if (ft_is_path_clear(cub, cur, new))
	{
		cub->player->x_cur = new.x;
		cub->player->y_cur = new.y;
	}
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
