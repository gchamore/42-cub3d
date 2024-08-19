/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:15:51 by anferre           #+#    #+#             */
/*   Updated: 2024/08/19 19:21:22 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" 

void	ft_draw_tiles(t_cub *cub, float pos_x, float pos_y, int color)
{
	int	i;
	int	j;

	i = 1;
	while (i < cub->player->minimap_scale -1)
	{
		j = 1;
		while (j < cub->player->minimap_scale -1)
		{
			ft_mpp(&cub->data->img, pos_x + j, pos_y + i, color);
			j++;
		}
		i++;
	}
}

void 		ft_draw_player_minimap(t_cub *cub, float start_x, float start_y)
{
	float	player_pos_x;
	float	player_pos_y;
	float	player_size;
	int		i;
	int		j;

	player_pos_x = start_x + cub->player->x_cur * cub->player->minimap_scale;
    player_pos_y = start_y + cub->player->y_cur * cub->player->minimap_scale;
	player_size = cub->player->minimap_scale / 4;
	i = 0;
	while (i < player_size)
	{
		j = 0;
		while (j < player_size)
		{
			ft_mpp(&cub->data->img, player_pos_x + j, player_pos_y + i, BLUE_COLOR);
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_cub *cub)
{
	size_t		x;
	size_t		y;
	int 	start_x;
	int 	start_y;
	float	pos_x;
	float	pos_y;

	start_x = WIN_WIDTH - MINIMAP_SIZE + (MINIMAP_SIZE - cub->parse->map_width * cub->player->minimap_scale) / 2;
	start_y = WIN_HEIGTH - MINIMAP_SIZE + (MINIMAP_SIZE - cub->parse->map_height * cub->player->minimap_scale) / 2;


	
	y = 0;
	while (y < cub->parse->map_height)
	{
		x = 0;
		while (x < cub->parse->map_width)
		{
			pos_x = start_x + x * cub->player->minimap_scale;
			pos_y = start_y + y * cub->player->minimap_scale;
			if (cub->map[y][x].value == '1')
				ft_draw_tiles(cub, pos_x, pos_y, BLACK_COLOR);
			else
				ft_draw_tiles(cub, pos_x, pos_y, WHITE_COLOR);
			x++;
		}
		y++;
	}
	ft_draw_player_minimap(cub, start_x, start_y);
}

void	ft_render_background(t_cub *cub, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGTH)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			ft_mpp(&cub->data->img, j, i, color);
			j++;
		}
		i++;
	}
}

int	ft_render(t_cub *cub)
{
	ft_render_background(cub, GREY_COLOR);
	ft_draw_map(cub);
	mlx_put_image_to_window(cub->data->mlx_ptr, cub->data->win_ptr, cub->data->img.mlx_img, 0, 0);
	return (0);
}

int	ft_key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(cub->data->mlx_ptr, cub->data->win_ptr);
		cub->data->win_ptr = NULL;
		ft_free_cub(cub);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	ft_handle_red_cross(t_cub *cub)
{
	mlx_destroy_window(cub->data->mlx_ptr, cub->data->win_ptr);
	cub->data->win_ptr = NULL;
	ft_free_cub(cub);
	exit(EXIT_SUCCESS);
}

void	ft_project(t_cub *cub)
{
	mlx_loop_hook(cub->data->mlx_ptr, ft_render, cub);
	mlx_key_hook(cub->data->win_ptr, ft_key_press, cub);
	mlx_hook(cub->data->win_ptr, 17, (1L << 17), ft_handle_red_cross, cub);
	mlx_loop(cub->data->mlx_ptr);
}