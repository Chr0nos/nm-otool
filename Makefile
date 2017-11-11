# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 17:33:00 by snicolet          #+#    #+#              #
#    Updated: 2017/11/11 16:28:12 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS=-Wall -Werror -Wextra -Weverything
INC=-I./libft -I.
LINKER=-L./libft -lft
NAME=nm
OBJS=nm.o nm_x32.o nm_x64.o loadfile.o nm_display.o
CC=clang

all: $(NAME)

%.o: srcs/%.c
	$(CC) $(INC) $(CFLAGS) -c $<

./libft/libft.a:
	make -C libft

$(NAME): ./libft/libft.a $(OBJS)
	$(CC) $(INC) $(CFLAGS) $(OBJS) $(LINKER) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
