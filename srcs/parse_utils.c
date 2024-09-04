/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:38:03 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 16:34:39 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_checker(char *line, char one, char two)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == one)
		{
			if (two == '\0')
				return (1);
			else
			{
				if (line[i + 1] == two)
					return (1);
				else
				{
					i++;
					continue ;
				}
			}
		}
		i++;
	}
	return (0);
}

// split la map
char	**ft_mod_split(char *str, t_cub *cub, size_t i, int tmp)
{
	char	**split;
	size_t	len;

	len = cub->parse->map_width;
	split = (char **)malloc(sizeof(char *) * (len + 1));
	if (!split)
		return (NULL);
	while (i < len)
	{
		split[i] = (char *)malloc(sizeof(char) * 2);
		if (!split[i])
			return (ft_free_split(split), NULL);
		if (((i >= ft_strlen(str) || str[i] == '\n' || str[i] == '\0') && \
		(i < len)) || tmp == 1)
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
	int		i;
	char	*tmp;
	int		check;

	i = 0;
	tmp = str;
	check = 0;
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
	{
		i++;
	}
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
	int		i;
	char	*tmp;

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

// Retourne 1 si c est un delimiteur, 0 sinon
int	ft_is_delimiter(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}
