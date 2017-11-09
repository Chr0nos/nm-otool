#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/11/09 17:33:00 by snicolet          #+#    #+#             *#
#*   Updated: 2017/11/09 17:45:08 by snicolet         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

CFLAGS=-Wall -Werror -Wextra -Weverything
INC=-I./libft
LINKER=-L./libft -lft
NAME=nm
OBJS=nm.o
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

fclean:
	$(RM) $(NAME)

re: clean fclean
