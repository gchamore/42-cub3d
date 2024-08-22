/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:31:15 by anferre           #+#    #+#             */
/*   Updated: 2024/08/21 18:46:07 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

int	ft_init_mlx(t_cub *cub)
{
	cub->data = malloc(sizeof(t_data));
	if (!cub->data)
		return (EXIT_FAILURE);
	cub->data->mlx_ptr = mlx_init();
	if (!cub->data->mlx_ptr)
		return (EXIT_FAILURE);
	cub->data->win_ptr = mlx_new_window(cub->data->mlx_ptr, WIN_WIDTH, WIN_HEIGTH, "cub3d");
	if (!cub->data->win_ptr)
		return (EXIT_FAILURE);
	cub->data->img.mlx_img = mlx_new_image(cub->data->mlx_ptr, WIN_WIDTH, WIN_HEIGTH);
	if (!cub->data->img.mlx_img)
		return (EXIT_FAILURE);
	cub->data->img.addr = mlx_get_data_addr(cub->data->img.mlx_img, &cub->data->img.bpp, &cub->data->img.line_len, &cub->data->img.endian);
	if (!cub->data->img.addr)
		return (EXIT_FAILURE);
	if (cub->parse->map_width > cub->parse->map_height)
		cub->player->minimap_scale = WIN_WIDTH / cub->parse->map_width;
		// cub->player->minimap_scale = MINIMAP_SIZE / cub->parse->map_width;
	else
		// cub->player->minimap_scale = MINIMAP_SIZE / cub->parse->map_height;
		cub->player->minimap_scale = WIN_HEIGTH / cub->parse->map_height;
	printf("minimap scale: %f\n", cub->player->minimap_scale);
	return (EXIT_SUCCESS);
}

void	ft_mpp(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x > WIN_WIDTH || y > WIN_HEIGTH || x < 0 || y < 0)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
