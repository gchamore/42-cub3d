/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:00 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/03 19:46:56 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_parsing(t_cub *cub, char **argv)
{
	if (ft_get_data(argv[1], cub, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_fill_all(argv[1], cub) == NULL)
		return (EXIT_FAILURE);
	ft_verif_data(cub, cub->map);
	return (EXIT_SUCCESS);
}

int	ft_checker(char *line, char one, char two)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == one)
		{
			if (two == '\0')
				return (1);
			else
			{
				if (line[i + 1] == two)
					return (1);
				else
				{
					i++;
					continue ;
				}
			}
		}
		i++;
	}
	return (0);
}

void	verif_if_double_and_valid(t_cub *cub, char *line)
{
	if (line[0] != '\n' && line[0] != '\0' && !ft_strchr(line, '1') && \
	!ft_strchr(line, '0') && !ft_strchr(line, 'N') && !ft_strchr(line, 'S') \
	&& !ft_strchr(line, 'W') && !ft_strchr(line, 'E') && !ft_strchr(line, 'F') \
	&& !ft_strchr(line, 'C'))
	{
		free(line);
		ft_error(cub, "wrong data", -1, -1);
	}
	else if (ft_checker(line, 'N', 'O') == 1 && cub->parse->ct <= 6)
		cub->verif.NO++;
	else if (ft_checker(line, 'S', 'O') == 1 && cub->parse->ct <= 6)
		cub->verif.SO++;
	else if (ft_checker(line, 'W', 'E') == 1 && cub->parse->ct <= 6)
		cub->verif.WE++;
	else if (ft_checker(line, 'E', 'A') == 1 && cub->parse->ct <= 6)
		cub->verif.EA++;
	else if (ft_checker(line, 'F', '\0') == 1 && cub->parse->ct <= 6)
		cub->verif.F++;
	else if (ft_checker(line, 'C', '\0') == 1 && cub->parse->ct <= 6)
		cub->verif.C++;
}

void	verif_fill_data(t_cub *cub, char *line, int i)
{
	verif_if_double_and_valid(cub, line);
	while (line[i] && cub->parse->ct != 7)
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (cub->parse->ct < 6 && (line[i] == '1' || line[i] == '0' || \
		(line[i] == 'N' && line[i + 1] != 'O') || (line[i] == 'S' && \
		line[i + 1] != 'O') || (line[i] == 'W' && line[i + 1] != 'E') || \
		(line[i] == 'E' && line[i + 1] != 'A')))
		{
			free(line);
			ft_error(cub, "Invalid data", -1, -1);
		}
		else if (cub->parse->ct == 6 && (line[i] == '1' || line[i] == '0' || \
		(line[i] == 'N' && line[i + 1] != 'O') || (line[i] == 'S' && \
		line[i + 1] != 'O') || (line[i] == 'W' && line[i + 1] != 'E') || \
		(line[i] == 'E' && line[i + 1] != 'A')))
		{
			cub->parse->total_infos = cub->parse->total_height;
			cub->parse->ct = 7;
		}
		else
			break ;
	}
}

//Recupere les datas : NO, SO, WE, EA, F, C, map
int	ft_get_data(char *file, t_cub *cub, char *line)
{
	cub->fd = open(file, O_RDONLY);
	if (cub->fd == -1)
		return (ft_error(cub, "Invalid fd", -1, -1), EXIT_FAILURE);
	line = ft_get_next_line(cub->fd);
	if (!line)
		return (ft_error(cub, "NULL line", -1, -1), EXIT_FAILURE);
	while (line != NULL)
	{
		line = ft_if_only_blanks(line);
		verif_fill_data(cub, line, 0);
		if (cub->verif.NO > 1 || cub->verif.SO > 1 || cub->verif.WE > 1 || \
			cub->verif.EA > 1 || cub->verif.F > 1 || cub->verif.C > 1)
		{
			free(line);
			ft_error(cub, "Double info", -1, -1);
		}
		cub->parse->total_height++;
		ft_fill_utility(cub, line);
		free(line);
		line = ft_get_next_line(cub->fd);
	}
	close(cub->fd);
	if (cub->parse->map_height == 0 || cub->parse->map_width == 0)
		return (ft_error(cub, "map size = 0", -1, -1), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_fill_utility_map(t_cub *cub, char *line, char *tmp)
{
	if (line[0] == '\n')
	{
		cub->parse->total_newline++;
		if (cub->parse->check_newline == 1)
			cub->parse->check_newline = 2;
	}
	else if (line[0] != '\n' && (ft_strchr(line, '1') || \
	ft_strchr(line, '0') || ft_strchr(line, 'N') || ft_strchr(line, 'S') || \
	ft_strchr(line, 'W') || ft_strchr(line, 'E')))
	{
		if (cub->parse->check_newline == 2)
		{
			free(line);
			ft_error(cub, "Invalid Newline inside map", -1, -1);
		}
		tmp = ft_strtrim(line, "\n");
		if (cub->parse->map_width < ft_strlen(tmp) && ft_strlen(tmp) != 0)
			cub->parse->map_width = ft_strlen(tmp);
		cub->parse->map_height++;
		cub->parse->check_newline = 1;
		free(tmp);
	}
}

//Rempli les variables NO, SO, WE, EA, F, C, map
int	ft_fill_utility(t_cub *cub, char *line)
{
	char	*tmp;

	if (ft_checker(line, 'N', 'O'))
		return (cub->parse->NO = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"NO ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_checker(line, 'S', 'O'))
		return (cub->parse->SO = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"SO ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_checker(line, 'W', 'E'))
		return (cub->parse->WE = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"WE ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_checker(line, 'E', 'A'))
		return (cub->parse->EA = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"EA ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_checker(line, 'F', '\0'))
		return (tmp = ft_substr(ft_strnstr(line, "F ", ft_strlen(line)), 2, \
		ft_strlen(line) - 2), cub->parse->F = ft_get_rgb(cub->parse->F, tmp), \
		cub->parse->ct++, free(tmp), 1);
	else if (ft_checker(line, 'C', '\0'))
		return (tmp = ft_substr(ft_strnstr(line, "C ", ft_strlen(line)), 2, \
		ft_strlen(line) - 2), cub->parse->C = ft_get_rgb(cub->parse->C, tmp), \
		cub->parse->ct++, free(tmp), 1);
	else
		ft_fill_utility_map(cub, line, NULL);
	return (0);
}

void	ft_init_map(t_cub *cub, size_t y, size_t x, char val)
{
	cub->map[y][x].value = val;
	cub->map[y][x].used = false;
	cub->map[y][x].count = 0;
	cub->map[y][x].count_0 = 0;
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

void	ft_init_cub_map(t_cub *cub)
{
	size_t	i;

	i = 0;
	cub->map = malloc(sizeof(t_cell *) * (cub->parse->map_height + 1));
	if (!cub->map)
		ft_error(cub, "Map Alloc failed", -1, -1);
	while (i <= cub->parse->map_height)
	{
		cub->map[i] = NULL;
		i++;
	}
}

//Rempli le tableau map
t_cell	**ft_fill_all(char *file, t_cub *cub)
{
	char	*line;
	size_t	j;

	j = 0;
	cub->fd = open(file, O_RDONLY);
	if (cub->fd == -1)
		return (ft_error(cub, "Invalid fd", -1, -1), NULL);
	ft_init_cub_map(cub);
	while (j < cub->parse->total_height)
	{
		line = ft_get_next_line(cub->fd);
		if (!line && j == 0)
			return (ft_error(cub, "NULL line", -1, -1), NULL);
		else if (!line)
			break ;
		line = ft_if_only_blanks(line);
		ft_prepare(cub, line, j);
		free(line);
		j++;
	}
	close(cub->fd);
	return (cub->map);
}
