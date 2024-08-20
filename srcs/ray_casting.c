/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:37:13 by anferre           #+#    #+#             */
/*   Updated: 2024/08/20 18:44:16 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_cast_rays(t_cub *cub)
{
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;

	ra = cub->player->angle;
	r = 0;
	while (r < 1)
	{
		//horizontal lines
		dof = 0;
		float aTan = -1 / tan(ra);
		if (ra > PI) //looking down
		{
			ry = (((int)cub->player->y_cur >> 6) << 6) - 0.0001;
			rx = (cub->player->y_cur - ry) * aTan + cub->player->x_cur;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI) //looking up
		{
			ry = (((int)cub->player->y_cur >> 6) << 6) + 64;
			rx = (cub->player->y_cur - ry) * aTan + cub->player->x_cur;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI) //looking straight left or right
		{
			rx = cub->player->x_cur;
			ry = cub->player->y_cur;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * cub->parse->map_width + mx; //need to check if width and height are switched x / y 
			if (mp < cub->parse->map_width * cub->parse->map_height && mp > 0 && cub->map[mp] == '1')
			{
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			} 
		}
		r++;
	}
}

