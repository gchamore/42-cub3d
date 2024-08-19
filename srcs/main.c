/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:25:07 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/19 15:15:35 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_cub	*cub;

	cub = NULL;
	ft_create_cub(&cub);
	if (!cub)
		return (ft_free_cub(cub), 0);
	ft_init_structs(cub);
	if (argc != 2)
		return (ft_free_cub(cub), 0);
	fd = open(argv[1], O_RDONLY);
	if (ft_parsing(fd, cub, argv) == EXIT_FAILURE)
		return (0);
	if (!cub->map)
		return (ft_free_cub(cub), 0);
	if (ft_init_mlx(cub) == EXIT_FAILURE)
		return (ft_free_cub(cub), 0);
	ft_project(cub);
	// printf("map = \n");
	// ft_print_map(cub, cub->map, cub->parse->map_width, cub->parse->map_height);
	close(fd);
	ft_free_cub(cub);
	return (0);
}