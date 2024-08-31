/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookops <tookops@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:34:07 by tookops           #+#    #+#             */
/*   Updated: 2024/08/31 20:38:35 by tookops          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

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

int	ft_handle_red_cross(t_cub *cub)
{
	mlx_destroy_window(cub->data->mlx_ptr, cub->data->win_ptr);
	cub->data->win_ptr = NULL;
	ft_free_cub(cub);
	exit(EXIT_SUCCESS);
}

void	ft_handle_esc(t_cub *cub)
{
	mlx_destroy_window(cub->data->mlx_ptr, cub->data->win_ptr);
	cub->data->win_ptr = NULL;
	ft_free_cub(cub);
	exit(EXIT_SUCCESS);
}
