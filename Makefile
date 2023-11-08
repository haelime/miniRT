# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:22:09 by haeem             #+#    #+#              #
#    Updated: 2023/11/08 19:56:46 by hyunjunk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -g3 #werror
SRCDIR = $(CURDIR)

NAME = miniRT

LIBFTDIR = $(SRCDIR)/libft
LIBFT = ./libft/libft.a
LIBFTHEADER = ./libft/libft.h

MLX_NAME = mlx
MLX_DIR = ./mlx

SOURCES = $(addprefix $(CURDIR)/srcs/,\
main.c\
Control/Scene.c\
Graphics/Vector.c\
Graphics/Sphere.c\
Graphics/Triangle.c\
main.c\
Parse/Parse.c\
Parse/Parse_common.c\
Parse/Parse_object.c\
Parse/Parse_object2.c\
Parse/Parse_util.c\
)

# BONUSES = $(addprefix $(CURDIR)/srcs_bonus/,\

# )

OBJECTS = $(SOURCES:.c=.o)
# BONUSOBJECTS = $(BONUSES:.c=.o)
ALLOBJECTS = $(SOURCES:.c=.o) $(BONUSES:.c=.o)

HEADER = -I./includes\
-I./srcs/Control\
-I./srcs/Graphics\
-I./srcs/Parse\
-I./libft/includes\
-I./libft/get_next_line\

# BONUSHEADER = $(CURDIR)/include_bonus

# ifdef WITH_BONUS
# 	OBJ = $(BONUSOBJECTS)
# 	HDR = $(BONUSHEADER)
# else
	OBJ = $(OBJECTS)
	HDR = $(HEADER)
# endif

all: $(NAME)

# bonus:
# 	@make WITH_BONUS=1 all

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR) -I $(MLX_DIR) -I $(LIBFTDIR)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) all
	@$(MAKE) -C $(MLX_DIR) all
	@$(CC) $(CFLAGS) -L$(LIBFTDIR) $(LIBFT) -L$(MLX_DIR) -l$(MLX_NAME) -framework OpenGL -framework AppKit $^ -o $@
	@cp $(MLX_DIR)/libmlx.dylib $(SRCDIR)

clean:
	@rm -f $(ALLOBJECTS)
	@make -C $(LIBFTDIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean
	@make -C $(MLX_DIR) clean
	@rm -f libmlx.dylib

re: fclean all

.PHONY: re clean fclean all bonus miniRT