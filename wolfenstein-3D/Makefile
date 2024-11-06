# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 16:20:15 by alassiqu          #+#    #+#              #
#    Updated: 2024/11/06 23:23:38 by alassiqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cub3D
BONUS		:=	cub3D_bonus

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror #-fsanitize=address -g3

LXFLAGS		:=	-I /usr/local/include -L /usr/local/lib -lmlx -lXext -lX11 -lm
MCFLAGS		:=	-L ../mlx -lmlx -framework OpenGL -framework AppKit

RM			:=	rm -f

# Colors
GREEN		:=	\033[1;32m
RED			:=	\033[1;31m
RESET		:=	\033[0m
YELLOW		:=	\033[1;33m
UCYAN		:=	\033[0;34m

# This is mandatory libs.
LIBS		:=	libs/get-next-line/get_next_line.c			\
				libs/get-next-line/get_next_line_utils.c	\
				manda/free_mem.c

# This is bonus libs.
LIBS_B		:=	libs/get-next-line/get_next_line.c			\
				libs/get-next-line/get_next_line_utils.c	\
				bonus/free_mem.c

# This is mandatory parsing.
PARSING		:=	manda/parsing/colors.c						\
				manda/parsing/files.c						\
				manda/parsing/map_utils.c					\
				manda/parsing/map.c							\
				manda/parsing/math.c						\
				manda/parsing/parsing.c						\
				manda/parsing/player.c						\
				manda/parsing/textures.c					\
				manda/parsing/utils.c

# This is bonus parsing.
PARSING_B	:=	bonus/parsing/colors_bonus.c				\
				bonus/parsing/files_bonus.c					\
				bonus/parsing/map_utils_bonus.c				\
				bonus/parsing/map_bonus.c					\
				bonus/parsing/math_bonus.c					\
				bonus/parsing/parsing_bonus.c				\
				bonus/parsing/player_bonus.c				\
				bonus/parsing/textures_bonus.c				\
				bonus/parsing/utils_bonus.c

# This is mandatory execution.
EXECUTING	:=	manda/executing/cub_loop.c					\
				manda/executing/dda_and_wall_draw.c			\
				manda/executing/hooking.c					\
				manda/executing/ray_distance.c				\
				manda/executing/wall.c
				
# This is bonus execution.
EXECUTING_B	:=	bonus/executing/animation_bonus.c			\
				bonus/executing/animation_utils_bonus.c		\
				bonus/executing/collision_bonus.c			\
				bonus/executing/cub_loop_bonus.c			\
				bonus/executing/dda_and_wall_draw_bonus.c	\
				bonus/executing/hooking_bonus.c				\
				bonus/executing/minimap_bonus.c				\
				bonus/executing/ray_distance_bonus.c

# Mandatory sources.
SRCS		:=	$(LIBS)										\
				$(PARSING)									\
				$(EXECUTING)								\
				manda/cub3d.c

# Bonus sources.
SRCS_B		:=	$(LIBS_B)									\
				$(PARSING_B)								\
				$(EXECUTING_B)								\
				bonus/cub3d_bonus.c

# Libft library.
LIBFT		:=	libs/libft/libft.a

# Mandatory and bonus object files.
OBJS		:=	$(SRCS:.c=.o)
OBJS_B		:=	$(SRCS_B:.c=.o)

# Rules to make mandatory and bonus.
all:		$(NAME)
bonus:		$(BONUS)

# Mnadatory ASCII-ART
ASCII_ART_M	:=	"\
\n\
\n\
███╗   ███╗ █████╗ ███╗   ██╗██████╗  █████╗      ██████╗██╗   ██╗██████╗       ██╗███████╗      ██████╗ ██████╗ ██████╗ \n\
████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔══██╗    ██╔════╝██║   ██║██╔══██╗      ██║██╔════╝      ██╔══██╗██╔══██╗██╔══██╗\n\
██╔████╔██║███████║██╔██╗ ██║██║  ██║███████║    ██║     ██║   ██║██████╔╝█████╗██║███████╗█████╗██║  ██║██║  ██║██║  ██║\n\
██║╚██╔╝██║██╔══██║██║╚██╗██║██║  ██║██╔══██║    ██║     ██║   ██║██╔══██╗╚════╝██║╚════██║╚════╝██║  ██║██║  ██║██║  ██║\n\
██║ ╚═╝ ██║██║  ██║██║ ╚████║██████╔╝██║  ██║    ╚██████╗╚██████╔╝██████╔╝      ██║███████║      ██████╔╝██████╔╝██████╔╝\n\
╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝ ╚═╝  ╚═╝     ╚═════╝ ╚═════╝ ╚═════╝       ╚═╝╚══════╝      ╚═════╝ ╚═════╝ ╚═════╝ \n\
\n\
"

# Bonus ASCII-ART
ASCII_ART_B	:=	"\
\n\
\n\
██████╗  ██████╗ ███╗   ██╗██╗   ██╗███████╗     ██████╗██╗   ██╗██████╗       ██╗███████╗      ██████╗ ██████╗ ██████╗ \n\
██╔══██╗██╔═══██╗████╗  ██║██║   ██║██╔════╝    ██╔════╝██║   ██║██╔══██╗      ██║██╔════╝      ██╔══██╗██╔══██╗██╔══██╗\n\
██████╔╝██║   ██║██╔██╗ ██║██║   ██║███████╗    ██║     ██║   ██║██████╔╝█████╗██║███████╗█████╗██║  ██║██║  ██║██║  ██║\n\
██╔══██╗██║   ██║██║╚██╗██║██║   ██║╚════██║    ██║     ██║   ██║██╔══██╗╚════╝██║╚════██║╚════╝██║  ██║██║  ██║██║  ██║\n\
██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████║    ╚██████╗╚██████╔╝██████╔╝      ██║███████║      ██████╔╝██████╔╝██████╔╝\n\
╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝     ╚═════╝ ╚═════╝ ╚═════╝       ╚═╝╚══════╝      ╚═════╝ ╚═════╝ ╚═════╝ \n\
\n\
"

$(LIBFT):
	@echo "$(RED)** Building Libft. **$(YELLOW)"
	@make -C libs/libft
	@echo "$(RED)** Libft builded succesfully. **$(RESET)"

$(NAME)	:	$(LIBFT) $(OBJS)
	@echo "$(RED)** Linking. **$(YELLOW)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MCFLAGS) -o $(NAME)
	@printf "$(UCYAN)"
	@printf $(ASCII_ART_M)
	@echo "$(RED)** Manda Cub is waiting ! **$(RESET)"

$(BONUS)	:	$(LIBFT) $(OBJS_B)
	@echo "$(RED)** Linking. **$(YELLOW)"
	$(CC) $(CFLAGS) $(OBJS_B) $(LIBFT) $(MCFLAGS) -o $(BONUS)
	@printf "$(UCYAN)"
	@printf $(ASCII_ART_B)
	@echo "$(RED)** Bonus Cub is waiting ! **$(RESET)"

clean:
	@echo "$(RED)** Cleaning Object Files. **$(YELLOW)"
	@make -C libs/libft clean
	@$(RM) $(OBJS) $(OBJS_B)

fclean:	clean
	@echo "$(RED)** Cleaning. **$(YELLOW)"
	@make -C libs/libft fclean
	@$(RM) $(NAME) $(BONUS)

re:	fclean all

.PHONY: all bonus clean fclean re
