/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:00 by gchamore          #+#    #+#             */
/*   Updated: 2024/07/18 15:49:46 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_cub *cub, char *str, char c)
{
	printf("Error : %s on %c\n", str, c);
	ft_free_map(cub->map, cub->parse->map_height);
	exit(1);
}

void	ft_check_line(t_cub *cub, char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_is_delimiter(line[i]) && line[i] != '1' \
			&& line[i] != '0' && line[i] != 'N' && line[i] \
			!= 'S' && line[i] != 'W' && line[i] != 'E')
		{
			ft_error(cub, "Invalid map", line[i]);
			exit(1);
		}
		i++;
	}
}

void	ft_init_structs(t_cub *cub)
{
	cub->map = NULL;
	cub->parse->NO = NULL;
	cub->parse->SO = NULL;
	cub->parse->WE = NULL;
	cub->parse->EA = NULL;
	cub->parse->F = NULL;
	cub->parse->C = NULL;
	cub->parse->map_height = 0;
	cub->parse->map_width = 0;
	cub->parse->total_height = 0;
}

void	ft_print_map(int **map, int map_width, int map_height)
{
    int	i;
    int	j;

    i = 0;
    while (i < map_height)
    {
        j = 0;
        while (j < map_width)
        {
            printf("%d", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

char	*ft_if_blanks(char *str)
{
	int	i;
	char *tmp;

	i = 0;
	tmp = str;
	while (tmp[i])
	{
		if (ft_is_delimiter(tmp[i]))
		{
			str = ft_strtrim(tmp, &tmp[i]);
			free(tmp);
			tmp = str;
			i = 0;
			continue ;
		}
		i++;
	}
	return (str);
}

int	ft_get_size(char *file, t_cub *cub)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	line = ft_get_next_line(fd);
	if (!line)
		return (1);
	while (line != NULL)
	{
		ft_fill_utility(cub, line);
		cub->parse->total_height++;
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	if (cub->parse->map_height == 0 || cub->parse->map_width == 0)
		return (1);
	cub->parse->map_width--;
	printf("map_width = %zu\n", cub->parse->map_width);
	printf("map_height = %zu\n", cub->parse->map_height);
	printf("total_height = %zu\n", cub->parse->total_height);
	// printf("NO = %s\n", cub->parse->NO);
	// printf("SO = %s\n", cub->parse->SO);
	// printf("WE = %s\n", cub->parse->WE);
	// printf("EA = %s\n", cub->parse->EA);
	// printf("F = %s\n", cub->parse->F);
	// printf("C = %s\n", cub->parse->C);
	return (0);
}

int	ft_fill_utility(t_cub *cub, char *line)
{
	if (ft_strnstr(line, "NO ", ft_strlen(line)))
		return (cub->parse->NO = ft_if_blanks(ft_substr(ft_strnstr(line, "NO ", \
			ft_strlen(line)), 3, ft_strlen(line) - 3)), 1);
	else if (ft_strnstr(line, "SO ", ft_strlen(line)))
		return (cub->parse->SO = ft_if_blanks(ft_substr(ft_strnstr(line, "SO ", \
			ft_strlen(line)), 3, ft_strlen(line) - 3)), 1);
	else if (ft_strnstr(line, "WE ", ft_strlen(line)))
		return (cub->parse->WE = ft_if_blanks(ft_substr(ft_strnstr(line, "WE ", \
			ft_strlen(line)), 3, ft_strlen(line) - 3)), 1);
	else if (ft_strnstr(line, "EA ", ft_strlen(line)))
		return (cub->parse->EA = ft_if_blanks(ft_substr(ft_strnstr(line, "EA ", \
			ft_strlen(line)), 3, ft_strlen(line) - 3)), 1);
	else if (ft_strnstr(line, "F ", ft_strlen(line)))
		return (cub->parse->F = ft_if_blanks(ft_substr(ft_strnstr(line, "F ", \
			ft_strlen(line)), 2, ft_strlen(line) - 2)), 1);
	else if (ft_strnstr(line, "C ", ft_strlen(line)))
		return (cub->parse->C = ft_if_blanks(ft_substr(ft_strnstr(line, "C ", \
			ft_strlen(line)), 2, ft_strlen(line) - 2)), 1);
	else if (line[0] != '\n')
	{
		if (cub->parse->map_width < ft_strlen(line) && ft_strlen(line) != 0)
			cub->parse->map_width = ft_strlen(line);
		cub->parse->map_height++;
	}
	return (0);
}

int	**ft_fill_tab(int fd, t_cub *cub)
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
		return (NULL);
	// printf("cub->parse->map_width = %zu\n", cub->parse->map_width);
	// printf("cub->parse->map_height = %zu\n", cub->parse->map_height);
	cub->map = malloc(sizeof(int *) * cub->parse->map_height + 1);
	if (!cub->map)
		return (NULL);
	while (j < cub->parse->total_height - cub->parse->map_height)
	{
		j++;
		free(line);
		line = ft_get_next_line(fd);
		if (!line)
			return (NULL);
	}
	while (j <= cub->parse->total_height)
	{
		// printf("j = %zu\n", j);
		// printf("cub->parse->total_height = %zu\n", cub->parse->total_height);
		// printf("line = %s\n", line);
		ft_check_line(cub, line);
		y = 0;
		split = ft_mod_split(line, cub);
		if (split == NULL)
    		return (NULL);
		// printf("cub->parse->map_width = %zu\n", cub->parse->map_width);
		// printf("cub->parse->map_height = %zu\n", cub->parse->map_height);
		cub->map[i] = malloc(sizeof(int) * cub->parse->map_width);
		if (!cub->map[i])
			return (NULL);
		while (y < cub->parse->map_width)
		{
			cub->map[i][y] = ft_atoi(split[y]);
			y++;
		}
		free(line);
		ft_free_split(split);
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		j++;
		i++;
	}
	// free(line);
	return (cub->map);
}

void	ft_create_cub(t_cub **cub)
{
    *cub = malloc(sizeof(t_cub));
    if (*cub)
    {
        (*cub)->parse = malloc(sizeof(t_parse));
        if (!(*cub)->parse)
        {
            ft_free_cub(*cub);
            *cub = NULL;
            return;
        }
        (*cub)->data = malloc(sizeof(t_data));
        if (!(*cub)->data)
        {
            ft_free_cub(*cub);
            *cub = NULL;
            return;
        }
    }
}

void	ft_free_map(int **map, int map_height)
{
	int	i;

	i = 0;
	if (map && map_height > 0)
	{
		while (i < map_height)
		{
			free(map[i]);
			map[i] = NULL;
			i++;
		}
		free(map);
		map = NULL;
	}
}

void	ft_free_cub(t_cub *cub)
{
	if (cub)
	{
		if (cub->map)
		{
			ft_free_map(cub->map, cub->parse->map_height);
			cub->map = NULL;
		}
		if (cub->data)
		{
			free(cub->data);
			cub->data = NULL;
		}
		if (cub->parse)
		{
			if (cub->parse->NO)
			{
				free(cub->parse->NO);
				cub->parse->NO = NULL;
			}
			if (cub->parse->SO)
			{
				free(cub->parse->SO);
				cub->parse->SO = NULL;
			}
			if (cub->parse->WE)
			{
				free(cub->parse->WE);
				cub->parse->WE = NULL;
			}
			if (cub->parse->EA)
			{
				free(cub->parse->EA);
				cub->parse->EA = NULL;
			}
			if (cub->parse->F)
			{
				free(cub->parse->F);
				cub->parse->F = NULL;
			}
			if (cub->parse->C)
			{
				free(cub->parse->C);
				cub->parse->C = NULL;
			}
			free(cub->parse);
			cub->parse = NULL;
		}
		free(cub);
		cub = NULL;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_cub	*cub;

	cub = NULL;
	ft_create_cub(&cub);
	if (!cub)
		return (ft_free_cub(cub), 0);
	ft_init_structs(cub);
	if (argc != 2 || ft_get_size(argv[1], cub) == 1)
		return (ft_free_cub(cub), 0);
	fd = open(argv[1], O_RDONLY);
	cub->map = ft_fill_tab(fd, cub);
	if (!cub->map)
		return (ft_free_cub(cub), 0);
	printf("map = \n");
	ft_print_map(cub->map, cub->parse->map_width, cub->parse->map_height);
	close(fd);
	ft_free_cub(cub);
	return (0);
}
