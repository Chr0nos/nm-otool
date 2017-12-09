/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:43:01 by snicolet          #+#    #+#             */
/*   Updated: 2017/12/09 03:33:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H
# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
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
}							t_sym;

typedef struct				s_handlers
{
	unsigned int			magic;
	unsigned int			padding;
	void					(*run)(char *);
}							t_handlers;

void						handle_x32(char *fileraw);
void						handle_x64(char *fileraw);
t_list						*nm_display_list(t_list *lst, t_list *segments);
void						nm_display_sym(const t_sym *sym, t_list *segments);
int							handle_sort(t_list *a, t_list *b);
char						nm_getletter(const t_sym *sym, t_list *segments);
char						*loadfile(const char *filepath, size_t *usize);

#endif
