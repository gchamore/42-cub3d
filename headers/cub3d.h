/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:58:37 by gchamore          #+#    #+#             */
/*   Updated: 2024/09/04 16:30:28 by gchamore         ###   ########.fr       */
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

// map_height = nombre de lignes de la map
// map_width = nombre de colonnes de la map
// total_infos = nombre de lignes d'infos dans le fichier avant map
// total_height = nombre de lignes total
// total_newline = nombre de lignes vides

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}	t_rgb;

typedef struct s_parse
{
	size_t			tmp_height;
	size_t			tmp_width;
	size_t			map_height;
	size_t			map_width;
	size_t			total_infos;
	size_t			total_height;
	size_t			total_newline;
	size_t			ct;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	t_rgb			F;
	t_rgb			C;
	int				check_newline;
}	t_parse;

typedef struct s_player
{
	size_t			y_start;
	size_t			x_start;
	size_t			y_cur;
	size_t			x_cur;
	char			dir;
}	t_player;

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

typedef struct s_cell
{
	char		value;
	bool		used;
	int			count;
	int			count_0;
}	t_cell;

typedef struct s_verif
{
	int			NO;
	int			SO;
	int			WE;
	int			EA;
	int			F;
	int			C;
}	t_verif;

typedef struct s_cub
{
	t_cell		**map;
	t_data		*data;
	t_parse		*parse;
	t_player	*player;
	t_verif		verif;
	int			fd;
	int			i;
}	t_cub;

//////////////////////////
//         MAIN         //
//////////////////////////

//main.c
int	main(int argc, char **argv);

//////////////////////////
//         INIT         //
//////////////////////////

//init.c
void	ft_create_cub(t_cub **cub);
void	ft_init_structs(t_cub *cub);
void	ft_init_info(t_cub *cub);
void	ft_init_map(t_cub *cub, size_t y, size_t x, char val);
void	ft_init_cub_map(t_cub *cub);

//////////////////////////
//        PARSING       //
//////////////////////////

//parsing.c
int	ft_parsing(t_cub *cub, char **argv);
int	ft_get_data(char *file, t_cub *cub, char *line);
t_cell	**ft_fill_all(char *file, t_cub *cub);
t_cell	**ft_verif_data(t_cub *cub, t_cell **map);

//parse_data.c
void	verif_fill_data(t_cub *cub, char *line, int i);
void	verif_if_double_and_valid(t_cub *cub, char *line);
int		ft_fill_utility(t_cub *cub, char *line);
void	ft_fill_utility_map(t_cub *cub, char *line, char *tmp);

//parse_fill.c
void	ft_prepare(t_cub *cub, char *line, size_t j);
void	ft_fill_map(t_cub *cub, char *line, char **split, size_t j);
int	ft_check_line(t_cub *cub, char *line);
void	ft_check_data(t_cub *cub, char *line);

//parse_rgb.c
char	*ft_verify_rgb(char *str);
t_rgb	ft_get_rgb(t_rgb rgb, char *str);

//parse_utils.c
int		ft_checker(char *line, char one, char two);
char	**ft_mod_split(char *str, t_cub *cub, size_t i, int tmp);
char	*ft_if_only_blanks(char *str);
char	*ft_if_blanks(char *str);
int		ft_is_delimiter(char c);

//////////////////////////
//        VERIFS        //
//////////////////////////

//verif.c
void	ft_check_if_valid_map(t_cub *cub);
void	ft_check_inside(t_cub *cub, size_t y, size_t x);
int	ft_is_valid(t_cub *cub, size_t y, size_t x);
void	ft_get_player(t_cub *cub, size_t y, size_t x);

//verif_arround_map.c
void	ft_check_borders(t_cub *cub, size_t y, size_t x);
void	ft_check_corners_1(t_cub *cub, size_t y, size_t x);
void	ft_check_corners_2(t_cub *cub, size_t y, size_t x);
void	ft_check_sides_1(t_cub *cub, size_t y, size_t x);
void	ft_check_sides_2(t_cub *cub, size_t y, size_t x);

//verif_algo.c
int	ft_check_arround_1(t_cub *cub, size_t y, size_t x);
int	ft_check_map_direction(t_cub *cub, size_t y, size_t x);
int	ft_count(t_cub *cub, size_t y, size_t x, char value);
int	ft_check_diag(t_cub *cub, size_t y, size_t x, char value);

//verif_algo_direction_1.c
int	ft_verif_right(t_cub *cub, size_t y, size_t x);
int	ft_verif_right_down(t_cub *cub, size_t y, size_t x);
int	ft_verif_down(t_cub *cub, size_t y, size_t x);
int	ft_verif_left_down(t_cub *cub, size_t y, size_t x);

//verif_algo_direction_2.c
int	ft_verif_left(t_cub *cub, size_t y, size_t x);
int	ft_verif_left_up(t_cub *cub, size_t y, size_t x);
int	ft_verif_up(t_cub *cub, size_t y, size_t x);
int	ft_verif_right_up(t_cub *cub, size_t y, size_t x);

//verif_utils.c
void	ft_reset_map(t_cub *cub);
void	ft_check_cell(t_cub *cub, size_t y, size_t x);

//////////////////////////
//        DESTROY       //
//////////////////////////

//destroy.c
void	ft_free_map(t_cell **map, int map_height);
void	ft_free_cub(t_cub *cub);
void	ft_free_split(char **split);

//////////////////////////
//        ERROR         //
//////////////////////////

//error.c
void	ft_error(t_cub *cub, char *str, size_t y, size_t x);

#endif