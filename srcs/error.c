/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:21:46 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/19 16:14:25 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_cub *cub, char *str, size_t x, size_t y)
{
	if (x == (size_t)-1 && y == (size_t)-1)
		printf("Error : %s\n", str);
	else
		printf("Error : %s at position map x=[%zu]y=[%zu] \n", str, x, y);
	ft_free_cub(cub);
	exit(1);
}