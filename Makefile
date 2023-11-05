# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:22:09 by haeem             #+#    #+#              #
#    Updated: 2023/11/05 20:40:38 by haeem            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = $(CURDIR)

NAME = miniRT

LIBFTDIR = $(SRCDIR)/libft
LIBFT = ./libft/libft.a
LIBFTHEADER = ./libft/libft.h

MLX_NAME = mlx
MLX_DIR = ./mlx

SOURCES = $(addprefix $(CURDIR)/srcs/,\
main.c\
)

# BONUSES = $(addprefix $(CURDIR)/srcs_bonus/,\

# )

OBJECTS = $(SOURCES:.c=.o)
# BONUSOBJECTS = $(BONUSES:.c=.o)
ALLOBJECTS = $(SOURCES:.c=.o) $(BONUSES:.c=.o)

HEADER = $(CURDIR)/includes
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
	@$(CC) $(CFLAG) -c $< -o $@ -I $(HDR) -I $(MLX_DIR) -I $(LIBFTDIR)

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