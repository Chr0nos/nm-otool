/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:43:01 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 17:29:27 by snicolet         ###   ########.fr       */
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
# include "loadfile.h"
# include "swap.h"
# include "common.h"
# include "flags.h"
# include "security.h"
# include "lib.h"
# define NM_ERROR 	1
# define NM_SUCCESS	0
# define NM_LIBRARY 0x72613c21

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
	size_t					filesize;
	const char				*filepath;
	char					*fileraw;
	t_list					*segments;
	char					*rootraw;
	size_t					rfs;
	char					*subfilename;
	unsigned int			magic;
	unsigned int			display_size;
	t_segindex				indexes;
	char					*padding;
}							t_nm;

t_sym						**symbols_sort(t_list *symbols);
void						nm_display_foreach(void *userdata, size_t size,
	void *content);
int							handle_files_types(t_nm *nm);
void						nm_display(t_list *lst, t_nm *nm);
t_list						*nm_display_list(t_list *lst, t_nm *nm);
void						nm_display_sym(const t_sym *sym, t_nm *nm);
char						nm_getletter(const t_sym *sym, const t_nm *nm);

void						nm_wrapper(size_t ptr, t_list *segments,
	t_common *com);
void						print_symb_32(struct symtab_command *sym,
	size_t const ptr, t_common *com);
void						print_symb_64(struct symtab_command *sym,
	size_t const ptr, t_common *com);
int							sort_by_names(t_sym *a, t_sym *b);
int							sort_by_addr(t_sym *a, t_sym *b);
void						nm_fat_run(struct fat_arch *arch, t_common *com);
void						lib_rl_run(t_common *com, size_t index,
	const size_t size, t_ar **tab);
#endif
