/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:37 by gchamore          #+#    #+#             */
/*   Updated: 2024/07/19 12:23:45 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_map(char **map, int map_width, int map_height)
{
    int	i;
    int	j;

    i = 0;
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
            break ; // Skip this iteration
        }
        j = 0;
        while (j < map_width)
        {
            printf("%c", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

char	**ft_mod_split(char *str, t_cub *cub)
{
    size_t		i;
    char	**split;
    size_t	len;
	int		tmp;

	i = 0;
	tmp = 0;
    len = cub->parse->map_width;
	// printf("len = %zu\n", len);
	// printf("str = %s\n", str);
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

char	*ft_if_only_blanks(char *str)
{
    int	i;
    char *tmp;
    int	check;

    i = 0;
    tmp = str;
    check = 0;
    // Modifier la condition pour ignorer '\n'
    while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
        i++;
    // Vérifier si on a un caractère autre que '\0' et qui n'est pas un délimiteur
    if (tmp[i] != '\0' && tmp[i] != '\n' && !ft_is_delimiter(tmp[i]))
        check = 1;
    i = 0;
    while (tmp[i] && check == 0)
    {
        if (tmp[i] == ' ' || tmp[i] == '\t')
        {
            str = ft_strtrim(tmp, " \t");
            free(tmp);
            tmp = str;
            i = 0;
            continue ;
        }
        i++;
    }
    return (str);
}

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