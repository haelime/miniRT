# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:22:09 by haeem             #+#    #+#              #
#    Updated: 2023/11/20 15:32:20 by hyunjunk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -mavx2 -o3 -fsanitize=address #werror
SRCDIR = $(CURDIR)

NAME = miniRT

LIBFTDIR = $(SRCDIR)/libft
LIBFT = ./libft/libft.a
LIBFTHEADER = ./libft/libft.h

MLX_NAME = mlx
MLX_DIR = ./mlx

SOURCES = $(addprefix $(CURDIR)/srcs/,\
Control/ControlBlock.c\
Control/hooks.c\
Control/Image.c\
Control/Scene.c\
Graphics/Matrix.c\
Graphics/Object.c\
Graphics/Ray.c\
Graphics/Sphere.c\
Graphics/SphereTraceRay.c\
Graphics/Triangle.c\
Graphics/Vector.c\
Graphics/Vector2.c\
Graphics/Vector3.c\
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