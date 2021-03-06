# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 17:33:00 by snicolet          #+#    #+#              #
#    Updated: 2018/03/07 15:06:41 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS=-Wall -Werror -Wextra -Weverything -Wno-reserved-id-macro
INC=-I./libft/include -I./include
LINKER=-L./libft -lft
NAME=ft_nm
CC=clang

BUILDDIR=./build/

OTOOL=ft_otool
OTOOL_SRCS=otool.c loadfile.c otool_macho.c security.c \
	swap.c otool_showmem.c macho.c filetype.c arch_lookup.c fat.c otool_fat.c \
	lib.c otool_lib.c lib_empty.c otool_sname.c
OTOOL_SRCS_FULL=$(OTOOL_SRCS:%.c=srcs/%.c)
OTOOL_OBJS=$(OTOOL_SRCS:%.c=$(BUILDDIR)%.o)


NM=ft_nm
NM_SRCS=nm.c nm_x32.c nm_x64.c loadfile.c nm_display.c nm_fat.c swap.c \
	nm_lib.c security.c macho.c nm_wrapper.c nm_sorts.c filetype.c \
	arch_lookup.c fat.c lib.c lib_empty.c
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
