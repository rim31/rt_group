# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 18:24:41 by lnieto-m          #+#    #+#              #
#    Updated: 2016/06/12 14:12:46 by svelhinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

SRC_PATH = srcs

OBJ_PATH = obj

CFLAGS = -g -Wall -Wextra -Werror

CPFLAGS = -I./usr/local/include -I./libft/includes -I ./includes

LFLAGS = -lmlx -framework OpenGl -framework AppKit -lm -L/usr/local/lib/

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0` `gsl-config --cflags`

GTK_LDFLAGS = `pkg-config --libs gtk+-3.0` `gsl-config --libs`

NAME = rt

SRC_NAME =	other/main.c raytracer/expose.c other/functions.c raytracer/raytracer.c \
			objects/basic/objects.c init/init_all.c init/init_camera_light.c \
			init/init_objects.c parser/parser.c parser/parsing_camera_light.c \
			parser/parsing_objects.c vectors/vectors.c light/light.c \
			vectors/rotations.c objects/limited/limited_objects.c gtk/create_window.c \
			reflections_refractions/reflec_refrac.c gtk/window.c effects/color_filter.c \
			effects/antialiasing.c parser/parsing_materials.c init/init_materials.c \
			vectors/vectors2.c objects/limited/triangle.c objects/limited/quadrilateral.c \
			objects/automatic/automatics_objects.c raytracer/render.c objects/exotic/exotic.c \
			init/init_name.c textures/procedural.c textures/textures.c gtk/open_file.c \
			effects/cartoon.c gtk/screenshot.c gtk/antialiasing_gtk.c gtk/select_antialiasing.c \
			gtk/draw_area.c gtk/filters.c parser/parser_options.c parser/parsing_objects2.c \
			raytracer/raytracer2.c objects/exotic/normal_quadric.c reflections_refractions/reflections.c \
			reflections_refractions/refractions.c objects/limited/limited_objects2.c \
			objects/limited/limited_equations.c light/shadows.c light/light2.c

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
	@mkdir $(OBJ_PATH)/effects 2> /dev/null || true
	@mkdir $(OBJ_PATH)/gtk 2> /dev/null || true
	@mkdir $(OBJ_PATH)/init 2> /dev/null || true
	@mkdir $(OBJ_PATH)/light 2> /dev/null || true
	@mkdir $(OBJ_PATH)/objects 2> /dev/null || true
	@mkdir $(OBJ_PATH)/objects/automatic 2> /dev/null || true
	@mkdir $(OBJ_PATH)/objects/limited 2> /dev/null || true
	@mkdir $(OBJ_PATH)/objects/exotic 2> /dev/null || true
	@mkdir $(OBJ_PATH)/objects/basic 2> /dev/null || true
	@mkdir $(OBJ_PATH)/other 2> /dev/null || true
	@mkdir $(OBJ_PATH)/parser 2> /dev/null || true
	@mkdir $(OBJ_PATH)/raytracer 2> /dev/null || true
	@mkdir $(OBJ_PATH)/reflections_refractions 2> /dev/null || true
	@mkdir $(OBJ_PATH)/textures 2> /dev/null || true
	@mkdir $(OBJ_PATH)/vectors 2> /dev/null || true
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
