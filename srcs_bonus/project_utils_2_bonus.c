/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_utils_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:34:07 by tookops           #+#    #+#             */
/*   Updated: 2024/09/03 11:16:53 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

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
	if (x < 0 || x >= WIN_WIDTH)
		return (cub->player->mousse_x = WIN_WIDTH / 2, 0);
	if (cub->player->mousse_x == -1)
	{
		cub->player->mousse_x = x;
		cub->player->last_render = ft_get_time();
		return (0);
	}
	rotation_speed = (x - cub->player->mousse_x) * 0.007;
	cub->player->mousse_x = x;
	cub->player->angle += rotation_speed;
	ft_check_limits(&cub->player->angle);
	cur_time = ft_get_time();
	if (cur_time - cub->player->last_render > 50)
	{
		ft_render(cub);
		cub->player->last_render = cur_time;
	}
	return (0);
}
