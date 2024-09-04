/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:21:46 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 16:35:51 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_cub *cub, char *str, size_t y, size_t x)
{
	if (y == (size_t)-1 && x == (size_t)-1)
		printf("Error : %s\n", str);
	else
		printf("Error : %s position map y=[%zu]x=[%zu] \n", str, y, x);
	ft_free_cub(cub);
	exit(1);
}
