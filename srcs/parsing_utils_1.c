/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:37 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/21 15:08:20 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// imprime la map
void	ft_print_map(t_cub *cub, t_cell **map, int map_width, int map_height)
{
    int	i;
    int	j;

    i = 0;
	printf("map =");
	printf("\n\n");
	printf("map_width = %zu\n", cub->parse->map_width);
	printf("map_height = %zu\n", cub->parse->map_height);
	printf("total_height = %zu\n", cub->parse->total_height);
	printf("total_newline = %zu\n", cub->parse->total_newline);
	printf("total_infos = %zu\n", cub->parse->total_infos);
	printf("ct = %zu\n", cub->parse->ct);
	printf("NO = %s\n", cub->parse->NO);
	printf("SO = %s\n", cub->parse->SO);
	printf("WE = %s\n", cub->parse->WE);
	printf("EA = %s\n", cub->parse->EA);
	printf("floor->r = %d\n", cub->parse->F.r);
	printf("floor->g = %d\n", cub->parse->F.g);
	printf("floor->b = %d\n", cub->parse->F.b);
	printf("ceiling->r = %d\n", cub->parse->C.r);
	printf("ceiling->g = %d\n", cub->parse->C.g);
	printf("ceiling->b = %d\n", cub->parse->C.b);
	printf("player->dir = %c\n", cub->player->dir);
	printf("player location map start x->[%zu] y->[%zu]\n", cub->player->x_start, cub->player->y_start);
	printf("\n\n");
	if (map == NULL)
	{
        fprintf(stderr, "Error: map is NULL\n");
        return;
    }
    while (i < map_height)
    {
		if (map[i] == NULL)
		{
            fprintf(stderr, "Error: map[%d] is NULL\n", i);
            break ;
        }
        j = 0;
        while (j < map_width)
        {
            printf("%c", map[i][j].value);
            j++;
        }
        printf("\n");
        i++;
    }
}

// split la map
char	**ft_mod_split(char *str, t_cub *cub)
{
    size_t		i;
    char	**split;
    size_t	len;
	int		tmp;

	i = 0;
	tmp = 0;
    len = cub->parse->map_width;
    split = (char **)malloc(sizeof(char *) * (len + 1));
    if (!split)
	{
        return (NULL);
	}
    while (i < len)
    {
        split[i] = (char *)malloc(sizeof(char) * 2);
        if (!split[i])
        {
            while (i-- > 0)
                free(split[i]);
            free(split);
            return (NULL);
        }
		if (((i >= ft_strlen(str) || str[i] == '\n' || str[i] == '\0') && (i < len)) || tmp == 1)
		{
			split[i][0] = ' ';
			tmp = 1;
		}
		else
			split[i][0] = str[i];
    	split[i][1] = '\0';
		i++;
    }
    split[len] = NULL;
	return (split);
}

// SI QUE ESPACES ET TABS DANS LA LIGNE ALORS ON LES SUPPRIME
char	*ft_if_only_blanks(char *str)
{
    int	i;
    char *tmp;
    int	check;

    i = 0;
    tmp = str;
    check = 0;
    while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
        i++;
    if (tmp[i] != '\0' && tmp[i] != '\n' && !ft_is_delimiter(tmp[i]))
        check = 1;
    i = 0;
    if (check == 0)
    {
        str = ft_strtrim(tmp, " \t");
        free(tmp);
    }
    return (str);
}

// TRIM LES ESPACES ET TABS DE LA LIGNES AVANT ET APRES LE TEXTE
char	*ft_if_blanks(char *str)
{
	int	i;
	char *tmp;

	i = 0;
	if (str == NULL)
		return (NULL);
	tmp = str;
	str = ft_strtrim(tmp, " \t\n");
	if (str == NULL)
		return (str);
	free(tmp);
	return (str);
}

// char	*ft_if_blanks_after(char *str)
// {
//     char *tmp;
//     char *new_str;
//     char *trimmed_str;
//     int len;
//     int i;

//     if (str == NULL)
//         return (NULL);
//     tmp = str;
//     while (*tmp && (*tmp == ' ' || *tmp == '\t'))
//         tmp++;
//     len = strlen(tmp);
//     new_str = (char *)malloc(len + 1);
//     if (new_str == NULL)
//         return (NULL);
//     i = 0;
//     while (tmp[i])
//     {
// 		// printf ("%c->", tmp[i]);
//         new_str[i] = tmp[i];
// 		// printf ("%c|", new_str[i]);
//         i++;
//     }
// 	// printf ("\n");
//     new_str[i] = '\0';
// 	printf ("str_trim = %s\n", new_str);
//     trimmed_str = ft_strtrim(new_str, " \t\n");
//     free(new_str);
//     if (trimmed_str == NULL)
//         return (NULL);
//     return (trimmed_str);
// }