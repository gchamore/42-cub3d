/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:00 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/14 14:34:41 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Parse le fichier .cub
// je commente verif map pour que tu es une version fonctionnelle. je suis en train de taff sur 
// la verif de la map
int	ft_parsing(int fd, t_cub *cub, char **argv)
{
	if (ft_get_data(argv[1], cub) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_fill_tab(fd, cub) == NULL)
		return (EXIT_FAILURE);
	// ft_verif_map(cub, cub->map);
	return (EXIT_SUCCESS);
}

//Recupere les datas : NO, SO, WE, EA, F, C, map
int	ft_get_data(char *file, t_cub *cub)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_error(cub, "Invalid fd", ' '), EXIT_FAILURE);
	line = ft_get_next_line(fd);
	if (!line)
		return (ft_error(cub, "NULL line", ' '), EXIT_FAILURE);
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
		return (ft_error(cub, "map size = 0", ' '), EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
	else if (line[0] == '\n')
		cub->parse->total_newline++;
	else if (line[0] != '\n')
	{
		tmp = ft_if_blanks(ft_strdup(line));
		if (cub->parse->map_width < ft_strlen(tmp) && ft_strlen(tmp) != 0)
			cub->parse->map_width = ft_strlen(tmp);
		cub->parse->map_height++;
		free(tmp);
	}
	return (0);
}

//Rempli le tableau map
t_cell	**ft_fill_tab(int fd, t_cub *cub)
{
	char	**split;
	char	*line;
	size_t		i;
	size_t		j;
	size_t		y;

	i = 0;
	j = 0;
	line = ft_get_next_line(fd);
	if (!line)
		return (ft_error(cub, "NULL line", ' '), NULL);
	cub->map = malloc(sizeof(t_cell *) * (cub->parse->map_height + 1));
	if (!cub->map)
		return (ft_error(cub, "Map Alloc failed", ' '), NULL);
	while (j < cub->parse->total_infos)
	{
		j++;
		free(line);
		line = ft_get_next_line(fd);
		if (!line)
			return (ft_error(cub, "NULL line", ' '), NULL);
	}
	while (j <= cub->parse->total_height)
	{
		if (ft_check_line(cub, line) == 1)
		{
			y = 0;
			split = ft_mod_split(line, cub);
			if (split == NULL)
				return (ft_error(cub, "Split Alloc failed", ' '), NULL);
			cub->map[i] = malloc(sizeof(t_cell) * (cub->parse->map_width + 1));
			if (!cub->map[i])
				return (ft_error(cub, "Map Alloc failed", ' '), NULL);
			while (y < cub->parse->map_width)
			{
				cub->map[i][y].value = *split[y];
				cub->map[i][y].used = false;
				y++;
			}
			cub->map[i][y].value = '\0';
			cub->map[i][y].used = false;
			ft_free_split(split);
			i++;
		}
		free(line);
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		j++;
	}
	cub->map[i] = NULL;
	return (cub->map);
}

