/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:17:40 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/07 15:04:31 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
# include "common.h"
# include <string.h>
# include <mach-o/ranlib.h>

typedef struct				s_artab
{
	size_t					offset;
	char					*filename;
	struct ar_hdr			*ar;
	size_t					date;
	size_t					size;
	unsigned int			uid;
	unsigned int			gid;
	unsigned int			mode;
	unsigned int			len;
}							t_ar;

void						handle_lib(t_common *com,
	void (*callback)(t_common *, size_t, const size_t, t_ar **));
void						lib_empty(t_common *com, struct ar_hdr *ar);
int							load_ar(struct ar_hdr *ar, t_ar *load);

#endif
