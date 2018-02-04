/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:43:01 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/04 14:25:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H
# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach/machine.h>
# include "libft.h"
# define SYM_TEXT 'T'
# define SYM_DATA 'D'
# define SYM_BSS 'B'

typedef struct				s_sym
{
	size_t					type;
	size_t					value;
	unsigned int			nsect;
	unsigned int			ndesc;
	char					*name;
	unsigned int			display_size;
	unsigned int			padding;
}							t_sym;
typedef struct				s_nm
{
	unsigned int			magic;
	unsigned int			display_size;
	char					*fileraw;
	const char				*filepath;
}							t_nm;

typedef struct				s_handlers
{
	unsigned int			magic;
	unsigned int			display_size;
	void					(*run)(t_nm *);
}							t_handlers;

void						handle_x32(t_nm *nm);
void						handle_x64(t_nm *nm);
void						handle_fat(t_nm *nm);
t_list						*nm_display_list(t_list *lst, t_list *segments);
void						nm_display_sym(const t_sym *sym, t_list *segments);
int							handle_sort(t_list *a, t_list *b);
char						nm_getletter(const t_sym *sym, t_list *segments);
char						*loadfile(const char *filepath, size_t *usize);

#endif
