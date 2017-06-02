# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 18:24:41 by lnieto-m          #+#    #+#              #
#    Updated: 2016/04/20 17:37:09 by lnieto-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

SRC_PATH = srcs

OBJ_PATH = obj

CFLAGS = -Wall -Wextra -Werror

CPFLAGS = -I./usr/local/include -I./libft/includes -I ./includes

LFLAGS = -lmlx -framework OpenGl -framework AppKit -lm -L/usr/local/lib/

NAME = rtv1

SRC_NAME = main.c \
		   expose_hook.c \
		   mlx_pixel_put_to_image.c \
		   rays.c \
		   balayage.c \
		   big_balayage.c \
		   sphere.c \
		   plan.c \
		   cylindre.c \
		   cone.c \
		   key_p.c \
		   rotation.c \
		   shadow_equ.c \
		   shadows1.c \
		   scene_init1.c \
		   scene_init2.c \
		   big_scene_init.c \
		   big_scene_init2.c \
		   resolution.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFT_PATH = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(LIBFT_PATH) $(LFLAGS) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPFLAGS) -o $@ -c $<

clean:
	make -C libft/ clean
	rm -rf $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
