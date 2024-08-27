/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookops <tookops@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:15:51 by anferre           #+#    #+#             */
/*   Updated: 2024/08/26 02:12:27 by tookops          ###   ########.fr       */
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

void ft_draw_line(t_img *img, float x0, float y0, float x1, float y1, int color)
{
    float dx = fabs(x1 - x0);
    float dy = fabs(y1 - y0);
    float sx = (x0 < x1) ? 1 : -1;
    float sy = (y0 < y1) ? 1 : -1;
    float err = dx - dy;
    float e2;
	float tolerance = 0.5;

    while (1)
    {
        ft_mpp(img, x0, y0, color);
        if (fabs(x0 - x1) < tolerance && fabs(y0 - y1) < tolerance)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx * tolerance;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy * tolerance;
        }
		// if (fabs(x0 - x1) < 2 && fabs(y0 - y1) < 2)
		// 	// printf("x0 = %f, y0 = %f x1= %f, y1 = %f \n", x0, y0, x1, y1);
    }
}

void ft_player_orientation(t_cub *cub, float player_pos_x, float player_pos_y)
{
	float line_length = cub->player->minimap_scale *2;
	float player_size = PLAYER_SIZE * cub->player->minimap_scale;
	player_pos_x += player_size / 2;
	player_pos_y += player_size / 2;
	float end_x = player_pos_x + line_length * cos(cub->player->angle);
	float end_y = player_pos_y + line_length * sin(cub->player->angle);
	// printf("curr x = %f, y = %f \n", cub->player->x_cur, cub->player->y_cur);
	// printf("start_x = %f, start_y = %f, end_x = %f, end_y = %f\n", player_pos_x, player_pos_y, end_x, end_y);
	ft_draw_line(&cub->data->img, player_pos_x, player_pos_y, end_x, end_y, RED_COLOR);
}

void 		ft_draw_player_minimap(t_cub *cub, float start_x, float start_y)
{
	float	player_pos_x;
	float	player_pos_y;
	float	player_size;
	int		i;
	int		j;

	player_size = PLAYER_SIZE * cub->player->minimap_scale;
	player_pos_x = start_x + (cub->player->x_cur * cub->player->minimap_scale) + (cub->player->minimap_scale / 2) - (player_size / 2);
    player_pos_y = start_y + (cub->player->y_cur * cub->player->minimap_scale) + (cub->player->minimap_scale / 2) - (player_size / 2);
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
	ft_player_orientation(cub, player_pos_x, player_pos_y);
}

void	ft_draw_map(t_cub *cub)
{
	size_t		x;
	size_t		y;
	int 	start_x;
	int 	start_y;
	float	pos_x;
	float	pos_y;
	//minimap scale
	start_x = WIN_WIDTH - MINIMAP_SIZE + (MINIMAP_SIZE - cub->parse->map_width * cub->player->minimap_scale) / 2;
	start_y = WIN_HEIGTH - MINIMAP_SIZE + (MINIMAP_SIZE - cub->parse->map_height * cub->player->minimap_scale) / 2;

	//full window scale
	// cub->player->minimap_scale = fmin(WIN_WIDTH / cub->parse->map_width, WIN_HEIGTH / cub->parse->map_height);

	
	y = 0;
	while (y < cub->parse->map_height)
	{
		x = 0;
		while (x < cub->parse->map_width)
		{
			//minimap scale
			pos_x = start_x + x * cub->player->minimap_scale;
			pos_y = start_y + y * cub->player->minimap_scale;
			//full window scale 
			// pos_x = x * cub->player->minimap_scale;
            // pos_y = y * cub->player->minimap_scale;
			if (cub->map[y][x].value == '1')
				ft_draw_tiles(cub, pos_x, pos_y, BLACK_COLOR);
			else
				ft_draw_tiles(cub, pos_x, pos_y, WHITE_COLOR);
			x++;
		}
		y++;
	}
	//minimap scale
	ft_draw_player_minimap(cub, start_x, start_y);
	//full window scale
	// ft_draw_player_minimap(cub, 0, 0);
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
	ft_cast_rays(cub);
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
	if (keycode == XK_w || keycode == XK_W)
	{
		cub->player->x_cur += cub->player->delta_x * STEP_SIZE;
		cub->player->y_cur += cub->player->delta_y * STEP_SIZE;
	}
	if (keycode == XK_s || keycode == XK_S)
	{
		cub->player->x_cur -= cub->player->delta_x * STEP_SIZE;
		cub->player->y_cur -= cub->player->delta_y * STEP_SIZE;
	}
	if (keycode == XK_a || keycode == XK_A)
	{
		cub->player->angle -= ROTATION_SPEED;
		if (cub->player->angle < 0)
			cub->player->angle += 2 * PI;
	}
	if (keycode == XK_d || keycode == XK_D)
	{
		cub->player->angle += ROTATION_SPEED;
		if (cub->player->angle > 2 * PI)
			cub->player->angle -= 2 * PI;
	}
	cub->player->delta_x = cos(cub->player->angle);
	cub->player->delta_y = sin(cub->player->angle);
	ft_render(cub);
	// printf("Player position: x = %f, y = %f angle = %f\n", cub->player->x_cur, cub->player->y_cur, cub->player->angle);
	return (0);
}

int	ft_handle_red_cross(t_cub *cub)
{
	mlx_destroy_window(cub->data->mlx_ptr, cub->data->win_ptr);
	cub->data->win_ptr = NULL;
	ft_free_cub(cub);
	exit(EXIT_SUCCESS);
}

void	ft_init_player(t_cub *cub)
{
	cub->player->x_cur = cub->player->x_start;
	cub->player->y_cur = cub->player->y_start;
	if (cub->player->dir == 'N')
		cub->player->angle = NORTH_ANGLE;
	if (cub->player->dir == 'S')
		cub->player->angle = SOUTH_ANGLE;
	if (cub->player->dir == 'W')
		cub->player->angle = WEST_ANGLE;
	if (cub->player->dir == 'E')
		cub->player->angle = EAST_ANGLE;
	cub->player->delta_x = cos(cub->player->angle);
	cub->player->delta_y = sin(cub->player->angle);
	// printf("player start position: x = %f, y = %f, \n", cub->player->x_cur, cub->player->y_cur);
}

void	ft_project(t_cub *cub)
{
	ft_init_player(cub);
	ft_render(cub);
	// mlx_loop_hook(cub->data->mlx_ptr, ft_render, cub);
	mlx_hook(cub->data->win_ptr, KeyPress, KeyPressMask, ft_key_press, cub);
	mlx_hook(cub->data->win_ptr, 17, (1L << 17), ft_handle_red_cross, cub);
	mlx_hook(cub->data->win_ptr, KeyRelease, KeyReleaseMask, NULL, cub);
	mlx_loop(cub->data->mlx_ptr);
}