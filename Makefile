# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 17:33:00 by snicolet          #+#    #+#              #
#    Updated: 2018/02/27 23:16:53 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS=-Wall -Werror -Wextra -Weverything -Wno-reserved-id-macro
INC=-I./libft/include -I./include
LINKER=-L./libft -lft
NAME=ft_nm
OBJS=nm.o nm_x32.o nm_x64.o loadfile.o nm_display.o nm_fat.o swap.o nm_lib.o
SRCS=$(OBJS:%.o=srcs/%.c)
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

norminette:
	make -C libft norminette
	norminette $(SRCS) nm.h

otool: otool.o loadfile.o
	$(CC) $(CFLAGS) $(LINKER) otool.o loadfile.o -o ft_otool

.PHONY: re all clean fclean
