# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 16:20:15 by alassiqu          #+#    #+#              #
#    Updated: 2024/10/09 16:29:12 by alassiqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cub3D
BONUS		:=	cub3D_bonus

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -fsanitize=address -g3

LXFLAGS		:=	-I /usr/local/include -L /usr/local/lib -lmlx -lXext -lX11 -lm
MCFLAGS		:=	-L libs/mlx -lmlx -framework OpenGL -framework AppKit

RM			:=	rm -f

# Colors
GREEN		:=	\033[1;32m
RED			:=	\033[1;31m
RESET		:=	\033[0m
YELLOW		:=	\033[1;33m
UCYAN		:=	\033[0;34m

# Will be same for both mandatory and bonus.
LIBS		:=	libs/get-next-line/get_next_line.c			\
				libs/get-next-line/get_next_line_utils.c	\
				libs/memory/free_mem.c						\
				libs/memory/memory.c

MAIN_UTILS	:=	main-utils/cub_loop.c						\
				main-utils/math.c							\
				main-utils/ray_distance.c

# This is bonus parsing.
PARSING		:=	parsing/colors.c							\
				parsing/files.c								\
				parsing/map_utils.c							\
				parsing/map.c								\
				parsing/parsing.c							\
				parsing/player.c							\
				parsing/textures.c							\
				parsing/utils.c

# This is for bonus (for now).
RENDERING	:=	rendering/dda_algo.c						\
				rendering/rays_utils.c						\
				rendering/render_map.c						\
				rendering/render_utils.c


SRCS		:=	$(LIBS)										\
				$(PARSING)									\
				$(RENDERING)								\
				$(MAIN_UTILS)								\
				cub3d_bonus.c

LIBFT		:=	libs/libft/libft.a

OBJS		:=	$(SRCS:.c=.o)

all:		$(NAME)
# bonus:		$(BONUS)

ASCII_ART	:=	"\
\n\
\n\
 ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ \n\
██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n\
██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n\
██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n\
╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n\
 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ \n\
\n\
"

$(LIBFT):
	@echo "$(RED)** Building Libft. **$(YELLOW)"
	@make -C libs/libft
	@echo "$(RED)** Libft builded succesfully. **$(RESET)"

$(NAME)	:	$(LIBFT) $(OBJS)
	@echo "$(RED)** Linking. **$(YELLOW)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LXFLAGS) -o $(NAME)
	@printf "$(UCYAN)"
	@printf $(ASCII_ART)
	@echo "$(RED)** Cub3D is waiting ! **$(RESET)"

clean:
	@echo "$(RED)** Cleaning Object Files. **$(YELLOW)"
	@make -C libs/libft clean
	@$(RM) $(OBJS)

fclean:	clean
	@echo "$(RED)** Cleaning. **$(YELLOW)"
	@make -C libs/libft fclean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	clean fclean all re $(LIBFT)