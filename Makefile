# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 17:33:00 by snicolet          #+#    #+#              #
#    Updated: 2018/03/02 21:34:08 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS=-Wall -Werror -Wextra -Weverything -Wno-reserved-id-macro
INC=-I./libft/include -I./include
LINKER=-L./libft -lft
NAME=ft_nm
CC=clang

BUILDDIR=./build/

OTOOL=ft_otool
OTOOL_SRCS=otool.c loadfile.c otool_filetype.c otool_macho.c otool_security.c \
	swap.c otool_showmem.c
OTOOL_SRCS_FULL=$(OTOOL_SRCS:%.c=srcs/%.c)
OTOOL_OBJS=$(OTOOL_SRCS:%.c=$(BUILDDIR)%.o)


NM=ft_nm
NM_SRCS=nm.c nm_x32.c nm_x64.c loadfile.c nm_display.c nm_fat.c swap.c nm_lib.c
NM_SRCS_FULL=$(NM_SRCS:%.c=srcs/%.c)
NM_OBJS=$(NM_SRCS:%.c=$(BUILDDIR)%.o)


all: $(NM) $(OTOOL)

$(BUILDDIR)%.o: srcs/%.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

./libft/libft.a:
	make -C libft

$(NM): ./libft/libft.a $(BUILDDIR) $(NM_OBJS)
	$(CC) $(INC) $(CFLAGS) $(NM_OBJS) $(LINKER) -o $(NM)

clean:
	$(RM) -rf $(BUILDDIR)

fclean: clean
	$(RM) $(NM)

re: fclean all

norminette-all: norminette
	make -C libft norminette

norminette:
	norminette $(NM_SRCS_FULL) $(OTOOL_SRCS_FULL) include/*.h

$(OTOOL): ./libft/libft.a $(BUILDDIR) $(OTOOL_OBJS)
	$(CC) $(CFLAGS) $(LINKER) $(OTOOL_OBJS) -o $(OTOOL)

$(BUILDDIR):
	mkdir $(BUILDDIR)

.PHONY: re all clean fclean
