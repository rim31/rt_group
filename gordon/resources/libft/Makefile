# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grass-kw <grass-kw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/26 13:31:43 by grass-kw          #+#    #+#              #
#    Updated: 2016/04/10 06:14:53 by grass-kw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_memset.c ft_bzero.c ft_strlen.c ft_strcpy.c \
		ft_memccpy.c ft_strncpy.c ft_memcpy.c \
		ft_memmove.c ft_memchr.c ft_memcmp.c ft_strdup.c \
		ft_strcat.c ft_strlcat.c ft_strncat.c \
		ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
		ft_strncmp.c ft_strcmp.c ft_atoi.c ft_isdigit.c \
		ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_putchar.c ft_putstr.c \
		ft_strnew.c ft_strdel.c ft_strclr.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl.c ft_putendl_fd.c \
		ft_putnbr.c ft_putnbr_fd.c 	ft_strjoin.c \
		ft_memalloc.c ft_memdel.c \
		ft_striteri.c ft_striter.c ft_strmap.c ft_strmapi.c ft_strequ.c \
		ft_strnequ.c ft_strsub.c ft_strsplit.c \
		ft_free_tab.c ft_itoa.c ft_strtrim.c ft_isblank.c ft_isblank2.c \
		ft_ispace.c ft_islower.c ft_isblank.c ft_isblank2.c ft_isupper.c \
		ft_islower.c ft_isalnum.c \
		ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
		ft_lstmap.c ft_lst_push_back.c ft_strndup.c ft_strnjoin.c ft_putdata.c \
		ft_put_array.c ft_array_len.c get_next_line.c ft_strtrim_spc.c \
		ft_strsplit_spc.c ft_isnumber.c ft_strclean.c ft_atof.c ft_atol.c \
		ft_putdouble.c

OBJ = $(SRCS:.c=.o)

INC = -I./includes/

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o : %.c
	$(CC) $(CFLAG) $(INC) -c $^

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
