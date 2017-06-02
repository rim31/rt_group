# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 18:24:41 by lnieto-m          #+#    #+#              #
#    Updated: 2016/06/03 12:48:04 by svelhinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

SRC_PATH = srcs

OBJ_PATH = obj

CFLAGS = -g -Wall -Wextra -Werror

CPFLAGS = -I./usr/local/include -I./libft/includes -I ./includes

LFLAGS = -lmlx -framework OpenGl -framework AppKit -lm -L/usr/local/lib/

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`

GTK_LDFLAGS = `pkg-config --libs gtk+-3.0`

NAME = rt

SRC_NAME =	main.c events.c functions.c raytracer.c objects.c init_all.c init_camera_light.c \
			init_objects.c parser.c parsing_camera_light.c parsing_objects.c vectors.c light.c \
			rotations.c render.c limited_objects.c create_window.c reflec_refrac.c \
			perlin.c gtk.c color_filter.c signals.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFT_PATH = libft/libft.a

SHELL = ZSH

all: $(NAME)
	@echo "\033[0m"

$(NAME): rtv $(OBJ)
	@echo -n "\n\033[33mLIBFT : \033[0m"
	@make -C libft/
	@$(CC) $(LIBFT_PATH) $(LFLAGS) $(OBJ) $(GTK_LDFLAGS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo -n "\033[32m="
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPFLAGS) $(GTK_CFLAGS) -o $@ -c $<

rtv:
	@echo -n "\033[32mRT : "

clean:
	@echo "\033[32mSuppression des objets du rt\033[0m"
	@make -C libft/ clean
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "\033[32mSuppression de l'executable du rt\033[0m"
	@make -C libft/ fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all rtv
