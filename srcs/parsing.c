/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:00 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/03 15:27:39 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Parse le fichier .cub
// je commente verif map pour que tu es une version fonctionnelle. je suis en train de taff sur 
// la verif de la map
int	ft_parsing(t_cub *cub, char **argv)
{
	if (ft_get_data(argv[1], cub, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_fill_all(argv[1], cub) == NULL)
		return (EXIT_FAILURE);
	ft_verif_data(cub, cub->map);
	return (EXIT_SUCCESS);
}

void	verif_if_double(t_cub *cub, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (((line[i] == 'N' && line[i + 1] == 'O') && cub->parse->NO != NULL) || ((line[i] == 'S' && line[i + 1] == 'O') && cub->parse->SO != NULL) || ((line[i] == 'W' && line[i + 1] == 'E') && cub->parse->WE != NULL) || ((line[i] == 'E' && line[i + 1] == 'A') && cub->parse->EA != NULL))
		{
			free(line);
			ft_error(cub, "double data", -1, -1);
		}
		else
			i++;
	}
}

void	verif_fill_data(t_cub *cub, char *line)
{
	int i;

	i = 0;
	verif_if_double(cub, line);
	while (line[i] && cub->parse->ct != 7)
	{
		if (line[i] == ' ' || line[i] == '\t')
        	i++;
		else if (cub->parse->ct < 6 && (line[i] == '1' || line[i] == '0' || (line[i] == 'N' && line[i + 1] != 'O') || (line[i] == 'S' && line[i + 1] != 'O') || (line[i] == 'W' && line[i + 1] != 'E')|| (line[i] == 'E' && line[i + 1] != 'A')))
		{
			free(line);
			ft_error(cub, "Invalid data", -1, -1);
		}
		else if (cub->parse->ct == 6 && (line[i] == '1' || line[i] == '0' || (line[i] == 'N' && line[i + 1] != 'O') || (line[i] == 'S' && line[i + 1] != 'O') || (line[i] == 'W' && line[i + 1] != 'E')|| (line[i] == 'E' && line[i + 1] != 'A')))
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
		// printf ("line = %s\n", line);
		line = ft_if_only_blanks(line);
		verif_fill_data(cub, line);
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
	else if (line[0] != '\n' && (ft_strchr(line, '1') || ft_strchr(line, '0') || ft_strchr(line, 'N') || ft_strchr(line, 'S') || ft_strchr(line, 'W') || ft_strchr(line, 'E')))
	{
		if (cub->parse->check_newline == 2)
		{
			free(line);
			ft_error(cub, "Invalid Newline inside map", -1, -1);
		}
		//possibility to remove blanks before and after the map
		tmp = ft_strtrim(line, "\n");
		if (cub->parse->map_width < ft_strlen(tmp) && ft_strlen(tmp) != 0)
			cub->parse->map_width = ft_strlen(tmp);
		cub->parse->map_height = ((cub->parse->map_height + cub->parse->tmp_height) + 1);
		cub->parse->tmp_height = 0;
		cub->parse->check_newline = 1;
		free(tmp);
	}
}

//Rempli les variables NO, SO, WE, EA, F, C, map
int	ft_fill_utility(t_cub *cub, char *line)
{
	char *tmp;

	if (ft_strnstr(line, "NO ", ft_strlen(line)))
		return (cub->parse->NO = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"NO ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_strnstr(line, "SO ", ft_strlen(line)))
		return (cub->parse->SO = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"SO ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_strnstr(line, "WE ", ft_strlen(line)))
		return (cub->parse->WE = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"WE ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_strnstr(line, "EA ", ft_strlen(line)))
		return (cub->parse->EA = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"EA ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_strnstr(line, "F ", ft_strlen(line)))
		return (tmp = ft_substr(ft_strnstr(line, "F ", ft_strlen(line)), 2, \
		ft_strlen(line) - 2), cub->parse->F = ft_get_rgb(cub->parse->F, tmp), \
		cub->parse->ct++, free(tmp), 1);
	else if (ft_strnstr(line, "C ", ft_strlen(line)))
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
	size_t x;
	size_t y;

	y = (j - cub->parse->total_infos);
	if (ft_check_line(cub, line) == 1)
	{
		x = 0;
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
		while (x < cub->parse->map_width)
		{
			ft_init_map(cub, y, x, *split[x]);
			x++;
		}
		ft_init_map(cub, y, x, '\0');
		ft_free_split(split);
		y++;
	}
}

void ft_prepare(t_cub *cub, char *line, size_t j)
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

//Rempli le tableau map
t_cell	**ft_fill_all(char *file, t_cub *cub)
{
	char	*line;
	size_t		j;

	j = 0;
	cub->fd = open(file, O_RDONLY);
	if (cub->fd == -1)
		return (ft_error(cub, "Invalid fd", -1, -1), NULL);
	cub->map = malloc(sizeof(t_cell *) * (cub->parse->map_height + 1));
	if (!cub->map)
		return (ft_error(cub, "Map Alloc failed", -1, -1), NULL);
	while (j <= cub->parse->map_height)
	{
        cub->map[j] = NULL;
		j++;
	}
	j = 0;
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

