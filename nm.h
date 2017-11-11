/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:43:01 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/11 16:28:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H
# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "libft.h"

typedef struct				s_sym
{
	size_t					type;
	size_t					value;
	unsigned int			nsect;
	unsigned int			ndesc;
	char					*name;
}							t_sym;

void						handle_x32(char *fileraw);
void						handle_x64(char *fileraw);
t_list						*nm_display_list(t_list *lst);
void						nm_display_sym(const t_sym *sym);
int							handle_sort(t_list *a, t_list *b);
char						nm_getletter(const t_sym *sym);
char						*loadfile(const char *filepath, size_t *usize);

#endif
