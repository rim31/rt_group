MAIN	:= env_setup.c expose.c key.c set_pixel.c new_color.c \
			draw.c \

OBJ	:= $(OBJ) $(MAIN:.c=.o)

$(DIROBJ)/%.o: $(DIRMLX)/%.c $(HEAD)
	$(COMPIL)
