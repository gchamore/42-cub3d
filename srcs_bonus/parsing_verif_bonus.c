/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:22:42 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/22 14:37:30 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_inside(t_cub *cub, size_t y, size_t x)
{
	if (cub->map[y + 1][x].value == '0' || cub->map[y + 1][x].value == 'N' || cub->map[y + 1][x].value == 'S' || cub->map[y + 1][x].value == 'W' || cub->map[y + 1][x].value == 'E')
		ft_error(cub, "Invalid map 1", y, x);
	else if (cub->map[y - 1][x].value == '0' || cub->map[y - 1][x].value == 'N' || cub->map[y - 1][x].value == 'S' || cub->map[y - 1][x].value == 'W' || cub->map[y - 1][x].value == 'E')
		ft_error(cub, "Invalid map 2", y, x);
	else if (cub->map[y][x + 1].value == '0' || cub->map[y][x + 1].value == 'N' || cub->map[y][x + 1].value == 'S' || cub->map[y][x + 1].value == 'W' || cub->map[y][x + 1].value == 'E')
		ft_error(cub, "Invalid map 3", y, x);
	else if (cub->map[y][x - 1].value == '0' || cub->map[y][x - 1].value == 'N' || cub->map[y][x - 1].value == 'S' || cub->map[y][x - 1].value == 'W' || cub->map[y][x - 1].value == 'E')
		ft_error(cub, "Invalid map 4", y, x);
}
void	ft_check_corners_1(t_cub *cub, size_t y, size_t x)
{
	if (y == 0 && x == 0)
	{
		if (cub->map[y][x].value == ' ' && (cub->map[y + 1][x].value == '0' || cub->map[y + 1][x].value == 'N' || cub->map[y + 1][x].value == 'S' || cub->map[y + 1][x].value == 'W' || cub->map[y + 1][x].value == 'E'))
			ft_error(cub, "Invalid map 5", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y][x + 1].value == '0' || cub->map[y][x + 1].value == 'N' || cub->map[y][x + 1].value == 'S' || cub->map[y][x + 1].value == 'W' || cub->map[y][x + 1].value == 'E'))
			ft_error(cub, "Invalid map 6", y, x);
	}
	if (y == cub->parse->map_height - 1 && x == cub->parse->map_width - 1)
	{
		if (cub->map[y][x].value == ' ' && (cub->map[y - 1][x].value == '0' || cub->map[y - 1][x].value == 'N' || cub->map[y - 1][x].value == 'S' || cub->map[y - 1][x].value == 'W' || cub->map[y - 1][x].value == 'E'))
			ft_error(cub, "Invalid map 7", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y][x - 1].value == '0' || cub->map[y][x - 1].value == 'N' || cub->map[y][x - 1].value == 'S' || cub->map[y][x - 1].value == 'W' || cub->map[y][x - 1].value == 'E'))
			ft_error(cub, "Invalid map 8", y, x);
	}
}
void	ft_check_corners_2(t_cub *cub, size_t y, size_t x)
{
	if (y == 0 && x == cub->parse->map_width - 1)
	{
		if (cub->map[y][x].value == ' ' && (cub->map[y + 1][x].value == '0' || cub->map[y + 1][x].value == 'N' || cub->map[y + 1][x].value == 'S' || cub->map[y + 1][x].value == 'W' || cub->map[y + 1][x].value == 'E'))
			ft_error(cub, "Invalid map 9", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y][x - 1].value == '0' || cub->map[y][x - 1].value == 'N' || cub->map[y][x - 1].value == 'S' || cub->map[y][x - 1].value == 'W' || cub->map[y][x - 1].value == 'E'))
			ft_error(cub, "Invalid map 10", y, x);
	}
	if (y == cub->parse->map_height - 1 && x == 0)
	{
		if (cub->map[y][x].value == ' ' && (cub->map[y - 1][x].value == '0' || cub->map[y - 1][x].value == 'N' || cub->map[y - 1][x].value == 'S' || cub->map[y - 1][x].value == 'W' || cub->map[y - 1][x].value == 'E'))
			ft_error(cub, "Invalid map 11", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y][x + 1].value == '0' || cub->map[y][x + 1].value == 'N' || cub->map[y][x + 1].value == 'S' || cub->map[y][x + 1].value == 'W' || cub->map[y][x + 1].value == 'E'))
			ft_error(cub, "Invalid map 12", y, x);
	}
}

void	ft_check_sides_1(t_cub *cub, size_t y, size_t x)
{
	if (y == 0 && x > 0 && x < cub->parse->map_width - 1)
	{
		if (cub->map[y][x].value == ' ' && (cub->map[y + 1][x].value == '0' || cub->map[y + 1][x].value == 'N' || cub->map[y + 1][x].value == 'S' || cub->map[y + 1][x].value == 'W' || cub->map[y + 1][x].value == 'E'))
			ft_error(cub, "Invalid map 13", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y][x + 1].value == '0' || cub->map[y][x + 1].value == 'N' || cub->map[y][x + 1].value == 'S' || cub->map[y][x + 1].value == 'W' || cub->map[y][x + 1].value == 'E'))
			ft_error(cub, "Invalid map 14", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y][x - 1].value == '0' || cub->map[y][x - 1].value == 'N' || cub->map[y][x - 1].value == 'S' || cub->map[y][x - 1].value == 'W' || cub->map[y][x - 1].value == 'E'))
			ft_error(cub, "Invalid map 15", y, x);
	}
	if (x == 0 && y > 0 && y < cub->parse->map_height - 1)
	{
		if (cub->map[y][x].value == ' ' && (cub->map[y + 1][x].value == '0' || cub->map[y + 1][x].value == 'N' || cub->map[y + 1][x].value == 'S' || cub->map[y + 1][x].value == 'W' || cub->map[y + 1][x].value == 'E'))
			ft_error(cub, "Invalid map 16", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y - 1][x].value == '0' || cub->map[y - 1][x].value == 'N' || cub->map[y - 1][x].value == 'S' || cub->map[y - 1][x].value == 'W' || cub->map[y - 1][x].value == 'E'))
			ft_error(cub, "Invalid map 17", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y][x + 1].value == '0' || cub->map[y][x + 1].value == 'N' || cub->map[y][x + 1].value == 'S' || cub->map[y][x + 1].value == 'W' || cub->map[y][x + 1].value == 'E'))
			ft_error(cub, "Invalid map 18", y, x);
	}
}

void	ft_check_sides_2(t_cub *cub, size_t y, size_t x)
{
	if (y == cub->parse->map_height - 1 && x > 0 && x < cub->parse->map_width - 1)
	{
		if (cub->map[y][x].value == ' ' && (cub->map[y - 1][x].value == '0' || cub->map[y - 1][x].value == 'N' || cub->map[y - 1][x].value == 'S' || cub->map[y - 1][x].value == 'W' || cub->map[y - 1][x].value == 'E'))
			ft_error(cub, "Invalid map 19", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y][x + 1].value == '0' || cub->map[y][x + 1].value == 'N' || cub->map[y][x + 1].value == 'S' || cub->map[y][x + 1].value == 'W' || cub->map[y][x + 1].value == 'E'))
			ft_error(cub, "Invalid map 20", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y][x - 1].value == '0' || cub->map[y][x - 1].value == 'N' || cub->map[y][x - 1].value == 'S' || cub->map[y][x - 1].value == 'W' || cub->map[y][x - 1].value == 'E'))
			ft_error(cub, "Invalid map 21", y, x);
	}
	if (x == cub->parse->map_width - 1 && y > 0 && y < cub->parse->map_height - 1)
	{
		if (cub->map[y][x].value == ' ' && (cub->map[y + 1][x].value == '0' || cub->map[y + 1][x].value == 'N' || cub->map[y + 1][x].value == 'S' || cub->map[y + 1][x].value == 'W' || cub->map[y + 1][x].value == 'E'))
			ft_error(cub, "Invalid map 21", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y - 1][x].value == '0' || cub->map[y - 1][x].value == 'N' || cub->map[y - 1][x].value == 'S' || cub->map[y - 1][x].value == 'W' || cub->map[y - 1][x].value == 'E'))
			ft_error(cub, "Invalid map 22", y, x);
		if (cub->map[y][x].value == ' ' && (cub->map[y][x - 1].value == '0' || cub->map[y][x - 1].value == 'N' || cub->map[y][x - 1].value == 'S' || cub->map[y][x - 1].value == 'W' || cub->map[y][x - 1].value == 'E'))
			ft_error(cub, "Invalid map 23", y, x);
	}
}

int	ft_verif_right(t_cub *cub, size_t y, size_t x)
{
	if (x + 1 < cub->parse->map_width && cub->map[y][x + 1].value != '\0' && cub->map[y][x + 1].value == '1' && cub->map[y][x + 1].used == false && cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y, x + 1) == 0)
			return (0);
	}
	return (1);
}
int	ft_verif_down(t_cub *cub, size_t y, size_t x)
{
	if (y + 1 < cub->parse->map_height && cub->map[y + 1][x].value != '\0' && cub->map[y + 1][x].value == '1' && cub->map[y + 1][x].used == false && cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y + 1, x) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_left(t_cub *cub, size_t y, size_t x)
{
	if (x > 0 && cub->map[y][x].value == '1' && cub->map[y][x - 1].value == '1' && cub->map[y][x - 1].used == false && cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y, x - 1) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_up(t_cub *cub, size_t y, size_t x)
{
	if (y > 0 && cub->map[y][x].value == '1' && cub->map[y - 1][x].value == '1' && cub->map[y - 1][x].used == false && cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y - 1, x) == 0)
			return (0);
	}
	return (1);
}

int	ft_check_map_direction(t_cub *cub, size_t y, size_t x)
{
    if (ft_verif_right(cub, y, x) == 0)
		return (0);
	if (ft_verif_down(cub, y, x) == 0)
		return (0);
	if (ft_verif_left(cub, y, x) == 0)
		return (0);
	if (ft_verif_up(cub, y, x) == 0)
		return (0);
	return (1);
}

void	ft_count(t_cub *cub, size_t y, size_t x, char value)
{
	if (x + 1 < cub->parse->map_width && cub->map[y][x + 1].value == value && cub->map[y][x + 1].used == false)
	{
		if (value == '1')
			cub->map[y][x].count++;
		else if (value == '0')
			cub->map[y][x].count_0++;
	}
	if (y + 1 < cub->parse->map_height && cub->map[y + 1][x].value == value && cub->map[y + 1][x].used == false)
	{
		if (value == '1')
			cub->map[y][x].count++;
		else if (value == '0')
			cub->map[y][x].count_0++;
	}
	if (x > 0 && cub->map[y][x - 1].value == value && cub->map[y][x - 1].count == 0 && cub->map[y][x - 1].used == false)
	{
		if (value == '1')
			cub->map[y][x].count++;
		else if (value == '0')
			cub->map[y][x].count_0++;
	}
	if (y > 0 && cub->map[y - 1][x].value == value && cub->map[y - 1][x].count == 0 && cub->map[y - 1][x].used == false)
	{
		if (value == '1')
			cub->map[y][x].count++;
		else if (value == '0')
			cub->map[y][x].count_0++;
	}
}

int	ft_check_arround_1(t_cub *cub, size_t y, size_t x)
{
	cub->map[y][x].used = true;
	ft_count(cub, y, x, '0');
	ft_count(cub, y, x, '1');
	if (cub->map[y][x].count_0 != 0)
		return (0);
	if (ft_check_map_direction(cub, y, x) == 0)
		return (0);
	else
		return (1);
}

void	ft_reset_map(t_cub *cub)
{
	size_t y;
	size_t x;

	y = 0;
	while (y < cub->parse->map_height)
	{
		x = 0;
		while (x < cub->parse->map_width)
		{
			cub->map[y][x].used = false;
			cub->map[y][x].count = 0;
			cub->map[y][x].count_0 = 0;
			x++;
		}
		y++;
	}
}

void	ft_print_used(t_cub *cub)
{
	size_t y;
	size_t x;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x].value)
		{
			printf("%d", cub->map[y][x].used);
			x++;
		}
		printf ("\n");
		y++;
	}
}

void	ft_check_borders(t_cub *cub)
{
    size_t y;
    size_t x;

    y = 0;
    while (y < cub->parse->map_height)
    {
        x = 0;
        while (x < cub->parse->map_width)
        {
			if (cub->map[y][x].value == '1')
			{
				ft_reset_map(cub);
				if(ft_check_arround_1(cub, y, x) == 1)
					ft_error(cub, "Walls alone", y, x);
			}
			// printf("\n");
            if (y == 0 || x == 0 || y == cub->parse->map_height - 1 || x == cub->parse->map_width - 1)
			{
				// printf("Borders -> [%zu][%zu] = %c\n", y, x, cub->map[y][x].value);
				if (cub->map[y][x].value != '1' && cub->map[y][x].value != ' ')
					ft_error(cub, "Invalid map 0", y, x);
				ft_check_corners_1(cub, y, x);
				ft_check_corners_2(cub, y, x);
				ft_check_sides_1(cub, y, x);
				ft_check_sides_2(cub, y, x);
			}
            x++;
        }
        y++;
    }
}

void ft_get_player(t_cub *cub, size_t y, size_t x)
{
	if (cub->map[y][x].value == 'N' || cub->map[y][x].value == 'S' || cub->map[y][x].value == 'W' || cub->map[y][x].value == 'E')
	{
		if (cub->player->y_start != 0 || cub->player->x_start != 0 || cub->player->dir != 0)
			ft_error(cub, "Invalid map already a player", -1, -1);
		cub->player->dir = cub->map[y][x].value;
		cub->player->y_start = y;
		cub->player->x_start = x;
		cub->player->y_cur = y;
		cub->player->x_cur = x;
	}
	if (y == cub->parse->map_height - 2 && x == cub->parse->map_width - 2 && cub->player->dir == 0)
		ft_error(cub, "No player", -1, -1);
}

void	ft_check_if_valid_map(t_cub *cub)
{
    size_t y;
    size_t x;

    y = 1;
    while (y < cub->parse->map_height - 1)
    {
        x = 1;
        while (x < cub->parse->map_width - 1)
        {
			ft_get_player(cub, y, x);
            if (cub->map[y][x].value == ' ' && cub->map[y][x].used == false)
			{
				// printf("inside -> [%zu][%zu] = %c\n", y, x, cub->map[y][x].value);
				ft_check_inside(cub, y, x);
			}
            x++;
        }
        y++;
    }
}

// void	ft_verif_textures(t_cub *cub, char *to_check)
// {
// 	int	i;
// 	int	count_1;
// 	int	count_2;

// 	i = 0;
// 	count_1 = 0;
// 	count_2 = 0;
// 	while (to_check[i])
// 	{
// 		if (to_check[i] == '/')
// 			count_1++;
// 		if (to_check[i] == '.')
// 			count_2++;
// 		if (count_1 > 2)
// 			ft_error(cub, "Invalid texture", -1, -1);
// 		if (to_check[i] == '.' && count_1 != 2)
// 			ft_error(cub, "Invalid texture", -1, -1);
// 		i++;
// 	}
// 	if (count_1 != 2 || count_2 != 1)
// 		ft_error(cub, "Invalid texture", -1, -1);
// }

void ft_check_data(t_cub *cub)
{
	if (!cub->parse->NO || !cub->parse->SO || \
	!cub->parse->WE || !cub->parse->EA || \
	cub->parse->C.r <= -1 || cub->parse->C.g <= -1 || \
	cub->parse->C.b <= -1|| cub->parse->F.r <= -1 || \
	cub->parse->F.g <= -1 || cub->parse->F.b <= -1)
		ft_error(cub, "Missing data", -1, -1);
	// ft_verif_textures(cub, cub->parse->NO);
	// ft_verif_textures(cub, cub->parse->SO);
	// ft_verif_textures(cub, cub->parse->WE);
	// ft_verif_textures(cub, cub->parse->EA);
}

t_cell **ft_verif_data(t_cub *cub, t_cell **map)
{
	ft_check_borders(cub);
	ft_check_if_valid_map(cub);
    return (map);
}

// Vérifie si la ligne est valide (1, 0 , N, S, W, E)
int	ft_check_line(t_cub *cub, char *line)
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	ft_check_data(cub);
	while (line[i])
	{
		if (!ft_is_delimiter(line[i]) && line[i] != '1' \
			&& line[i] != '0' && line[i] != 'N' && line[i] \
			!= 'S' && line[i] != 'W' && line[i] != 'E')
		{
			ft_error(cub, "Invalid map", line[i], -1);
			exit(1);
		}
		if (line[i] == ' ' || line[i] == '1' || line[i] == 'N' || line[i] \
			== 'S' || line[i] == 'W' || line[i] == 'E')
			check = 1;
		i++;
	}
	// printf("\n");
	if (check == 1)
		return (1);
	return (0);
}