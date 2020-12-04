NAME = wolf

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SDLF = -I SDL/SDL2.framework/Headers   

INC = wolft3d.h

SRC = main.c process_input.c rendering.c updating.c tools.c\
		raycasting.c checker.c Get_Next_Line/libft/ft_split_whitespaces.c \
		Get_Next_Line/libft/ft_strdup.c \
		Get_Next_Line/libft/ft_strchr.c \
		Get_Next_Line/libft/ft_strdel.c \
		Get_Next_Line/libft/ft_strjoin.c \
		Get_Next_Line/libft/ft_strnew.c \
		Get_Next_Line/libft/ft_strlen.c \
		Get_Next_Line/libft/ft_atoi.c \
		Get_Next_Line/get_next_line.c projection3d.c raycasting2.c \
		tools1.c tools2.c

OBJ = $(SRC:.c=.o)

INC = -I SDL/SDL2.framework/Headers -I SDL/SDL2_mixer.framework/Headers -I SDL/SDL2_image.framework/Headers

LIB = -rpath @loader_path/SDL -lz

FRM = -framework SDL2 -F ./SDL/ -framework SDL2_mixer -framework SDL2_image -F ./SDL -framework OpenGl -framework Appkit

CFLAGS = -Wall -Werror -Wextra $(INC)

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[2;36m"
	@$(CC) $(CFLAGS) $(LIB) $(FRM) $(OBJ) -o $(NAME)
	@echo "wolf3d_3D: executable file is ready"
	@echo "\033[0m"
clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
