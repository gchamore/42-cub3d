/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anferre <anferre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:58:37 by gchamore          #+#    #+#             */
/*   Updated: 2024/08/19 16:30:23 by anferre          ###   ########.fr       */
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
# define WIN_HEIGTH 1080
# define WIN_WIDTH 1920

# define TILE_SIZE 64
# define PLAYER_SIZE 16
# define FOV 60

# define RED_COLOR 0xFF0000
# define GREEN_COLOR 0xEFFBEF
# define BLUE_COLOR 0x0000FF
# define WHITE_COLOR 0xFFFFFF
# define BLACK_COLOR 0x000000
# define GREY_COLOR 0x808080

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}	t_rgb;

typedef struct s_parse
{
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
	// t_rgb			floor;
	// t_rgb			ceiling;
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

typedef struct s_cell
{
	char		value;
	bool		used;
	int			count;
	bool		end;
}	t_cell;

typedef struct s_cub
{
	t_cell		**map;
	size_t		x_start;
	size_t		y_start;
	int 		exit;
	int			check;
	int			mooves;
	t_data		*data;
	t_parse		*parse;
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

//////////////////////////
//        PARSING       //
//////////////////////////

//parsing.c
int	ft_parsing(int fd, t_cub *cub, char **argv);
int	ft_get_data(char *file, t_cub *cub);
int	ft_fill_utility(t_cub *cub, char *line);
t_cell	**ft_fill_tab(int fd, t_cub *cub);

//parsing_verif.c
int ft_check_if_valid_map(t_cub *cub, size_t x, size_t y);
t_cell **ft_verif_map(t_cub *cub, t_cell **map);
int	ft_check_line(t_cub *cub, char *line);

//parsing_utils_1.c
void	ft_print_map(t_cub *cub, t_cell **map, int map_width, int map_height);
char	**ft_mod_split(char *str, t_cub *cub);
char	*ft_if_only_blanks(char *str);
char	*ft_if_blanks(char *str);

//parsing_utils_2.c
int	ft_is_delimiter(char c);
t_rgb	ft_get_rgb(t_rgb rgb, char *str);

//////////////////////////
//        DESTROY       //
//////////////////////////

//destroy.c
void	ft_free_cub(t_cub *cub);
void	ft_free_map(t_cell **map, int map_height);
void	ft_free_split(char **split);

//////////////////////////
//        ERROR         //
//////////////////////////

//error.c
void		ft_error(t_cub *cub, char *str, char c);


//////////////////////////
//        RENDERING     //
//////////////////////////

//render.c
void		ft_project(t_cub *cub);

//mlx_utils.c
int			ft_init_mlx(t_cub *cub);
void		ft_mpp(t_img *img, int x, int y, int color);

#endif