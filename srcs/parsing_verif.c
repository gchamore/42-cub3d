/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:22:42 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/16 16:51:55 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_count_1(t_cub *cub, size_t x, size_t y)
{
	if (cub->map[x][y].value == '1')
	{
		if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == false)
			cub->map[x][y].count++;
		if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == false)
			cub->map[x][y].count++;
		if (y > 0 && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].count == 0 && cub->map[x][y - 1].used == false)
			cub->map[x][y].count++;
		if (x > 0 && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].count == 0 && cub->map[x - 1][y].used == false)
			cub->map[x][y].count++;
	}	
}

int	ft_check_end(t_cub *cub, size_t x, size_t y)
{
	int i;

	i = 0;
	if (cub->map[x][y].value == '1')
	{
		if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == true && cub->map[x][y + 1].end == true)
			return (printf("map = [%zu][%zu]\n", x, y + 1), 0);
		if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == true && cub->map[x + 1][y].end == true)
			return (printf("map = [%zu][%zu]\n", x + 1, y), 0);
		if (y > 0 && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].used == true && cub->map[x][y - 1].end == true)
			return (printf("map = [%zu][%zu]\n", x, y - 1), 0);
		if (x > 0 && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].used == true && cub->map[x - 1][y].end == true)
			return (printf("map = [%zu][%zu]\n", x - 1, y), 0);
	}
	return (1);
}

// Vérifie si la map est bien fermee algo en cours de creation
int ft_check_if_valid_map(t_cub *cub, size_t x, size_t y)
{
	if (!cub || !cub->parse || x >= cub->parse->map_height || y >= cub->parse->map_width)
        return (0);
	cub->check++;
	if (cub->map[x][y].value != '1' || cub->check == 0)
        return (ft_error(cub, "Invalid map", cub->map[x][y].value), 1);
	printf("map = [%zu][%zu]\n", x, y);
	cub->map[x][y].used = true;
	ft_count_1(cub, x, y);
	if (cub->map[x][y].count == 0)
	{
		if (ft_check_end(cub, x, y) == 0 && cub->check >= 4)
			return (printf("THE END !"), 0);
		else
			return (1);
	}
	if (ft_check_end(cub, x, y) == 0 && cub->check >= 4)
			return (printf("THE END !"), 0);
    if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value != '\0' && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == false && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if ((x > 0 && cub->map[x - 1][y].value == '0'))
		{
			printf("\nUnvalid path at [%zu][%zu]\n\n", x, y);
			return (1);
		}
		if (ft_check_if_valid_map(cub, x, y + 1) == 0)
			return (0);
		else
		{
			cub->check--;
			printf("go back at -> [%zu][%zu]\n", x, y + 1);
		}	
	}
    if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value != '\0' && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == false && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if ((y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == '0'))
		{
			printf("\nUnvalid path at [%zu][%zu]\n\n", x, y);
			return (1);
		}
		if (ft_check_if_valid_map(cub, x + 1, y) == 0)
			return (0);
		else
		{
			cub->check--;
			printf("go back at -> [%zu][%zu]\n", x + 1, y);
		}	
	}
    if (y > 0 && cub->map[x][y].value == '1' && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].used == false && cub->map[x][y].count >= 1 && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if ((x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == '0'))
		{
			printf("\nUnvalid path at [%zu][%zu]\n\n", x, y);
			return (1);
		}
		if (ft_check_if_valid_map(cub, x, y - 1) == 0)
			return (0);
		else
		{
			cub->check--;
			printf("go back at -> [%zu][%zu]\n", x, y - 1);
		}	
	}
    if (x > 0 && cub->map[x][y].value == '1' && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].used == false && cub->map[x][y].count >= 1 && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if ((y > 0 && cub->map[x][y - 1].value == '0'))
		{
			printf("\nUnvalid path at [%zu][%zu]\n\n", x, y);
			return (1);
		}
		if (ft_check_if_valid_map(cub, x - 1, y) == 0)
			return (0);
		else
		{
			cub->check--;
			printf("go back at -> [%zu][%zu]\n", x - 1, y);
		}
	}
	return (1);
}

// Vérifie si la map est bien fermee
t_cell **ft_verif_map(t_cub *cub, t_cell **map)
{
    size_t x;
    size_t y;

    x = 0;
	printf ("map_height = %zu\n", cub->parse->map_height);
	printf ("map_width = %zu\n", cub->parse->map_width);
    while (map[x] && x < cub->parse->map_height)
    {
        y = 0;
        while (map[x][y].value && y < cub->parse->map_width)
        {
			if (map[x][y].value == ' ')
			{
				// printf("[%zu][%zu] = %c\n", x, y, map[x][y]);
				y++;
				continue ;
			}
			if (map[x][y].value == '1')
			{
				ft_count_1(cub, x, y);
				if (cub->map[x][y].count == 1)
				{
					y++;
					cub->map[x][y].used = true;
					continue;
				}
				cub->map[x][y].count = 0;
				cub->map[x][y].end = true;
				if (ft_check_if_valid_map(cub, x, y) == 0)
					return (printf("YEAAAAAAH \n\n"), map);
				else
					return (printf("NOOOOO \n\n"), NULL);
			}
            y++;
        }
		printf("\n\n");
        x++;
    }
    return (map);
}

// Vérifie si la ligne est valide (1, 0 , N, S, W, E)
int	ft_check_line(t_cub *cub, char *line)
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	while (line[i])
	{
		if (!ft_is_delimiter(line[i]) && line[i] != '1' \
			&& line[i] != '0' && line[i] != 'N' && line[i] \
			!= 'S' && line[i] != 'W' && line[i] != 'E')
		{
			ft_error(cub, "Invalid map", line[i]);
			exit(1);
		}
		if (line[i] == '1' || line[i] == 'N' || line[i] \
			== 'S' || line[i] == 'W' || line[i] == 'E')
			check = 1;
		i++;
	}
	if (check == 1)
		return (1);
	return (0);
}