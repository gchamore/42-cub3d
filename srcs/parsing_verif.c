/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:22:42 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/03 18:33:47 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_valid(t_cub *cub, size_t y, size_t x)
{
	if (cub->map[y][x].value == '0' || cub->map[y][x].value == 'N' || \
	cub->map[y][x].value == 'S' || cub->map[y][x].value == 'W' || \
	cub->map[y][x].value == 'E')
		return (1);
	return (0);
}

void	ft_check_inside(t_cub *cub, size_t y, size_t x)
{
	if (ft_is_valid(cub, y + 1, x) == 1)
		ft_error(cub, "Invalid map wrong value arround", y, x);
	else if (ft_is_valid(cub, y - 1, x) == 1)
		ft_error(cub, "Invalid map wrong value arround", y, x);
	else if (ft_is_valid(cub, y, x + 1) == 1)
		ft_error(cub, "Invalid map wrong value arround", y, x);
	else if (ft_is_valid(cub, y, x - 1) == 1)
		ft_error(cub, "Invalid map wrong value arround", y, x);
}

void	ft_check_corners_1(t_cub *cub, size_t y, size_t x)
{
	if (y == 0 && x == 0 && (cub->map[y][x].value == ' ' || \
	ft_is_valid(cub, y, x) == 1))
	{
		if (ft_is_valid(cub, y + 1, x) == 1 || ft_is_valid(cub, y, x + 1) == 1)
			ft_error(cub, "Invalid map wrong value arround corner", y, x);
	}
	if (y == cub->parse->map_height - 1 && x == cub->parse->map_width - 1 && \
	(cub->map[y][x].value == ' ' || ft_is_valid(cub, y, x) == 1))
	{
		if (ft_is_valid(cub, y - 1, x) == 1 || ft_is_valid(cub, y, x - 1) == 1)
			ft_error(cub, "Invalid map wrong value arround corner", y, x);
	}
}

void	ft_check_corners_2(t_cub *cub, size_t y, size_t x)
{
	if (y == 0 && x == cub->parse->map_width - 1 && \
	(cub->map[y][x].value == ' ' || ft_is_valid(cub, y, x) == 1))
	{
		if (ft_is_valid(cub, y + 1, x) == 1 || ft_is_valid(cub, y, x - 1) == 1)
			ft_error(cub, "Invalid map wrong value arround corner", y, x);
	}
	if (y == cub->parse->map_height - 1 && x == 0 && \
	(cub->map[y][x].value == ' ' || ft_is_valid(cub, y, x) == 1))
	{
		if (ft_is_valid(cub, y - 1, x) == 1 || ft_is_valid(cub, y, x + 1) == 1)
			ft_error(cub, "Invalid map wrong value arround corner", y, x);
	}
}

void	ft_check_sides_1(t_cub *cub, size_t y, size_t x)
{
	if (y == 0 && x > 0 && x < cub->parse->map_width - 1 && \
	(cub->map[y][x].value == ' ' || ft_is_valid(cub, y, x) == 1))
	{
		if ((ft_is_valid(cub, y + 1, x) == 1 || \
		ft_is_valid(cub, y, x + 1) == 1) || (ft_is_valid(cub, y, x - 1) == 1))
			ft_error(cub, "Invalid map wrong value arround up side", y, x);
	}
	if (x == 0 && y > 0 && y < cub->parse->map_height - 1 && \
	(cub->map[y][x].value == ' ' || ft_is_valid(cub, y, x) == 1))
	{
		if ((ft_is_valid(cub, y + 1, x) == 1 || \
		ft_is_valid(cub, y - 1, x) == 1) || (ft_is_valid(cub, y, x + 1) == 1))
			ft_error(cub, "Invalid map wrong value arround left side", y, x);
	}
}

void	ft_check_sides_2(t_cub *cub, size_t y, size_t x)
{
	if (y == cub->parse->map_height - 1 && x > 0 && \
		x < cub->parse->map_width - 1 && (cub->map[y][x].value == ' ' || \
		ft_is_valid(cub, y, x) == 1))
	{
		if ((ft_is_valid(cub, y - 1, x) == 1 || \
		ft_is_valid(cub, y, x + 1) == 1) || (ft_is_valid(cub, y, x - 1) == 1))
			ft_error(cub, "Invalid map wrong value arround down side", y, x);
	}
	if (x == cub->parse->map_width - 1 && y > 0 && \
	y < cub->parse->map_height - 1 && (cub->map[y][x].value == ' ' || \
	ft_is_valid(cub, y, x) == 1))
	{
		if ((ft_is_valid(cub, y + 1, x) == 1 || \
		ft_is_valid(cub, y - 1, x) == 1) || (ft_is_valid(cub, y, x - 1) == 1))
			ft_error(cub, "Invalid map wrong value arround right side", y, x);
	}
}

int	ft_verif_right(t_cub *cub, size_t y, size_t x)
{
	if (x + 1 < cub->parse->map_width && cub->map[y][x + 1].value != '\0' && \
	cub->map[y][x + 1].value == '1' && cub->map[y][x + 1].used == false && \
	cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y, x + 1) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_right_down(t_cub *cub, size_t y, size_t x)
{
	if (y + 1 < cub->parse->map_height && x + 1 < cub->parse->map_width && \
	cub->map[y + 1][x + 1].value != '\0' && cub->map[y + 1][x + 1].value == '1' && \
	cub->map[y + 1][x + 1].used == false && cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y + 1, x + 1) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_down(t_cub *cub, size_t y, size_t x)
{
	if (y + 1 < cub->parse->map_height && cub->map[y + 1][x].value != '\0' && \
	cub->map[y + 1][x].value == '1' && cub->map[y + 1][x].used == false && \
	cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y + 1, x) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_left_down(t_cub *cub, size_t y, size_t x)
{
	if (y + 1 < cub->parse->map_height && x > 0 && \
	cub->map[y + 1][x - 1].value == '1' && cub->map[y + 1][x - 1].used == false && \
	cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y + 1, x - 1) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_left(t_cub *cub, size_t y, size_t x)
{
	if (x > 0 && cub->map[y][x].value == '1' && \
	cub->map[y][x - 1].value == '1' && cub->map[y][x - 1].used == false && \
	cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y, x - 1) == 0)
			return (0);
	}
	return (1);
}

int ft_verif_left_up(t_cub *cub, size_t y, size_t x)
{
	if (y > 0 && x > 0 && cub->map[y - 1][x - 1].value == '1' && \
	cub->map[y - 1][x - 1].used == false && cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y - 1, x - 1) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_up(t_cub *cub, size_t y, size_t x)
{
	if (y > 0 && cub->map[y][x].value == '1' && \
	cub->map[y - 1][x].value == '1' && cub->map[y - 1][x].used == false && \
	cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y - 1, x) == 0)
			return (0);
	}
	return (1);
}

int ft_verif_right_up(t_cub *cub, size_t y, size_t x)
{
	if (y > 0 && x + 1 < cub->parse->map_width && \
	cub->map[y - 1][x + 1].value == '1' && cub->map[y - 1][x + 1].used == false && \
	cub->map[y][x].count >= 1)
	{
		cub->map[y][x].count--;
		if (ft_check_arround_1(cub, y - 1, x + 1) == 0)
			return (0);
	}
	return (1);
}

int	ft_check_map_direction(t_cub *cub, size_t y, size_t x)
{
	if (ft_verif_right(cub, y, x) == 0)
		return (0);
	if (ft_verif_right_down(cub, y, x) == 0)
		return (0);
	if (ft_verif_down(cub, y, x) == 0)
		return (0);
	if (ft_verif_left_down(cub, y, x) == 0)
		return (0);
	if (ft_verif_left(cub, y, x) == 0)
		return (0);
	if (ft_verif_left_up(cub, y, x) == 0)
		return (0);
	if (ft_verif_up(cub, y, x) == 0)
		return (0);
	if (ft_verif_right_up(cub, y, x) == 0)
		return (0);
	return (1);
}

int ft_check_diag(t_cub *cub, size_t y, size_t x)
{
	int	count;

	count = 0;
	if (y > 0 && x > 0 && cub->map[y - 1][x - 1].value == '1' && \
	cub->map[y - 1][x - 1].used == false)
		count++;
	if (y > 0 && x + 1 < cub->parse->map_width && \
	cub->map[y - 1][x + 1].value == '1' && cub->map[y - 1][x + 1].used == false)
		count++;
	if (y + 1 < cub->parse->map_height && x > 0 && \
	cub->map[y + 1][x - 1].value == '1' && cub->map[y + 1][x - 1].used == false)
		count++;
	if (y + 1 < cub->parse->map_height && x + 1 < cub->parse->map_width && \
	cub->map[y + 1][x + 1].value == '1' && cub->map[y + 1][x + 1].used == false)
		count++;
	return (count);
}

int	ft_count(t_cub *cub, size_t y, size_t x, char value)
{
	int	count;

	count = 0;
	if (x + 1 < cub->parse->map_width && cub->map[y][x + 1].value == value && \
		cub->map[y][x + 1].used == false)
		count++;
	if (y + 1 < cub->parse->map_height && cub->map[y + 1][x].value == value && \
		cub->map[y + 1][x].used == false)
		count++;
	if (x > 0 && cub->map[y][x - 1].value == value && \
		cub->map[y][x - 1].count == 0 && cub->map[y][x - 1].used == false)
		count++;
	if (y > 0 && cub->map[y - 1][x].value == value && \
		cub->map[y - 1][x].count == 0 && cub->map[y - 1][x].used == false)
		count++;
	if (value == '1')
		count += ft_check_diag(cub, y, x);
	return (count);
}

int	ft_check_arround_1(t_cub *cub, size_t y, size_t x)
{
	cub->map[y][x].used = true;
	cub->map[y][x].count_0 = ft_count(cub, y, x, '0');
	cub->map[y][x].count = ft_count(cub, y, x, '1');
	if (cub->map[y][x].count_0 != 0)
		return (0);
	if (ft_check_map_direction(cub, y, x) == 0)
		return (0);
	else
		return (1);
}

void	ft_reset_map(t_cub *cub)
{
	size_t	y;
	size_t	x;

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
	size_t	y;
	size_t	x;

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

void	ft_check_cell(t_cub *cub, size_t y, size_t x)
{
	if (cub->map[y][x].value == ' ')
	{
		if (ft_count(cub, y, x, '0') != 0 || ft_count(cub, y, x, 'N') != 0 || \
		ft_count(cub, y, x, 'S') != 0 || ft_count(cub, y, x, 'W') != 0 || \
		ft_count(cub, y, x, 'E') != 0)
			ft_error(cub, "Invalid 0,N,S,E,W Alone arround", y, x);
	}
}

void	ft_check_borders(t_cub *cub, size_t y, size_t x)
{
	while (y < cub->parse->map_height)
	{
		x = -1;
		while (++x < cub->parse->map_width)
		{
			ft_reset_map(cub);
			ft_check_cell(cub, y, x);
			if (cub->map[y][x].value == '1')
			{
				if (ft_check_arround_1(cub, y, x) == 1)
					ft_error(cub, "Invalid 1 Alone at", y, x);
			}
			if (y == 0 || x == 0 || y == cub->parse->map_height - 1 || \
			x == cub->parse->map_width - 1)
			{
				ft_check_corners_1(cub, y, x);
				ft_check_corners_2(cub, y, x);
				ft_check_sides_1(cub, y, x);
				ft_check_sides_2(cub, y, x);
				if (cub->map[y][x].value != '1' && cub->map[y][x].value != ' ')
					ft_error(cub, "Invalid map 0 at", y, x);
			}
		}
		y++;
	}
}

void	ft_get_player(t_cub *cub, size_t y, size_t x)
{
	if (cub->map[y][x].value == 'N' || cub->map[y][x].value == 'S' || \
	cub->map[y][x].value == 'W' || cub->map[y][x].value == 'E')
	{
		if (cub->player->y_start != 0 || cub->player->x_start != 0 || \
		cub->player->dir != 0)
			ft_error(cub, "Invalid map to much players", -1, -1);
		cub->player->dir = cub->map[y][x].value;
		cub->player->y_start = y;
		cub->player->x_start = x;
		cub->player->y_cur = y;
		cub->player->x_cur = x;
	}
	if (y == cub->parse->map_height - 2 && x == cub->parse->map_width - 2 && \
	cub->player->dir == 0)
		ft_error(cub, "No player", -1, -1);
}

void	ft_check_if_valid_map(t_cub *cub)
{
	size_t	y;
	size_t	x;

	y = 1;
	while (y < cub->parse->map_height - 1)
	{
		x = 1;
		while (x < cub->parse->map_width - 1)
		{
			ft_get_player(cub, y, x);
			if (cub->map[y][x].value == ' ' && cub->map[y][x].used == false)
				ft_check_inside(cub, y, x);
			x++;
		}
		y++;
	}
}

void	ft_check_data(t_cub *cub, char *line)
{
	if (!cub->parse->NO || !cub->parse->SO || \
	!cub->parse->WE || !cub->parse->EA || \
	cub->parse->C.r <= -1 || cub->parse->C.g <= -1 || \
	cub->parse->C.b <= -1 || cub->parse->F.r <= -1 || \
	cub->parse->F.g <= -1 || cub->parse->F.b <= -1)
	{
		free(line);
		ft_error(cub, "Missing data", -1, -1);
	}
}

t_cell	**ft_verif_data(t_cub *cub, t_cell **map)
{
	ft_check_borders(cub, 0, 0);
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
	ft_check_data(cub, line);
	while (line[i])
	{
		if (!ft_is_delimiter(line[i]) && line[i] != '1' \
			&& line[i] != '0' && line[i] != 'N' && line[i] \
			!= 'S' && line[i] != 'W' && line[i] != 'E')
		{
			// printf ("line = %s\n", line);
			free(line);
			ft_error(cub, "Invalid Cell", -1, -1);
		}
		if (line[i] == ' ' || line[i] == '1' || line[i] == 'N' || line[i] \
			== 'S' || line[i] == 'W' || line[i] == 'E' || line[i] == '0')
			check = 1;
		i++;
	}
	if (check == 1)
		return (1);
	return (0);
}
