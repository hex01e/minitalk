# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houmanso <houmanso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 19:08:04 by houmanso          #+#    #+#              #
#    Updated: 2023/01/20 10:47:21 by houmanso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra 
LIBFT  = ./libft/libft.a 
NAME   = minitalk
SRC    = client.c server.c
OBJ    = ${SRC:.c=.o}
BSRC    = client_bonus.c server_bonus.c
BOBJ    = ${SRC:.c=.o}

all: ${NAME}

${NAME} : libft client server

client: client.c
	cc ${CFLAGS} ${LIBFT} $< -o $@

server: server.c
	cc ${CFLAGS} ${LIBFT} $< -o $@

client_bonus: client_bonus.c
	cc ${CFLAGS} ${LIBFT} $< -o $@

server_bonus: server_bonus.c
	cc ${CFLAGS} ${LIBFT} $< -o $@

libft : 
	make -C ./libft

bonus : libft client_bonus server_bonus

clean :
	rm -f server client server_bonus client_bonus
	make -C ./libft clean

fclean : clean
	make -C ./libft fclean

re : fclean all

.PHONY : all clean fclean re bonus libft