/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:31:15 by anferre           #+#    #+#             */
/*   Updated: 2024/08/27 16:56:49 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 


int	ft_read_texture(t_cub *cub)
{
	t_texture	*texture;


	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (EXIT_FAILURE);
	texture->img_ptr[NORTH] = mlx_xpm_file_to_image(cub->data->mlx_ptr, cub->parse->NO, &(texture->width[NORTH]), &(texture->height[NORTH]));
	texture->img_ptr[SOUTH] = mlx_xpm_file_to_image(cub->data->mlx_ptr, cub->parse->SO, &(texture->width[SOUTH]), &(texture->height[SOUTH]));
	texture->img_ptr[WEST] = mlx_xpm_file_to_image(cub->data->mlx_ptr, cub->parse->WE, &(texture->width[WEST]), &(texture->height[WEST]));
	texture->img_ptr[EAST] = mlx_xpm_file_to_image(cub->data->mlx_ptr, cub->parse->EA, &(texture->width[EAST]), &(texture->height[EAST]));
	if (!texture->img_ptr[NORTH] || !texture->img_ptr[SOUTH] || !texture->img_ptr[WEST] || !texture->img_ptr[EAST])
		return (EXIT_FAILURE);
	texture->addr[NORTH] = mlx_get_data_addr(texture->img_ptr[NORTH], &texture->bpp[NORTH], &texture->line_len[NORTH], &texture->endian[NORTH]);
	texture->addr[SOUTH] = mlx_get_data_addr(texture->img_ptr[SOUTH], &texture->bpp[SOUTH], &texture->line_len[SOUTH], &texture->endian[SOUTH]);
	texture->addr[WEST] = mlx_get_data_addr(texture->img_ptr[WEST], &texture->bpp[WEST], &texture->line_len[WEST], &texture->endian[WEST]);
	texture->addr[EAST] = mlx_get_data_addr(texture->img_ptr[EAST], &texture->bpp[EAST], &texture->line_len[EAST], &texture->endian[EAST]);
	cub->texture = texture;
	return (EXIT_SUCCESS);
}

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
		// cub->player->minimap_scale = WIN_WIDTH / cub->parse->map_width;
		cub->player->minimap_scale = MINIMAP_SIZE / cub->parse->map_width;
	else
		// cub->player->minimap_scale = WIN_HEIGTH / cub->parse->map_height;
		cub->player->minimap_scale = MINIMAP_SIZE / cub->parse->map_height;
	if (ft_read_texture(cub) == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
