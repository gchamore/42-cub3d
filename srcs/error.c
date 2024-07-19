/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:21:46 by gchamore          #+#    #+#             */
/*   Updated: 2024/07/19 13:00:29 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_cub *cub, char *str, char c)
{
	if (c == ' ')
		printf("Error : %s\n", str);
	else
		printf("Error : %s on %c\n", str, c);
	ft_free_cub(cub);
	exit(1);
}