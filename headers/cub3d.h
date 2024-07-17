/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:58:37 by gchamore          #+#    #+#             */
/*   Updated: 2024/07/17 17:32:43 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <fcntl.h> // Pour open
# include <unistd.h> // Pour close, read, write
# include <stdio.h> // Pour printf
# include <stdlib.h> // Pour malloc, free, exit
# include <string.h> // Pour strerror
# include <errno.h> // Pour perror
# include <math.h> // Pour tan, cos, sin, atan2, sqrt
# include <stdbool.h> // Pour les booleens


typedef struct s_parse
{
	size_t			map_height;
	size_t			map_width;
	size_t			total_height;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	char			*F;
	char			*C;
}	t_parse;

typedef struct s_point2d
{
	double		x;
	double		y;
}	t_point2d;

typedef struct s_point3d
{
	double		x;
	double		y;
	double		z;
}	t_point3d;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}	t_data;

typedef struct s_cub
{
	int			**map;
	t_data		*data;
	t_parse		*parse;
}	t_cub;

char	**ft_mod_split(char *str);
void	*ft_verif_str(char **split, char *str);
int	ft_is_delimiter(char c);
int	ft_words_count(char *str);
int	ft_one_word_len(char *str);
void	ft_free_split(char **split);
int	ft_count_rows(char	**tab);
void	ft_free_cub(t_cub *cub);
int	ft_fill_utility(t_cub *cub, char *line);

#endif