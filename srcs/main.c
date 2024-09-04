/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:25:07 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 17:01:25 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = NULL;
	ft_create_cub(&cub);
	if (!cub)
		return (ft_free_cub(cub), 0);
	ft_init_structs(cub);
	if (argc != 2)
		return (ft_free_cub(cub), 0);
	if (ft_parsing(cub, argv) == EXIT_FAILURE)
		return (0);
	if (!cub->map)
		return (ft_free_cub(cub), 0);
	if (ft_init_mlx(cub) == EXIT_FAILURE)
		return (ft_free_cub(cub), 0);
	ft_project(cub);
	ft_free_cub(cub);
	return (0);
}
