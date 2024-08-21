/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:22:42 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/21 15:06:13 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// // Compte le nombre de 1 autour de la case pour connaitre le nombre 
// // de chemins possibles depuis cette case et revenir a la case precedente si besoin
// void	ft_count_1(t_cub *cub, size_t x, size_t y)
// {
// 	if (cub->map[x][y].value == '1')
// 	{
// 		if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == false)
// 			cub->map[x][y].count++;
// 		if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == false)
// 			cub->map[x][y].count++;
// 		if (y > 0 && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].count == 0 && cub->map[x][y - 1].used == false)
// 			cub->map[x][y].count++;
// 		if (x > 0 && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].count == 0 && cub->map[x - 1][y].used == false)
// 			cub->map[x][y].count++;
// 	}	
// }

// // Vérifie si il y a la case de fin accessible autour de la case actuelle
// int	ft_check_end(t_cub *cub, size_t x, size_t y)
// {
// 	int i;

// 	i = 0;
// 	if (cub->map[x][y].value == '1' && cub->check >= 4)
// 	{
// 		if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == true && cub->map[x][y + 1].end == true)
// 			return (printf("map 2 = [%zu][%zu]\n", x, y + 1), 0);
// 		if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == true && cub->map[x + 1][y].end == true)
// 			return (printf("map 2 = [%zu][%zu]\n", x + 1, y), 0);
// 		if (y > 0 && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].used == true && cub->map[x][y - 1].end == true)
// 			return (printf("map 2 = [%zu][%zu]\n", x, y - 1), 0);
// 		if (x > 0 && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].used == true && cub->map[x - 1][y].end == true)
// 			return (printf("map 2 = [%zu][%zu]\n", x - 1, y), 0);
// 	}
// 	return (1);
// }

// // Vérifie si la map est bien fermee algo principale check droite -> bas -> gauche -> haut
// // check sert a savoir de combien on avance et si on fait demi tour afin de ne pas toucher end en revenant en arriere
// // count sert a savoir combien de 1 il y a autour de la case actuelle cf ft_count_1

// void	ft_verif_right(t_cub *cub, size_t x, size_t y)
// {
// 	if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value != '\0' && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == false && cub->map[x][y].count >= 1)
// 	{
// 		cub->map[x][y].count--;
// 		if ((x > 0 && cub->map[x - 1][y].value == '0'))
// 			cub->exit = 1;
// 		if (ft_check_if_valid_map(cub, x, y + 1) == 0)
// 			cub->exit = 0;
// 		else
// 			cub->check--;

// 	}
// }
// void	ft_verif_down(t_cub *cub, size_t x, size_t y)
// {
// 	if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value != '\0' && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == false && cub->map[x][y].count >= 1)
// 	{
// 		cub->map[x][y].count--;
// 		if ((y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == '0'))
// 			cub->exit = 1;
// 		if (ft_check_if_valid_map(cub, x + 1, y) == 0)
// 			cub->exit = 0;
// 		else
// 			cub->check--;

// 	}
// }

// void	ft_verif_left(t_cub *cub, size_t x, size_t y)
// {
// 	if (y > 0 && cub->map[x][y].value == '1' && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].used == false && cub->map[x][y].count >= 1 && cub->map[x][y].count >= 1)
// 	{
// 		cub->map[x][y].count--;
// 		if ((x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == '0'))
// 			cub->exit = 1;
// 		if (ft_check_if_valid_map(cub, x, y - 1) == 0)
// 			cub->exit = 0;
// 		else
// 			cub->check--;
// 	}
// }

// void	ft_verif_up(t_cub *cub, size_t x, size_t y)
// {
// 	if (x > 0 && cub->map[x][y].value == '1' && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].used == false && cub->map[x][y].count >= 1 && cub->map[x][y].count >= 1)
// 	{
// 		cub->map[x][y].count--;
// 		if ((y > 0 && cub->map[x][y - 1].value == '0'))
// 			cub->exit = 1;
// 		if (ft_check_if_valid_map(cub, x - 1, y) == 0)
// 			cub->exit = 0;
// 		else
// 			cub->check--;
// 	}
// }

// int	ft_check_map_direction(t_cub *cub, size_t x, size_t y)
// {
// 	ft_verif_right(cub, x, y);
// 	if (cub->exit == 1)
// 		return (1);
// 	else if (cub->exit == 0)
// 		return (0);
// 	ft_verif_down(cub, x, y);
// 	if (cub->exit == 1)
// 		return (1);
// 	else if (cub->exit == 0)
// 		return (0);
// 	ft_verif_left(cub, x, y);
// 	if (cub->exit == 1)
// 		return (1);
// 	else if (cub->exit == 0)
// 		return (0);
// 	ft_verif_up(cub, x, y);
// 	if (cub->exit == 1)
// 		return (1);
// 	else if (cub->exit == 0)
// 		return (0);
// 	return (1);
// }

// // Vérifie si la map est bien fermee algo principale check droite -> bas -> gauche -> haut
// // check sert a savoir de combien on avance et si on fait demi tour afin de ne pas toucher end en revenant en arriere
// // count sert a savoir combien de 1 il y a autour de la case actuelle cf ft_count_1
// // je vais serparer chaque direction en fonction individuelle pour plus de clarte
// int ft_check_if_valid_map(t_cub *cub, size_t x, size_t y)
// {
// 	if (!cub || !cub->parse || x >= cub->parse->map_height || y >= cub->parse->map_width)
//         return (0);
// 	printf ("-> [%zu][%zu]\n", x, y);
// 	cub->exit = 2;
// 	cub->check++;
// 	// printf("cub->check = %d\n", cub->check);
// 	if (cub->map[x][y].value != '1')
//         return (ft_error(cub, "Invalid map", cub->map[x][y].value), 1);
// 	cub->map[x][y].used = true;
// 	ft_count_1(cub, x, y);
// 	if (cub->map[x][y].count == 0)
// 	{
// 		if (ft_check_end(cub, x, y) == 0 && cub->check >= 4)
// 			return (printf("THE END 1 !"), 0);
// 		else
// 			return (1);
// 	}
// 	if (ft_check_end(cub, x, y) == 0 && cub->check >= 4)
// 			return (printf("THE END 2 !"), 0);
// 	ft_check_map_direction(cub, x, y);
// 	if (cub->exit == 1)
// 		return (1);
// 	else if (cub->exit == 0)
// 		return (0);
// 	return (1);
// }

// // Trouve la case de depart de la map pour commencer l'algo de verification
// // afin d'eviter de commencer sur une case non valide sur laquelle on ne peut pas boucler
// //exemple :
// //            1
// //           111
// //            1
// // start -> 1111
// //          1001
// //          1111
// // le 1 avec start est la case de depart et il sera marque comme end
// void	ft_get_map_start(t_cub *cub)
// {
//     size_t x;
//     size_t y;

//     x = 0;
//     while (cub->map[x])
//     {
//         y = 0;
//         while (cub->map[x][y].value)
//         {
//             if (y > 0 && x + 1 < cub->parse->map_height && y + 1 < cub->parse->map_width)
//             {
//                 if (cub->map[x][y].value == '1' && cub->map[x][y + 1].value == '1' && cub->map[x + 1][y].value == '1' && (cub->map[x + 1][y + 1].value == '0' || cub->map[x + 1][y + 1].value == '1' || cub->map[x + 1][y + 1].value == 'N' || cub->map[x + 1][y + 1].value == 'S' || cub->map[x + 1][y + 1].value == 'W' || cub->map[x + 1][y + 1].value == 'E'))
//                 {
//                     cub->x_start = x;
//                     cub->y_start = y;
// 					return ;
//                 }
//             }
//             y++;
//         }
//         x++;
//     }
// }

// // Vérifie si la map est valide
// t_cell **ft_verif_map(t_cub *cub, t_cell **map)
// {
// 	printf ("map_height = %zu\n", cub->parse->map_height);
// 	printf ("map_width = %zu\n", cub->parse->map_width);

// 	ft_get_map_start(cub);
// 	cub->map[cub->x_start][cub->y_start].end = true;
// 	if (ft_check_if_valid_map(cub, cub->x_start, cub->y_start) == 0)
// 		return (printf("YEAAAAAAH \n\n"), map);
// 	else
// 		return (printf("Error\nWrong Map \n\n"), NULL);
//     return (map);
// }

// void	ft_if_solo_1(t_cub *cub, size_t x, size_t y)
// {
// 	if (cub->map[x][y].value == '1')
// 	{
// 		if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == false)
// 			return 1;
// 		if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == false)
// 			cub->map[x][y].count++;
// 		if (y > 0 && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].count == 0 && cub->map[x][y - 1].used == false)
// 			cub->map[x][y].count++;
// 		if (x > 0 && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].count == 0 && cub->map[x - 1][y].used == false)
// 			cub->map[x][y].count++;
// 	}
// }

void	ft_check_inside(t_cub *cub, size_t x, size_t y)
{
	if (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E')
		ft_error(cub, "Invalid map 1", x, y);
	else if (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E')
		ft_error(cub, "Invalid map 2", x, y);
	else if (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E')
		ft_error(cub, "Invalid map 3", x, y);
	else if (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E')
		ft_error(cub, "Invalid map 4", x, y);
}
void	ft_check_corners_1(t_cub *cub, size_t x, size_t y)
{
	if (x == 0 && y == 0)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E'))
			ft_error(cub, "Invalid map 5", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E'))
			ft_error(cub, "Invalid map 6", x, y);
	}
	if (x == cub->parse->map_height - 1 && y == cub->parse->map_width - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E'))
			ft_error(cub, "Invalid map 7", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E'))
			ft_error(cub, "Invalid map 8", x, y);
	}
}
void	ft_check_corners_2(t_cub *cub, size_t x, size_t y)
{
	if (x == 0 && y == cub->parse->map_width - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E'))
			ft_error(cub, "Invalid map 9", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E'))
			ft_error(cub, "Invalid map 10", x, y);
	}
	if (x == cub->parse->map_height - 1 && y == 0)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E'))
			ft_error(cub, "Invalid map 11", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E'))
			ft_error(cub, "Invalid map 12", x, y);
	}
}

void	ft_check_sides_1(t_cub *cub, size_t x, size_t y)
{
	if (x == 0 && y > 0 && y < cub->parse->map_width - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E'))
			ft_error(cub, "Invalid map 13", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E'))
			ft_error(cub, "Invalid map 14", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E'))
			ft_error(cub, "Invalid map 15", x, y);
	}
	if (y == 0 && x > 0 && x < cub->parse->map_height - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E'))
			ft_error(cub, "Invalid map 16", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E'))
			ft_error(cub, "Invalid map 17", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E'))
			ft_error(cub, "Invalid map 18", x, y);
	}
}

void	ft_check_sides_2(t_cub *cub, size_t x, size_t y)
{
	if (x == cub->parse->map_height - 1 && y > 0 && y < cub->parse->map_width - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E'))
			ft_error(cub, "Invalid map 19", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y + 1].value == '0' || cub->map[x][y + 1].value == 'N' || cub->map[x][y + 1].value == 'S' || cub->map[x][y + 1].value == 'W' || cub->map[x][y + 1].value == 'E'))
			ft_error(cub, "Invalid map 20", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E'))
			ft_error(cub, "Invalid map 21", x, y);
	}
	if (y == cub->parse->map_width - 1 && x > 0 && x < cub->parse->map_height - 1)
	{
		if (cub->map[x][y].value == ' ' && (cub->map[x + 1][y].value == '0' || cub->map[x + 1][y].value == 'N' || cub->map[x + 1][y].value == 'S' || cub->map[x + 1][y].value == 'W' || cub->map[x + 1][y].value == 'E'))
			ft_error(cub, "Invalid map 21", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x - 1][y].value == '0' || cub->map[x - 1][y].value == 'N' || cub->map[x - 1][y].value == 'S' || cub->map[x - 1][y].value == 'W' || cub->map[x - 1][y].value == 'E'))
			ft_error(cub, "Invalid map 22", x, y);
		if (cub->map[x][y].value == ' ' && (cub->map[x][y - 1].value == '0' || cub->map[x][y - 1].value == 'N' || cub->map[x][y - 1].value == 'S' || cub->map[x][y - 1].value == 'W' || cub->map[x][y - 1].value == 'E'))
			ft_error(cub, "Invalid map 23", x, y);
	}
}

int	ft_verif_right(t_cub *cub, size_t x, size_t y)
{
	if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value != '\0' && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == false && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if (ft_check_arround_1(cub, x, y + 1) == 0)
			return (0);
	}
	return (1);
}
int	ft_verif_down(t_cub *cub, size_t x, size_t y)
{
	if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value != '\0' && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == false && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if (ft_check_arround_1(cub, x + 1, y) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_left(t_cub *cub, size_t x, size_t y)
{
	if (y > 0 && cub->map[x][y].value == '1' && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].used == false && cub->map[x][y].count >= 1 && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if (ft_check_arround_1(cub, x, y - 1) == 0)
			return (0);
	}
	return (1);
}

int	ft_verif_up(t_cub *cub, size_t x, size_t y)
{
	if (x > 0 && cub->map[x][y].value == '1' && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].used == false && cub->map[x][y].count >= 1 && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if (ft_check_arround_1(cub, x - 1, y) == 0)
			return (0);
	}
	return (1);
}

int	ft_check_map_direction(t_cub *cub, size_t x, size_t y)
{
	if (ft_verif_right(cub, x, y) == 0)
		return (0);
	if (ft_verif_down(cub, x, y) == 0)
		return (0);
	if (ft_verif_left(cub, x, y) == 0)
		return (0);
	if (ft_verif_up(cub, x, y) == 0)
		return (0);
	return (1);
}

void	ft_count(t_cub *cub, size_t x, size_t y, char value)
{
	if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == value && cub->map[x][y + 1].used == false)
	{
		if (value == '1')
			cub->map[x][y].count++;
		else
			cub->map[x][y].count_0++;
	}
	if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == value && cub->map[x + 1][y].used == false)
	{
		if (value == '1')
			cub->map[x][y].count++;
		else
			cub->map[x][y].count_0++;
	}
	if (y > 0 && cub->map[x][y - 1].value == value && cub->map[x][y - 1].count == 0 && cub->map[x][y - 1].used == false)
	{
		if (value == '1')
			cub->map[x][y].count++;
		else
			cub->map[x][y].count_0++;
	}
	if (x > 0 && cub->map[x - 1][y].value == value && cub->map[x - 1][y].count == 0 && cub->map[x - 1][y].used == false)
	{
		if (value == '1')
			cub->map[x][y].count++;
		else
			cub->map[x][y].count_0++;
	}
}

int	ft_check_arround_1(t_cub *cub, size_t x, size_t y)
{
	cub->map[x][y].used = true;
	ft_count(cub, x, y, '0');
	if (cub->map[x][y].count_0 != 0)
		return (0);
	ft_count(cub, x, y, '1');
	if (cub->map[x][y].count >= 1)
	{
		if (ft_check_map_direction(cub, x, y) == 0)
				return (0);
			else
				return (1);
	}
	return (1);
}

void	ft_reset_used(t_cub *cub)
{
	size_t x;
	size_t y;

	x = 0;
	while (cub->map[x])
	{
		y = 0;
		while (cub->map[x][y].value)
		{
			cub->map[x][y].used = false;
			y++;
		}
		x++;
	}
}

void	ft_check_borders(t_cub *cub)
{
    size_t x;
    size_t y;

    x = 0;
    while (cub->map[x])
    {
        y = 0;
        while (cub->map[x][y].value)
        {
			if (cub->map[x][y].value == '1')
			{
				if(ft_check_arround_1(cub, x, y) == 1)
					ft_error(cub, "Walls alone", x, y);
				ft_reset_used(cub);
			}
			// printf("\n");
            if (x == 0 || y == 0 || x == cub->parse->map_height - 1 || y == cub->parse->map_width - 1)
			{
				// printf("Borders -> [%zu][%zu] = %c\n", x, y, cub->map[x][y].value);
				// if (cub->map[x][y].value != '1' && cub->map[x][y].value != ' ')
				// 	ft_error(cub, "Invalid map 0", x, y);
				ft_check_corners_1(cub, x, y);
				ft_check_corners_2(cub, x, y);
				ft_check_sides_1(cub, x, y);
				ft_check_sides_2(cub, x, y);
			}
            y++;
        }
        x++;
    }
}

void ft_get_player(t_cub *cub, size_t x, size_t y)
{
	if (cub->map[x][y].value == 'N' || cub->map[x][y].value == 'S' || cub->map[x][y].value == 'W' || cub->map[x][y].value == 'E')
	{
		if (cub->player->x_start != 0 || cub->player->y_start != 0 || cub->player->dir != 0)
			ft_error(cub, "Invalid map already a player", -1, -1);
		cub->player->dir = cub->map[x][y].value;
		cub->player->x_start = x;
		cub->player->y_start = y;
		cub->player->x_cur = x;
		cub->player->y_cur = y;
	}
}

void	ft_check_if_valid_map(t_cub *cub)
{
    size_t x;
    size_t y;

    x = 1;
    while (cub->map[x] && x < cub->parse->map_height - 1)
    {
        y = 1;
        while (cub->map[x][y].value && y < cub->parse->map_width - 1)
        {
			ft_get_player(cub, x, y);
            if (cub->map[x][y].value == ' ' && cub->map[x][y].used == false)
			{
				// printf("inside -> [%zu][%zu] = %c\n", x, y, cub->map[x][y].value);
				ft_check_inside(cub, x, y);
			}
            y++;
        }
        x++;
    }
}

void	ft_verif_color(t_cub *cub)
{
	if (cub->parse->F.r <= -1 || cub->parse->F.g <= -1 || cub->parse->F.b <= -1 || cub->parse->C.r <= -1 || cub->parse->C.g <= -1 || cub->parse->C.b <= -1)
		ft_error(cub, "Invalid color", -1, -1);
}

t_cell **ft_verif_map(t_cub *cub, t_cell **map)
{
	ft_check_borders(cub);
	ft_check_if_valid_map(cub);
	ft_verif_color(cub);
    return (map);
}

// Vérifie si la ligne est valide (1, 0 , N, S, W, E)
int	ft_check_line(t_cub *cub, char *line)
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	ft_verif_data(cub);
	while (line[i])
	{
		if (!ft_is_delimiter(line[i]) && line[i] != '1' \
			&& line[i] != '0' && line[i] != 'N' && line[i] \
			!= 'S' && line[i] != 'W' && line[i] != 'E')
		{
			ft_error(cub, "Invalid map", line[i], -1);
			exit(1);
		}
		if (line[i] == ' ' || line[i] == '1' || line[i] == 'N' || line[i] \
			== 'S' || line[i] == 'W' || line[i] == 'E')
			check = 1;
		i++;
	}
	// printf("\n");
	if (check == 1)
		return (1);
	return (0);
}