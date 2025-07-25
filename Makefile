# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achemlal <achemlal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 12:33:08 by yel-haya          #+#    #+#              #
#    Updated: 2025/07/19 10:51:15 by achemlal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = cub3D
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -Ofast

# -------------------- MLX mac Flags --------------------
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit 
# MLXFLAGS = -L./minilibx-linux -lmlx -lXext -lX11 -lm -lGL

# -------------------- Source Files --------------------
SRC_DIR  = ./
UTILS    = utils/otherFunctions
GNL      = $(UTILS)/get_next_line
PARSING  = parsing
RAYCAST  = reycasting

SRCS = \
	$(SRC_DIR)/cub3d.c\
	$(UTILS)/ft_memset.c \
	$(UTILS)/ft_strncmp.c \
	$(UTILS)/ft_strrchr.c \
	$(UTILS)/ft_strtrim.c \
	$(UTILS)/ft_strlcpy.c \
	$(UTILS)/ft_split.c \
	$(UTILS)/ft_atoi.c \
	$(UTILS)/ft_isdigit.c \
	$(UTILS)/ft_itoa.c \
	$(UTILS)/ft_strcmp.c \
	$(GNL)/get_next_line.c \
	$(GNL)/get_next_line_utils.c \
	$(PARSING)/parsing.c \
	$(PARSING)/parse_map.c \
	$(PARSING)/parse_map2.c \
	$(PARSING)/parse_map_helper1.c \
	$(PARSING)/parse_map_helper2.c \
	$(PARSING)/free_functions.c \
	$(PARSING)/free_functions2.c \
	$(PARSING)/split_map.c \
	$(PARSING)/flood_fill.c \
	$(PARSING)/parse_texture.c \
	$(PARSING)/parse_texture2.c \
	$(PARSING)/parse_color.c \
	$(RAYCAST)/player_movments.c \
	$(RAYCAST)/player_movments2.c \
	$(RAYCAST)/putting_content.c \
	$(RAYCAST)/reycasting.c \
	$(RAYCAST)/door_functions.c\
	$(RAYCAST)/door_functions2.c\
	$(RAYCAST)/mlx_tools.c\
	$(RAYCAST)/rendring.c\
	$(RAYCAST)/anim.c\
	$(RAYCAST)/mouse.c\
	$(RAYCAST)/init_anim.c\
	$(RAYCAST)/init_surprise.c\
	$(RAYCAST)/surprise.c
	
# -------------------- Object Files --------------------
OBJ  = $(SRCS:.c=.o)

# -------------------- Rules --------------------
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

%.o: %.c headers/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
