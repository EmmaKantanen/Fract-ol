# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/03 16:40:05 by vinograd          #+#    #+#              #
#    Updated: 2022/08/08 12:37:29 by ekantane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
SRC =  src/color.c src/control.c src/follow_mouse.c src/julia.c src/main.c \
src/mandelbrot.c src/tricorn.c
OBJ = *.o
FLAGS = -Wall -Wextra -Werror
FRAMEWORKS = -framework OpenGL -framework AppKit
INCLUDES = libft/libft.a

.PHONY: all clean fclean re

all:	$(NAME)

$(NAME):
	make -C libft all
	gcc $(SRC) -o $(NAME) $(FLAGS) $(INCLUDES) \
	-L /usr/local/lib -lmlx -I /usr/local/include $(FRAMEWORKS)

clean:
	make -C libft clean
	rm -rf $(OBJ)
	
fclean: clean
	make -C libft clean
	rm -rf $(NAME)
	
re: fclean all
