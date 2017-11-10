/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:43:01 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/10 14:24:15 by snicolet         ###   ########.fr       */
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
	char					*name;
}							t_sym;

void						handle_x32(char *fileraw);
void						handle_x64(char *fileraw);
t_list						*nm_display_list(t_list *lst);
int							handle_sort(t_list *a, t_list *b);

#endif
