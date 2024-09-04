/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:39:56 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 16:34:54 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_prepare(t_cub *cub, char *line, size_t j)
{
	if (j < cub->parse->total_infos)
	{
		if (line[0] == '\n')
			cub->parse->total_newline--;
	}
	else if (j < (cub->parse->total_height - cub->parse->total_newline))
	{
		if (line[0] == '\n')
		{
			free(line);
			line = malloc((cub->parse->map_width + 1) * sizeof(char));
			if (!line)
				ft_error(cub, "Line Alloc failed", -1, -1);
			memset(line, ' ', cub->parse->map_width);
			line[cub->parse->map_width] = '\0';
		}
		ft_fill_map(cub, line, NULL, j);
	}
}

void	ft_fill_map(t_cub *cub, char *line, char **split, size_t j)
{
	size_t	x;
	size_t	y;

	y = (j - cub->parse->total_infos);
	if (ft_check_line(cub, line) == 1)
	{
		x = -1;
		split = ft_mod_split(line, cub, 0, 0);
		if (split == NULL)
		{
			free(line);
			ft_error(cub, "Split Alloc failed", -1, -1);
		}
		cub->map[y] = malloc(sizeof(t_cell) * (cub->parse->map_width + 1));
		if (!cub->map[y])
		{
			free(line);
			ft_error(cub, "Map Alloc failed", -1, -1);
		}
		while (++x < cub->parse->map_width)
			ft_init_map(cub, y, x, *split[x]);
		ft_init_map(cub, y, x, '\0');
		ft_free_split(split);
		y++;
	}
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

void	ft_check_data(t_cub *cub, char *line)
{
	if (!cub->parse->NO || !cub->parse->SO || \
	!cub->parse->WE || !cub->parse->EA || \
	cub->parse->C.r <= -1 || cub->parse->C.g <= -1 || \
	cub->parse->C.b <= -1 || cub->parse->F.r <= -1 || \
	cub->parse->F.g <= -1 || cub->parse->F.b <= -1)
	{
		free(line);
		ft_error(cub, "Wrong data infos", -1, -1);
	}
	if (cub->parse->C.r > 255 || cub->parse->C.g > 255 || \
	cub->parse->C.b > 255 || cub->parse->F.r > 255 || \
	cub->parse->F.g > 255 || cub->parse->F.b > 255)
	{
		free(line);
		ft_error(cub, "Invalid RGB too high value", -1, -1);
	}
}
