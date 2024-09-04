/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:31:15 by anferre           #+#    #+#             */
/*   Updated: 2024/09/04 17:45:21 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

void	ft_get_texture_addr(t_texture *texture)
{
	texture->addr[NORTH] = mlx_get_data_addr(texture->img_ptr[NORTH], \
	&texture->bpp[NORTH], &texture->line_len[NORTH], &texture->endian[NORTH]);
	texture->addr[SOUTH] = mlx_get_data_addr(texture->img_ptr[SOUTH], \
	&texture->bpp[SOUTH], &texture->line_len[SOUTH], &texture->endian[SOUTH]);
	texture->addr[WEST] = mlx_get_data_addr(texture->img_ptr[WEST], \
	&texture->bpp[WEST], &texture->line_len[WEST], &texture->endian[WEST]);
	texture->addr[EAST] = mlx_get_data_addr(texture->img_ptr[EAST], \
	&texture->bpp[EAST], &texture->line_len[EAST], &texture->endian[EAST]);
}

int	ft_read_texture(t_cub *cub)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (EXIT_FAILURE);
	texture->img_ptr[NORTH] = mlx_xpm_file_to_image(cub->data->mlx_ptr, \
	cub->parse->NO, &(texture->width[NORTH]), &(texture->height[NORTH]));
	texture->img_ptr[SOUTH] = mlx_xpm_file_to_image(cub->data->mlx_ptr, \
	cub->parse->SO, &(texture->width[SOUTH]), &(texture->height[SOUTH]));
	texture->img_ptr[WEST] = mlx_xpm_file_to_image(cub->data->mlx_ptr, \
	cub->parse->WE, &(texture->width[WEST]), &(texture->height[WEST]));
	texture->img_ptr[EAST] = mlx_xpm_file_to_image(cub->data->mlx_ptr, \
	cub->parse->EA, &(texture->width[EAST]), &(texture->height[EAST]));
	if (!texture->img_ptr[NORTH] || !texture->img_ptr[SOUTH] || \
	!texture->img_ptr[WEST] || !texture->img_ptr[EAST])
		return (printf("Error \n: Texture\n"), free(texture), ft_exit_mlx(cub), \
		EXIT_FAILURE);
	ft_get_texture_addr(texture);
	cub->texture = texture;
	return (EXIT_SUCCESS);
}

int	ft_init_mlx(t_cub *cub)
{
	cub->data->mlx_ptr = mlx_init();
	if (!cub->data->mlx_ptr)
		return (ft_error(cub, "mlx init", -1, -1), EXIT_FAILURE);
	cub->data->win_ptr = mlx_new_window(cub->data->mlx_ptr, WIN_WIDTH, \
	WIN_HEIGTH, "cub3d");
	if (!cub->data->win_ptr)
		return (ft_error(cub, "mlx win", -1, -1), EXIT_FAILURE);
	cub->data->img.mlx_img = mlx_new_image(cub->data->mlx_ptr, WIN_WIDTH, \
	WIN_HEIGTH);
	if (!cub->data->img.mlx_img)
		return (ft_error(cub, "mlx img", -1, -1), EXIT_FAILURE);
	cub->data->img.addr = mlx_get_data_addr(cub->data->img.mlx_img, \
	&cub->data->img.bpp, &cub->data->img.line_len, &cub->data->img.endian);
	if (!cub->data->img.addr)
		return (ft_error(cub, "mlx addr", -1, -1), EXIT_FAILURE);
	if (cub->parse->map_width > cub->parse->map_height)
		cub->player->minimap_scale = MINIMAP_SIZE / cub->parse->map_width;
	else
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
