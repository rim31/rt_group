# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oseng <oseng@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 18:24:41 by lnieto-m          #+#    #+#              #
#    Updated: 2016/06/03 08:18:28 by oseng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

SRC_PATH = srcs

OBJ_PATH = obj

CFLAGS = -g

CPFLAGS = -I./usr/local/include -I./libft/includes -I ./includes

LFLAGS = -lmlx -framework OpenGl -framework AppKit -lm -L/usr/local/lib/

NAME = rt

SRC_NAME =	main.c events.c functions.c raytracer.c objects.c init_all.c init_camera_light.c \
			init_objects.c parser.c parsing_camera_light.c parsing_objects.c vectors.c light.c \
			rotations.c render.c limited_objects.c create_window.c reflec_refrac.c \
			menu.c perlin.c exotic.c

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
	@$(CC) $(LIBFT_PATH) $(LFLAGS) $(OBJ) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo -n "\033[32m="
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPFLAGS) -o $@ -c $<

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
