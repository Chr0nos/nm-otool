/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 22:42:51 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 17:30:02 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# include "libft.h"

/*
** -------------------------------------------------------------------------- **
** flags    : binaries flags defined into flags.h
** filesize : the current file size, it can be a sub size (ex: fat binaries)
** filepath : the full path of the file
** fileraw  : the current root of the file, can be a sub content (fat bin)
** segments : segments list, can be segments in 32 or 64 bits
** rootraw  : the real root raw data, never changes, used in security with rfs
** rfs      : meaning for "Real File Size", the full size of rootraw
** -------------------------------------------------------------------------- **
** note: this structure has been designed to be accesible from a (t_otool)
** and a (t_nm*) with a cast like (t_common*)nm or (t_common*)otool
*/

typedef struct		s_common
{
	size_t			flags;
	size_t			filesize;
	const char		*filepath;
	unsigned char	*fileraw;
	t_list			*segments;
	unsigned char	*rootraw;
	size_t			rfs;
	char 			*subfilename;
}					t_common;

# define SEGSIZE64	sizeof(struct segment_command_64)
# define SEGSIZE32	sizeof(struct segment_command)

#endif
