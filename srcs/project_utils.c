/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:34:07 by tookops           #+#    #+#             */
/*   Updated: 2024/09/04 17:30:17 by anferre          ###   ########.fr       */
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
