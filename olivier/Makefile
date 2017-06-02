
GC = gcc

FLAG = -I $(INCL) ./minilibx_macos/libmlx.a -framework OpenGl -framework AppKit

SRCS = main.c\
	ft_object.c ft_expose.c ft_start_screen.c	my_key_funct.c ft_plan.c \
	mlx_pixel_put_to_image.c ft_sphere.c ft_cylind.c ft_cone.c ft_calcul.c\
	ft_shadow.c ft_scene_1.c ft_scene_2.c ft_scene_3.c ft_scene_4.c\
	ft_scene_5.c ft_scene_6.c ft_scene_6bis.c ft_scene_7.c\


LIBFT_PATH = ./libft/

LIBFT_NAME = libft.a

LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

INCL = rtv1.h

NAME = rtv1

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	@echo "by 😉seng     RTV1 "

		@echo "\033[92mCompiling"
		@make re -C $(LIBFT_PATH)
		@$(GC) -o $(NAME) -Wall -Wextra -Werror $(SRCS) $(FLAG) $(LIBFT)
		@echo "\033[96m->Done"
		@make fclean -C $(LIBFT_PATH)

clean:
		@echo "\033[92mDeleting"
		@rm -f $(OBJ)
		@make fclean -C $(LIBFT_PATH)
		@echo "\033[96mClean done"


fclean: clean
		@echo "\033[92mDeleting"
		@rm -f $(NAME)
		@make fclean -C $(LIBFT_PATH)
		@echo "\033[96mFclean Done"

re: fclean all

.PHONY: all clean fclean re
