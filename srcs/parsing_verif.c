/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:22:42 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/22 14:17:57 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_inside(t_cub *cub, size_t x, size_t y)
{
	if (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E')
		ft_error(cub, "Invalid map 1", x, y);
	else if (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E')
		ft_error(cub, "Invalid map 2", x, y);
	else if (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E')
		ft_error(cub, "Invalid map 3", x, y);
	else if (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E')
		ft_error(cub, "Invalid map 4", x, y);
}
void	ft_check_corners_1(t_cub *cub, size_t x, size_t y)
{
	if (x == 0 && y == 0)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E'))
			ft_error(cub, "Invalid map 5", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E'))
			ft_error(cub, "Invalid map 6", x, y);
	}
	if (x == cub->parse->map_height - 1 && y == cub->parse->map_width - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E'))
			ft_error(cub, "Invalid map 7", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E'))
			ft_error(cub, "Invalid map 8", x, y);
	}
}
void	ft_check_corners_2(t_cub *cub, size_t x, size_t y)
{
	if (x == 0 && y == cub->parse->map_width - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E'))
			ft_error(cub, "Invalid map 9", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E'))
			ft_error(cub, "Invalid map 10", x, y);
	}
	if (x == cub->parse->map_height - 1 && y == 0)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E'))
			ft_error(cub, "Invalid map 11", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E'))
			ft_error(cub, "Invalid map 12", x, y);
	}
}

void	ft_check_sides_1(t_cub *cub, size_t x, size_t y)
{
	if (x == 0 && y > 0 && y < cub->parse->map_width - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E'))
			ft_error(cub, "Invalid map 13", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E'))
			ft_error(cub, "Invalid map 14", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E'))
			ft_error(cub, "Invalid map 15", x, y);
	}
	if (y == 0 && x > 0 && x < cub->parse->map_height - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E'))
			ft_error(cub, "Invalid map 16", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E'))
			ft_error(cub, "Invalid map 17", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E'))
			ft_error(cub, "Invalid map 18", x, y);
	}
}

void	ft_check_sides_2(t_cub *cub, size_t x, size_t y)
{
	if (x == cub->parse->map_height - 1 && y > 0 && y < cub->parse->map_width - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E'))
			ft_error(cub, "Invalid map 19", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E'))
			ft_error(cub, "Invalid map 20", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E'))
			ft_error(cub, "Invalid map 21", x, y);
	}
	if (y == cub->parse->map_width - 1 && x > 0 && x < cub->parse->map_height - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E'))
			ft_error(cub, "Invalid map 21", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E'))
			ft_error(cub, "Invalid map 22", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E'))
			ft_error(cub, "Invalid map 23", x, y);
	}
}

int	ft_verif_right(t_cub *cub, size_t x, size_t y)
{
	if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value != '\0' && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == false && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if (ft_check_arround_1(cub, x, y + 1) == 0)
			return (0);
	}
	return (1);
}
int	ft_verif_down(t_cub *cub, size_t x, size_t y)
{
	if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value != '\0' && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == false && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if (ft_check_arround_1(cub, x + 1, y) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_left(t_cub *cub, size_t x, size_t y)
{
	if (y > 0 && cub->map[x][y].value == '1' && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].used == false && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if (ft_check_arround_1(cub, x, y - 1) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_up(t_cub *cub, size_t x, size_t y)
{
	if (x > 0 && cub->map[x][y].value == '1' && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].used == false && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if (ft_check_arround_1(cub, x - 1, y) == 0)
			return (0);
	}
	return (1);
}

int	ft_check_map_direction(t_cub *cub, size_t x, size_t y)
{
    if (ft_verif_right(cub, x, y) == 0)
		return (0);
	if (ft_verif_down(cub, x, y) == 0)
		return (0);
	if (ft_verif_left(cub, x, y) == 0)
		return (0);
	if (ft_verif_up(cub, x, y) == 0)
		return (0);
	return (1);
}

void	ft_count(t_cub *cub, size_t x, size_t y, char value)
{
	if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == value && cub->map[x][y + 1].used == false)
	{
		if (value == '1')
			cub->map[x][y].count++;
		else if (value == '0')
			cub->map[x][y].count_0++;
	}
	if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == value && cub->map[x + 1][y].used == false)
	{
		if (value == '1')
			cub->map[x][y].count++;
		else if (value == '0')
			cub->map[x][y].count_0++;
	}
	if (y > 0 && cub->map[x][y - 1].value == value && cub->map[x][y - 1].count == 0 && cub->map[x][y - 1].used == false)
	{
		if (value == '1')
			cub->map[x][y].count++;
		else if (value == '0')
			cub->map[x][y].count_0++;
	}
	if (x > 0 && cub->map[x - 1][y].value == value && cub->map[x - 1][y].count == 0 && cub->map[x - 1][y].used == false)
	{
		if (value == '1')
			cub->map[x][y].count++;
		else if (value == '0')
			cub->map[x][y].count_0++;
	}
}

int	ft_check_arround_1(t_cub *cub, size_t x, size_t y)
{
	cub->map[x][y].used = true;
	ft_count(cub, x, y, '0');
	ft_count(cub, x, y, '1');
	if (cub->map[x][y].count_0 != 0)
		return (0);
	if (ft_check_map_direction(cub, x, y) == 0)
		return (0);
	else
		return (1);
}

void	ft_reset_map(t_cub *cub)
{
	size_t x;
	size_t y;

	x = 0;
	while (x < cub->parse->map_height)
	{
		y = 0;
		while (y < cub->parse->map_width)
		{
			cub->map[x][y].used = false;
			cub->map[x][y].count = 0;
			cub->map[x][y].count_0 = 0;
			y++;
		}
		x++;
	}
}

void	ft_print_used(t_cub *cub)
{
	size_t x;
	size_t y;

	x = 0;
	while (cub->map[x])
	{
		y = 0;
		while (cub->map[x][y].value)
		{
			printf("%d", cub->map[x][y].used);
			y++;
		}
		printf ("\n");
		x++;
	}
}

void	ft_check_borders(t_cub *cub)
{
    size_t x;
    size_t y;

    x = 0;
    while (x < cub->parse->map_height)
    {
        y = 0;
        while (y < cub->parse->map_width)
        {
			if (cub->map[x][y].value == '1')
			{
				ft_reset_map(cub);
				cub->exit_map = 2;
				if(ft_check_arround_1(cub, x, y) == 1)
					ft_error(cub, "Walls alone", x, y);
			}
			// printf("\n");
            if (x == 0 || y == 0 || x == cub->parse->map_height - 1 || y == cub->parse->map_width - 1)
			{
				// printf("Borders -> [%zu][%zu] = %c\n", x, y, cub->map[x][y].value);
				if (cub->map[x][y].value != '1' && cub->map[x][y].value != ' ')
					ft_error(cub, "Invalid map 0", x, y);
				ft_check_corners_1(cub, x, y);
				ft_check_corners_2(cub, x, y);
				ft_check_sides_1(cub, x, y);
				ft_check_sides_2(cub, x, y);
			}
            y++;
        }
        x++;
    }
}

void ft_get_player(t_cub *cub, size_t x, size_t y)
{
	if (cub->map[x][y].value == 'N' || cub->map[x][y].value == 'S' || cub->map[x][y].value == 'W' || cub->map[x][y].value == 'E')
	{
		if (cub->player->x_start != 0 || cub->player->y_start != 0 || cub->player->dir != 0)
			ft_error(cub, "Invalid map already a player", -1, -1);
		cub->player->dir = cub->map[x][y].value;
		cub->player->x_start = x;
		cub->player->y_start = y;
		cub->player->x_cur = x;
		cub->player->y_cur = y;
	}
	if (x == cub->parse->map_height - 2 && y == cub->parse->map_width - 2 && cub->player->dir == 0)
		ft_error(cub, "No player", -1, -1);
}

void	ft_check_if_valid_map(t_cub *cub)
{
    size_t x;
    size_t y;

    x = 1;
    while (x < cub->parse->map_height - 1)
    {
        y = 1;
        while (y < cub->parse->map_width - 1)
        {
			ft_get_player(cub, x, y);
            if (cub->map[x][y].value == ' ' && cub->map[x][y].used == false)
			{
				// printf("inside -> [%zu][%zu] = %c\n", x, y, cub->map[x][y].value);
				ft_check_inside(cub, x, y);
			}
            y++;
        }
        x++;
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