/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:22:42 by gchamore          #+#    #+#             */
/*   Updated: 2024/07/19 12:43:45 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_check_close_map(t_cub *cub, char **map, int x, int y)
{
	if (x == 0 || y == 0 || !map[x + 1] || !map[x][y + 1])
		ft_error(cub, "Invalid walls", map[x][y]);
	if (map[x - 1][y] != '1' && map[x + 1][y] != '1' && map[x][y - 1] != '1' && map[x][y + 1] != '1')
		ft_error(cub, "Invalid walls", map[x][y]);
	return (1);
}

char **ft_verif_map(t_cub *cub, char **map)
{
    int x;
    int y;

    x = 0;
    while (map[x])
    {
        y = 0;
        while (map[x][y])
        {
            if (map[x][y] == '1')
            {
                ft_check_close_map(cub, map, x, y);
            }
            y++;
        }
        x++;
    }
    return (map);
}

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