/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:22:42 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/16 18:53:29 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// Compte le nombre de 1 autour de la case pour connaitre le nombre 
// de chemins possibles depuis cette case et revenir a la case precedente si besoin
void	ft_count_1(t_cub *cub, size_t x, size_t y)
{
	if (cub->map[x][y].value == '1')
	{
		if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == false)
			cub->map[x][y].count++;
		if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == false)
			cub->map[x][y].count++;
		if (y > 0 && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].count == 0 && cub->map[x][y - 1].used == false)
			cub->map[x][y].count++;
		if (x > 0 && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].count == 0 && cub->map[x - 1][y].used == false)
			cub->map[x][y].count++;
	}	
}

// Vérifie si il y a la case de fin accessible autour de la case actuelle
int	ft_check_end(t_cub *cub, size_t x, size_t y)
{
	int i;

	i = 0;
	if (cub->map[x][y].value == '1')
	{
		if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == true && cub->map[x][y + 1].end == true)
			return (printf("map = [%zu][%zu]\n", x, y + 1), 0);
		if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == true && cub->map[x + 1][y].end == true)
			return (printf("map = [%zu][%zu]\n", x + 1, y), 0);
		if (y > 0 && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].used == true && cub->map[x][y - 1].end == true)
			return (printf("map = [%zu][%zu]\n", x, y - 1), 0);
		if (x > 0 && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].used == true && cub->map[x - 1][y].end == true)
			return (printf("map = [%zu][%zu]\n", x - 1, y), 0);
	}
	return (1);
}

// Vérifie si la map est bien fermee algo principale check droite -> bas -> gauche -> haut
// check sert a savoir de combien on avance et si on fait demi tour afin de ne pas toucher end en revenant en arriere
// count sert a savoir combien de 1 il y a autour de la case actuelle cf ft_count_1
// je vais serparer chaque direction en fonction individuelle pour plus de clarte
int ft_check_if_valid_map(t_cub *cub, size_t x, size_t y)
{
	if (!cub || !cub->parse || x >= cub->parse->map_height || y >= cub->parse->map_width)
        return (0);
	cub->check++;
	if (cub->map[x][y].value != '1' || cub->check == 0)
        return (ft_error(cub, "Invalid map", cub->map[x][y].value), 1);
	printf("map = [%zu][%zu]\n", x, y);
	cub->map[x][y].used = true;
	ft_count_1(cub, x, y);
	if (cub->map[x][y].count == 0)
	{
		if (ft_check_end(cub, x, y) == 0 && cub->check >= 4)
			return (printf("THE END !"), 0);
		else
			return (1);
	}
	if (ft_check_end(cub, x, y) == 0 && cub->check >= 4)
			return (printf("THE END !"), 0);
    if (y + 1 < cub->parse->map_width && cub->map[x][y + 1].value != '\0' && cub->map[x][y + 1].value == '1' && cub->map[x][y + 1].used == false && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if ((x > 0 && cub->map[x - 1][y].value == '0'))
		{
			printf("\nUnvalid path at [%zu][%zu]\n\n", x, y);
			return (1);
		}
		if (ft_check_if_valid_map(cub, x, y + 1) == 0)
			return (0);
		else
		{
			cub->check--;
			printf("go back at -> [%zu][%zu]\n", x, y + 1);
		}	
	}
    if (x + 1 < cub->parse->map_height && cub->map[x + 1][y].value != '\0' && cub->map[x + 1][y].value == '1' && cub->map[x + 1][y].used == false && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if ((y + 1 < cub->parse->map_width && cub->map[x][y + 1].value == '0'))
		{
			printf("\nUnvalid path at [%zu][%zu]\n\n", x, y);
			return (1);
		}
		if (ft_check_if_valid_map(cub, x + 1, y) == 0)
			return (0);
		else
		{
			cub->check--;
			printf("go back at -> [%zu][%zu]\n", x + 1, y);
		}	
	}
    if (y > 0 && cub->map[x][y].value == '1' && cub->map[x][y - 1].value == '1' && cub->map[x][y - 1].used == false && cub->map[x][y].count >= 1 && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if ((x + 1 < cub->parse->map_height && cub->map[x + 1][y].value == '0'))
		{
			printf("\nUnvalid path at [%zu][%zu]\n\n", x, y);
			return (1);
		}
		if (ft_check_if_valid_map(cub, x, y - 1) == 0)
			return (0);
		else
		{
			cub->check--;
			printf("go back at -> [%zu][%zu]\n", x, y - 1);
		}
	}
    if (x > 0 && cub->map[x][y].value == '1' && cub->map[x - 1][y].value == '1' && cub->map[x - 1][y].used == false && cub->map[x][y].count >= 1 && cub->map[x][y].count >= 1)
	{
		cub->map[x][y].count--;
		if ((y > 0 && cub->map[x][y - 1].value == '0'))
		{
			printf("\nUnvalid path at [%zu][%zu]\n\n", x, y);
			return (1);
		}
		if (ft_check_if_valid_map(cub, x - 1, y) == 0)
			return (0);
		else
		{
			cub->check--;
			printf("go back at -> [%zu][%zu]\n", x - 1, y);
		}
	}
	return (1);
}

// Trouve la case de depart de la map pour commencer l'algo de verification
// afin d'eviter de commencer sur une case non valide sur laquelle on ne peut pas boucler
//exemple :
//            1
//           111
//            1
// start -> 1111
//          1001
//          1111
// le 1 avec start est la case de depart et il sera marque comme end
void	ft_get_map_start(t_cub *cub)
{
    size_t x;
    size_t y;

    x = 0;
    while (cub->map[x])
    {
        y = 0;
        while (cub->map[x][y].value)
        {
            if (y > 0 && x + 1 < cub->parse->map_height && y + 1 < cub->parse->map_width)
            {
                if (cub->map[x][y].value == '1' && cub->map[x][y + 1].value == '1' && cub->map[x + 1][y].value == '1' && (cub->map[x + 1][y + 1].value == '0' || cub->map[x + 1][y + 1].value == '1' || cub->map[x + 1][y + 1].value == 'N' || cub->map[x + 1][y + 1].value == 'S' || cub->map[x + 1][y + 1].value == 'W' || cub->map[x + 1][y + 1].value == 'E'))
                {
                    cub->map[x][y].end = true;
                    cub->x_start = x;
                    cub->y_start = y;
					return ;
                }
            }
            y++;
        }
        x++;
    }
}

// Vérifie si la map est valide
t_cell **ft_verif_map(t_cub *cub, t_cell **map)
{
	printf ("map_height = %zu\n", cub->parse->map_height);
	printf ("map_width = %zu\n", cub->parse->map_width);

	ft_get_map_start(cub);
	if (ft_check_if_valid_map(cub, cub->x_start, cub->y_start) == 0)
		return (printf("YEAAAAAAH \n\n"), map);
	else
		return (printf("NOOOOO \n\n"), NULL);
    return (map);
}

// Vérifie si la ligne est valide (1, 0 , N, S, W, E)
int	ft_check_line(t_cub *cub, char *line)
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	while (line[i])
	{
		if (!ft_is_delimiter(line[i]) && line[i] != '1' \
			&& line[i] != '0' && line[i] != 'N' && line[i] \
			!= 'S' && line[i] != 'W' && line[i] != 'E')
		{
			ft_error(cub, "Invalid map", line[i]);
			exit(1);
		}
		if (line[i] == '1' || line[i] == 'N' || line[i] \
			== 'S' || line[i] == 'W' || line[i] == 'E')
			check = 1;
		i++;
	}
	if (check == 1)
		return (1);
	return (0);
}