/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:37 by gchamore          #+#    #+#             */
/*   Updated: 2024/07/19 10:50:53 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

