MAIN	:= raytracer.c cone.c cylindre.c plan.c sphere.c \
		rotation.c resolve.c intersection.c shadow.c raytracing_obj.c \
		brightness.c \

OBJ	:= $(OBJ) $(MAIN:.c=.o)

$(DIROBJ)/%.o: $(DIRRT)/%.c $(HEAD)
	$(COMPIL)
