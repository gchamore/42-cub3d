/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:00 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/02 16:47:01 by gchamore         ###   ########.fr       */
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

void	verif_fill_data(t_cub *cub, char *line, int fd)
{
	int i;

	i = 0;
	// printf ("line = %s\n", line);
	while (line[i] && cub->parse->ct != 7)
	{
		if (line[i] == ' ' || line[i] == '\t')
        	i++;
		else if (cub->parse->ct < 6 && (line[i] == '1' || line[i] == '0' || (line[i] == 'N' && line[i + 1] != 'O') || (line[i] == 'S' && line[i + 1] != 'O') || (line[i] == 'W' && line[i + 1] != 'E')|| (line[i] == 'E' && line[i + 1] != 'A')))
		{
			free(line);
			close(fd);
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
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_error(cub, "Invalid fd", -1, -1), EXIT_FAILURE);
	line = ft_get_next_line(fd);
	if (!line)
		return (ft_error(cub, "NULL line", -1, -1), EXIT_FAILURE);
	while (line != NULL)
	{
		// printf ("line = %s\n", line);
		line = ft_if_only_blanks(line);
		verif_fill_data(cub, line, fd);
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
	else if (line[0] != '\n' && (ft_strchr(line, '1') || ft_strchr(line, '0') || ft_strchr(line, 'N') || ft_strchr(line, 'S') || ft_strchr(line, 'W') || ft_strchr(line, 'E')))
	{
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
	cub->map = malloc(sizeof(t_cell *) * (cub->parse->map_height + 1));
	if (!cub->map)
		return (ft_error(cub, "Map Alloc failed", -1, -1), NULL);
	for (size_t i = 0; i <= cub->parse->map_height; i++)
        cub->map[i] = NULL;
	while (j < cub->parse->total_infos)
	{
		// printf ("line = %s\n", line);
		j++;
		free(line);
		line = ft_get_next_line(fd);
		if (!line)
			return (ft_error(cub, "NULL line", -1, -1), NULL);
	}
	while (j <= (cub->parse->total_height - cub->parse->tmp_height))
	{
		// printf ("line = %s\n", line);
		line = ft_if_only_blanks(line);
		if (line[0] == '\n')
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
			split = ft_mod_split(line, cub, 0, 0);
			if (split == NULL)
				return (ft_error(cub, "Split Alloc failed", -1, -1), NULL);
			cub->map[y] = malloc(sizeof(t_cell) * (cub->parse->map_width + 1));
			if (!cub->map[y])
                return (ft_error(cub, "Map Alloc failed", -1, -1), NULL);
			while (x < cub->parse->map_width)
			{
				cub->map[y][x].value = *split[x];
				cub->map[y][x].used = false;
				cub->map[y][x].count = 0;
				cub->map[y][x].count_0 = 0;
				x++;
			}
			cub->map[y][x].value = '\0';
			cub->map[y][x].used = false;
			cub->map[y][x].count = 0;
			cub->map[y][x].count_0 = 0;
			ft_free_split(split);
			y++;
		}
		free(line);
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		j++;
	}
	return (cub->map);
}

