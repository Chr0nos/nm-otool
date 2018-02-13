/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:43:01 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/13 16:32:07 by snicolet         ###   ########.fr       */
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
# define NM_ERROR 	1
# define NM_SUCCESS	0
# define SEGSIZE64	sizeof(struct segment_command_64)
# define SEGSIZE32	sizeof(struct segment_command)

typedef struct				s_sym
{
	size_t					type;
	size_t					value;
	unsigned int			nsect;
	unsigned int			ndesc;
	char					*name;
}							t_sym;

typedef struct				s_segindex
{
	unsigned int			text;
	unsigned int			data;
	unsigned int			bss;
	unsigned int			sector;
}							t_segindex;

/*
** magic        : the magic tag of the file, the start of fileraw
** display_size : for 64 bits binnaries it will be 16, 8 for 32
** filepath     : the source file path
** segments     : chained list to internal segments
** rootraw      : equal to fileraw but will NOT be changed whatever appends
** fileraw      : the content of the file, all of it mmaped into the memory
** filesize     : the total file size in the mapped region, dont read after it
*/

typedef struct				s_nm
{
	size_t					flags;
	unsigned int			magic;
	unsigned int			display_size;
	t_segindex				indexes;
	char					*fileraw;
	char					*rootraw;
	const char				*filepath;
	t_list					*segments;
	size_t					filesize;
}							t_nm;

# define NM_FLAG_NONE	0
# define NM_FLAG_ERROR (1u << 0)
# define NM_FLAG_CIGAM (1u << 1)

typedef struct				s_handlers
{
	unsigned int			magic;
	unsigned int			display_size;
	void					(*run)(t_nm *);
	size_t					flags;
	const char				*name;
}							t_handlers;

void						nm_display_foreach(void *userdata, size_t size,
	void *content);
int							nm_security(t_nm *nm, const void *ptr,
	const size_t size);
void						handle_x32(t_nm *nm);
void						handle_x64(t_nm *nm);
void						handle_fat(t_nm *nm);
t_list						*nm_display_list(t_list *lst, t_nm *nm);
void						nm_display_sym(const t_sym *sym, t_nm *nm);
int							handle_sort(t_list *a, t_list *b);
char						nm_getletter(const t_sym *sym, const t_nm *nm);
char						*loadfile(const char *filepath, size_t *usize);

#endif
