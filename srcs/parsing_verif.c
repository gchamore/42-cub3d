/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:22:42 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/14 14:22:36 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Vérifie si la map est bien fermee algo en cours de creation
int ft_check_if_valid_map(t_cub *cub, int **check, size_t x, size_t y)
{
	if (!cub || !cub->parse || x >= cub->parse->map_height || y >= cub->parse->map_width)
        return (0);
	if (check[x][y] == 1)
		return (0);
	check[x][y] = 1;
	// printf("check[%zu][%zu] = %d\n", x, y, check[x][y]);
	if (cub->map[x][y].value != '1')
        return (ft_error(cub, "Invalid map", cub->map[x][y].value), 1);
	else if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value != '\0' && cub->map[x][y + 1].value == '1')
	{
		printf("[%zu][%zu] y++\n", x, y);
		ft_check_if_valid_map(cub, check, x, y + 1);
	}
	else if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value != '\0' && cub->map[x + 1][y].value == '1')
	{
		printf("[%zu][%zu] x++\n", x, y);
		ft_check_if_valid_map(cub, check, x + 1, y);
	}
	else if (y > 0 && cub->map[x][y].value == '1' && cub->map[x][y - 1].value == '1')
	{
		printf("[%zu][%zu] y--\n", x, y);
		ft_check_if_valid_map(cub, check, x, y - 1);
	}
	else if (x > 0 && cub->map[x][y].value == '1' && cub->map[x - 1][y].value == '1')
	{
		printf("[%zu][%zu] x--\n", x, y);
		ft_check_if_valid_map(cub, check, x - 1, y);
	}
	else
		return (ft_error(cub, "Invalid map", cub->map[x][y].value), 1);
	return (0);
}

// Vérifie si la map est bien fermee
t_cell **ft_verif_map(t_cub *cub, t_cell **map)
{
    size_t x;
    size_t y;
	int		**check;

    x = 0;
	printf ("map_height = %zu\n", cub->parse->map_height);
	printf ("map_width = %zu\n", cub->parse->map_width);
	check = (int **)malloc(sizeof(int *) * (cub->parse->map_height));
	if (!check)
		return (NULL);
    while (map[x] && x < cub->parse->map_height)
    {
        y = 0;
		check[x] = (int *)malloc(sizeof(int) * (cub->parse->map_width));
		if (!check[x])
        {
            while (x-- > 0)
                free(check[x]);
            free(check);
            return (NULL);
        }
		memset(check[x], 0, cub->parse->map_width * sizeof(int));
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
				// printf("[%zu][%zu] = %c\n", x, y, map[x][y]);
				if (ft_check_if_valid_map(cub, check, x, y) == 0)
					return (printf("YEAAAAAAH \n\n"), map);
				y++;
				continue ;
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