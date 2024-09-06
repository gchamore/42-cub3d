/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:00 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/06 12:13:03 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_parsing(t_cub *cub, char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
		i++;
	if (strcmp(&argv[1][i - 4], ".cub"))
		return (ft_error(cub, "not terminated with .cub", -1, -1), \
		EXIT_FAILURE);
	if (ft_get_data(argv[1], cub, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_fill_all(argv[1], cub) == NULL)
		return (EXIT_FAILURE);
	ft_verif_data(cub, cub->map);
	return (EXIT_SUCCESS);
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
		if (cub->verif.no > 1 || cub->verif.so > 1 || cub->verif.we > 1 || \
			cub->verif.ea > 1 || cub->verif.f > 1 || cub->verif.c > 1)
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

t_cell	**ft_verif_data(t_cub *cub, t_cell **map)
{
	ft_check_borders(cub, 0, 0);
	ft_check_if_valid_map(cub);
	return (map);
}
