# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anferre <anferre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 09:49:54 by gchamore          #+#    #+#              #
#    Updated: 2024/09/04 17:00:28 by anferre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -I./headers/

RM = rm -rf

SRCS_DIR = srcs

SRCS_DIR_BONUS = srcs_bonus

SRCS = $(addprefix $(SRCS_DIR)/,	\
	main.c							\
	init.c							\
	error.c							\
	destroy.c						\
	parsing.c						\
	parse_data.c					\
	parse_fill.c					\
	parse_rgb.c						\
	parse_utils.c					\
	utils_a_delete.c				\
	verif_algo_direction_1.c		\
	verif_algo_direction_2.c		\
	verif_algo.c					\
	verif_arround_map.c				\
	verif_utils.c					\
	verif.c							\
	project.c						\
	project_key.c					\
	project_utils.c					\
	mlx_utils.c						\
	ray_casting.c					\
	ray_casting_utils.c				\
	ray_casting_utils_2.c			\
	texture.c						\
	)

SRCS_BONUS = $(addprefix $(SRCS_DIR_BONUS)/,	\
	main_bonus.c					\
	init_bonus.c					\
	parsing_bonus.c					\
	parse_data_bonus.c				\
	parse_fill_bonus.c				\
	parse_rgb_bonus.c				\
	parse_utils_bonus.c				\
	verif_algo_bonus.c				\
	verif_algo_direction_1_bonus.c	\
	verif_algo_direction_2_bonus.c	\
	verif_arround_map_bonus.c		\
	verif_bonus.c					\
	verif_utils_bonus.c				\
	destroy_bonus.c					\
	error_bonus.c					\
	project_bonus.c					\
	project_key_bonus.c				\
	project_utils_bonus.c			\
	project_utils_2_bonus.c			\
	mlx_utils_bonus.c				\
	ray_casting_bonus.c				\
	ray_casting_utils_bonus.c		\
	ray_casting_utils_2_bonus.c		\
	texture_bonus.c					\
	project_minimap_bonus.c			\
	)

OBJ_DIR = objs

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

OBJS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

OBJS_TARGET = $(OBJS)

ifeq ($(MAKECMDGOALS),bonus)
    OBJS_TARGET = $(OBJS_BONUS)
endif

DEPS = $(OBJS:.o=.d) $(OBJS_BONUS:.o=.d)

all: first_header $(NAME) second_header

$(NAME): $(OBJS_TARGET)
	$(MAKE) -sC ./libft
	$(MAKE) -sC ./minilibx
	$(CC) $(CFLAGS) -o $@ $^ libft/libft.a minilibx/libmlx.a -lXext -lX11 -lm

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC)  $(CFLAGS) -MMD -c -o $@ $<

bonus: $(NAME)

clean:
	$(MAKE) clean -sC ./libft
	$(MAKE) clean -sC ./minilibx
	$(RM) $(OBJS) $(OBJS_BONUS) $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

info: header

-include $(DEPS)

first_header:
	@echo "\n $$FIRST_HEADER \n"

define FIRST_HEADER

⠀⠀⠀⠀⠀⠀⠀⠀⠀⡴⠞⠉⢉⣭⣿⣿⠿⣳⣤⠴⠖⠛⣛⣿⣿⡷⠖⣶⣤⡀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣼⠁⢀⣶⢻⡟⠿⠋⣴⠿⢻⣧⡴⠟⠋⠿⠛⠠⠾⢛⣵⣿⠀⠀⠀⠀
⣼⣿⡿⢶⣄⠀⢀⡇⢀⡿⠁⠈⠀⠀⣀⣉⣀⠘⣿⠀⠀⣀⣀⠀⠀⠀⠛⡹⠋⠀⠀⠀⠀
⣭⣤⡈⢑⣼⣻⣿⣧⡌⠁⠀⢀⣴⠟⠋⠉⠉⠛⣿⣴⠟⠋⠙⠻⣦⡰⣞⠁⢀⣤⣦⣤⠀
⠀⠀⣰⢫⣾⠋⣽⠟⠑⠛⢠⡟⠁⠀⠀⠀⠀⠀⠈⢻⡄⠀⠀⠀⠘⣷⡈⠻⣍⠤⢤⣌⣀
⢀⡞⣡⡌⠁⠀⠀⠀⠀⢀⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⢿⡀⠀⠀⠀⠸⣇⠀⢾⣷⢤⣬⣉
⡞⣼⣿⣤⣄⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⣿⠀⠸⣿⣇⠈⠻
⢰⣿⡿⢹⠃⠀⣠⠤⠶⣼⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⣿⠀⠀⣿⠛⡄⠀
⠈⠉⠁⠀⠀⠀⡟⡀⠀⠈⡗⠲⠶⠦⢤⣤⣤⣄⣀⣀⣸⣧⣤⣤⠤⠤⣿⣀⡀⠉⣼⡇⠀
⣿⣴⣴⡆⠀⠀⠻⣄⠀⠀⠡⠀⠀⠀⠈⠛⠋⠀⠀⠀⡈⠀⠻⠟⠀⢀⠋⠉⠙⢷⡿⡇⠀
⣻⡿⠏⠁⠀⠀⢠⡟⠀⠀⠀⠣⡀⠀⠀⠀⠀⠀⢀⣄⠀⠀⠀⠀⢀⠈⠀⢀⣀⡾⣴⠃⠀
⢿⠛⠀⠀⠀⠀⢸⠁⠀⠀⠀⠀⠈⠢⠄⣀⠠⠼⣁⠀⡱⠤⠤⠐⠁⠀⠀⣸⠋⢻⡟⠀⠀
⠈⢧⣀⣤⣶⡄⠘⣆⠀⠀⠀⠀⠀⠀⠀⢀⣤⠖⠛⠻⣄⠀⠀⠀⢀⣠⡾⠋⢀⡞⠀⠀⠀
⠀⠀⠻⣿⣿⡇⠀⠈⠓⢦⣤⣤⣤⡤⠞⠉⠀⠀⠀⠀⠈⠛⠒⠚⢩⡅⣠⡴⠋⠀⠀⠀⠀
⠀⠀⠀⠈⠻⢧⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⣻⠿⠋⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠉⠓⠶⣤⣄⣀⡀⠀⠀⠀⠀⠀⢀⣀⣠⡴⠖⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀

endef
export FIRST_HEADER

second_header:
	@echo "\n$$SECOND_HEADER \n"

define SECOND_HEADER
██████████████████████████████████████████████████████████████████████
█▌                                                                  ▐█
█▌                                                                  ▐█
█▌  ██╗  ██╗██████╗     ██████╗  ██████╗ ██████╗ ███╗   ██╗         ▐█
█▌  ██║  ██║╚════██╗    ██╔══██╗██╔═══██╗██╔══██╗████╗  ██║         ▐█
█▌  ███████║ █████╔╝    ██████╔╝██║   ██║██████╔╝██╔██╗ ██║         ▐█
█▌  ╚════██║██╔═══╝     ██╔══██╗██║   ██║██╔══██╗██║╚██╗██║         ▐█
█▌       ██║███████╗    ██████╔╝╚██████╔╝██║  ██║██║ ╚████║         ▐█
█▌       ╚═╝╚══════╝    ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝         ▐█
█▌                                                                  ▐█
█▌  ████████╗ ██████╗      ██████╗ ██████╗ ██████╗ ███████╗    ██╗  ▐█
█▌  ╚══██╔══╝██╔═══██╗    ██╔════╝██╔═══██╗██╔══██╗██╔════╝    ██║  ▐█
█▌     ██║   ██║   ██║    ██║     ██║   ██║██║  ██║█████╗      ██║  ▐█
█▌     ██║   ██║   ██║    ██║     ██║   ██║██║  ██║██╔══╝      ╚═╝  ▐█
█▌     ██║   ╚██████╔╝    ╚██████╗╚██████╔╝██████╔╝███████╗    ██╗  ▐█
█▌     ╚═╝    ╚═════╝      ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝    ╚═╝  ▐█
█▌                                                                  ▐█
█▌                                                                  ▐█
█▌                                                                  ▐█
██████████████████████████████████████████████████████████████████████
endef
export SECOND_HEADER

header:
	@echo "$$FIRST_HEADER"
	@echo "$$SECOND_HEADER"
