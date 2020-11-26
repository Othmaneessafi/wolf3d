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
		Get_Next_Line/get_next_line.c projection3d.c raycasting2.c

FRAM =  -framework SDL2 -F ./SDL/ -framework SDL2_mixer -F ./SDL  -framework SDL2_image -F ./SDL -rpath @loader_path/SDL -lz

OBJ = $(SRC:.c=.o) 

F_OBJ = ./OBJ

all: $(NAME)
%.o : %.c $(INC)
	$(CC) $(CFLAGS)$(OBJ) $(LIB) $(FRAM) -o $(NAME) -c -o $@ $<
$(NAME):$(OBJ)
		@echo "\033[2;36m"
		@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(FRAM) -o $(NAME)
		@echo "wolf3d_3D: executable file is ready"
		@echo "\033[0m"
clean:
		@echo "\033[2;32m"
		@rm -rf $(OBJ)   2> /dev/null || true
		@echo "wolf3d_3D: all resources deleted"
		@echo "\033[0m"
fclean: clean 
		@echo "\033[2;34m"
		@rm -f $(NAME)  2> /dev/null || true
		@echo "wolf3d_3D: executable file deleted"
		@echo "\033[0m"
		
re: fclean all
