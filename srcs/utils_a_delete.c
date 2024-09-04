/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_a_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:36 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 16:33:20 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// // imprime la map
// void    ft_print_map(t_cub *cub, t_cell **map, int map_width, int map_height)
// {
//     int	y;
//     int	x;

//     y = 0;
//     if (cub)
//     {}
// 	printf("map =");
// 	printf("\n\n");
// 	printf("map_width = %zu\n", cub->parse->map_width);
// 	printf("map_height = %zu\n", cub->parse->map_height);
// 	printf("total_height = %zu\n", cub->parse->total_height);
//     printf("tmp_height = %zu\n", cub->parse->tmp_height);
// 	printf("total_newline = %zu\n", cub->parse->total_newline);
// 	printf("total_infos = %zu\n", cub->parse->total_infos);
// 	printf("ct = %zu\n", cub->parse->ct);
// 	printf("NO = %s\n", cub->parse->NO);
// 	printf("SO = %s\n", cub->parse->SO);
// 	printf("WE = %s\n", cub->parse->WE);
// 	printf("EA = %s\n", cub->parse->EA);
// 	printf("floor->r = %d\n", cub->parse->F.r);
// 	printf("floor->g = %d\n", cub->parse->F.g);
// 	printf("floor->b = %d\n", cub->parse->F.b);
// 	printf("ceiling->r = %d\n", cub->parse->C.r);
// 	printf("ceiling->g = %d\n", cub->parse->C.g);
// 	printf("ceiling->b = %d\n", cub->parse->C.b);
// 	printf("player->dir = %c\n", cub->player->dir);
// 	printf("player location map start y->[%zu] x->[%zu]\n", 
//	cub->player->y_start, cub->player->x_start);
// 	printf("\n\n");
// 	if (map == NULL)
// 	{
//         fprintf(stderr, "Error: map is NULL\n");
//         return;
//     }
//     while (y < map_height)
//     {
// 		if (map[y] == NULL)
// 		{
//             fprintf(stderr, "Error: map[%d] is NULL\n", y);
//             break ;
//         }
//         x = 0;
//         while (x < map_width)
//         {
//             printf("%c", map[y][x].value);
//             x++;
//         }
//         printf("\n");
//         y++;
//     }
// }

// void	ft_print_used(t_cub *cub)
// {
// 	size_t	y;
// 	size_t	x;

// 	y = 0;
// 	while (cub->map[y])
// 	{
// 		x = 0;
// 		while (cub->map[y][x].value)
// 		{
// 			printf("%d", cub->map[y][x].used);
// 			x++;
// 		}
// 		printf ("\n");
// 		y++;
// 	}
// }