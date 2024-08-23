/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:00 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/23 13:55:48 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Parse le fichier .cub
// je commente verif map pour que tu es une version fonctionnelle. je suis en train de taff sur 
// la verif de la map
int	ft_parsing(int fd, t_cub *cub, char **argv)
{
	if (ft_get_data(argv[1], cub, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_fill_tab(fd, cub) == NULL)
		return (EXIT_FAILURE);
	ft_verif_data(cub, cub->map);
	return (EXIT_SUCCESS);
}

//Recupere les datas : NO, SO, WE, EA, F, C, map
int	ft_get_data(char *file, t_cub *cub, char *line)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_error(cub, "Invalid fd", -1, -1), EXIT_FAILURE);
	line = ft_get_next_line(fd);
	if (!line)
		return (ft_error(cub, "NULL line", -1, -1), EXIT_FAILURE);
	while (line != NULL)
	{
		line = ft_if_only_blanks(line);
		if (cub->parse->ct == 6 && ft_strchr(line, '1'))
		{
			cub->parse->total_infos = cub->parse->total_height;
			cub->parse->ct = 0;
		}
		cub->parse->total_height++;
		ft_fill_utility(cub, line);
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
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
		{
			cub->parse->tmp_height++;
		}
	}
	else if (line[0] != '\n' && ft_strchr(line, '1'))
	{
		//possibility to remove blanks before and after the map
		//tmp = ft_if_blanks(ft_strdup(line));
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

void	ft_init_tab(t_cub *cub)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	cub->map = malloc(sizeof(t_cell *) * (cub->parse->map_height + 1));
	if (!cub->map)
		ft_error(cub, "Map Alloc failed", -1, -1);
	while (y < cub->parse->map_height)
	{
		x = 0;
		cub->map[y] = malloc(sizeof(t_cell) * (cub->parse->map_width + 1));
		if (!cub->map[y])
			ft_error(cub, "Map Alloc failed", -1, -1);
		while (x < cub->parse->map_width)
		{
			cub->map[y][x].value = ' ';
			cub->map[y][x].used = false;
			cub->map[y][x].count = 0;
			cub->map[y][x].count_0 = 0;
			x++;
		}
        cub->map[y][x].value = '\0';
        y++;
    }
    cub->map[y] = NULL;
}

//Rempli le tableau map
t_cell	**ft_fill_tab(int fd, t_cub *cub)
{
	char	**split;
	char	*line;
	size_t		y;
	size_t		j;
	size_t		x;

	y = 0;
	j = 0;
	line = ft_get_next_line(fd);
	if (!line)
		return (ft_error(cub, "NULL line", -1, -1), NULL);
	while (j < cub->parse->total_infos)
	{
		j++;
		free(line);
		line = ft_get_next_line(fd);
		if (!line)
			return (ft_error(cub, "NULL line", -1, -1), NULL);
	}
	ft_init_tab(cub);
	while (j <= cub->parse->total_height)
	{
		if (line[0] == '\n' && cub->parse->tmp_height == 0)
		{
			free(line);
			line = malloc((cub->parse->map_width + 1) * sizeof(char));
			if (!line)
				return (ft_error(cub, "Line Alloc failed", -1, -1), NULL);
			memset(line, ' ', cub->parse->map_width);
			line[cub->parse->map_width] = '\0';
		}
		if (ft_check_line(cub, line) == 1)
		{
			x = 0;
			split = ft_mod_split(line, cub);
			if (split == NULL)
				return (ft_error(cub, "Split Alloc failed", -1, -1), NULL);
			while (x < cub->parse->map_width)
			{
				cub->map[y][x].value = *split[x];
				x++;
			}
			cub->map[y][x].value = '\0';
			ft_free_split(split);
			y++;
		}
		free(line);
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		j++;
	}
	cub->map[y] = NULL;
	return (cub->map);
}

