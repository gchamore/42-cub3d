/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:38:56 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/06 11:37:06 by anferre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verif_fill_data(t_cub *cub, char *line, int i)
{
	verif_if_double_and_valid(cub, line);
	while (line[i] && cub->parse->ct != 7)
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (cub->parse->ct < 6 && (line[i] == '1' || line[i] == '0' || \
		(line[i] == 'N' && line[i + 1] != 'O') || (line[i] == 'S' && \
		line[i + 1] != 'O') || (line[i] == 'W' && line[i + 1] != 'E') || \
		(line[i] == 'E' && line[i + 1] != 'A')))
		{
			free(line);
			ft_error(cub, "Invalid data", -1, -1);
		}
		else if (cub->parse->ct == 6 && (line[i] == '1' || line[i] == '0' || \
		(line[i] == 'N' && line[i + 1] != 'O') || (line[i] == 'S' && \
		line[i + 1] != 'O') || (line[i] == 'W' && line[i + 1] != 'E') || \
		(line[i] == 'E' && line[i + 1] != 'A')))
		{
			cub->parse->total_infos = cub->parse->total_height;
			cub->parse->ct = 7;
		}
		else
			break ;
	}
}

void	verif_if_double_and_valid(t_cub *cub, char *line)
{
	if (line[0] != '\n' && line[0] != '\0' && !ft_strchr(line, '1') && \
	!ft_strchr(line, '0') && !ft_strchr(line, 'N') && !ft_strchr(line, 'S') \
	&& !ft_strchr(line, 'W') && !ft_strchr(line, 'E') && !ft_strchr(line, 'F') \
	&& !ft_strchr(line, 'C'))
	{
		free(line);
		ft_error(cub, "wrong data", -1, -1);
	}
	else if (ft_checker(line, 'N', 'O') == 1 && cub->parse->ct <= 6)
		cub->verif.no++;
	else if (ft_checker(line, 'S', 'O') == 1 && cub->parse->ct <= 6)
		cub->verif.so++;
	else if (ft_checker(line, 'W', 'E') == 1 && cub->parse->ct <= 6)
		cub->verif.we++;
	else if (ft_checker(line, 'E', 'A') == 1 && cub->parse->ct <= 6)
		cub->verif.ea++;
	else if (ft_checker(line, 'F', '\0') == 1 && cub->parse->ct <= 6)
		cub->verif.f++;
	else if (ft_checker(line, 'C', '\0') == 1 && cub->parse->ct <= 6)
		cub->verif.c++;
}

//Rempli les variables NO, SO, WE, EA, F, C, map
int	ft_fill_utility(t_cub *cub, char *line)
{
	char	*tmp;

	if (ft_strnstr(line, "NO ", ft_strlen(line)))
		return (cub->parse->no = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"NO ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_strnstr(line, "SO ", ft_strlen(line)))
		return (cub->parse->so = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"SO ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_strnstr(line, "WE ", ft_strlen(line)))
		return (cub->parse->we = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"WE ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_strnstr(line, "EA ", ft_strlen(line)))
		return (cub->parse->ea = ft_if_blanks(ft_substr(ft_strnstr(line, \
		"EA ", ft_strlen(line)), 3, ft_strlen(line) - 3)), cub->parse->ct++, 1);
	else if (ft_strnstr(line, "F ", ft_strlen(line)))
		return (tmp = ft_substr(ft_strnstr(line, "F ", ft_strlen(line)), 2, \
		ft_strlen(line) - 2), cub->parse->f = ft_get_rgb(cub->parse->f, tmp), \
		cub->parse->ct++, free(tmp), 1);
	else if (ft_strnstr(line, "C ", ft_strlen(line)))
		return (tmp = ft_substr(ft_strnstr(line, "C ", ft_strlen(line)), 2, \
		ft_strlen(line) - 2), cub->parse->c = ft_get_rgb(cub->parse->c, tmp), \
		cub->parse->ct++, free(tmp), 1);
	else
		ft_fill_utility_map(cub, line, NULL);
	return (0);
}

void	ft_fill_utility_map(t_cub *cub, char *line, char *tmp)
{
	if (line[0] == '\n')
	{
		cub->parse->total_newline++;
		if (cub->parse->check_newline == 1)
			cub->parse->check_newline = 2;
	}
	else if (line[0] != '\n' && (ft_strchr(line, '1') || \
	ft_strchr(line, '0') || ft_strchr(line, 'N') || ft_strchr(line, 'S') || \
	ft_strchr(line, 'W') || ft_strchr(line, 'E')))
	{
		if (cub->parse->check_newline == 2)
		{
			free(line);
			ft_error(cub, "Invalid Newline inside map", -1, -1);
		}
		tmp = ft_strtrim(line, "\n");
		if (cub->parse->map_width < ft_strlen(tmp) && ft_strlen(tmp) != 0)
			cub->parse->map_width = ft_strlen(tmp);
		cub->parse->map_height++;
		cub->parse->check_newline = 1;
		free(tmp);
	}
}
