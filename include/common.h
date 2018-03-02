/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 22:42:51 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 23:34:58 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# include "libft.h"

typedef struct	s_common
{
	size_t			flags;
	size_t			filesize;
	const char		*filepath;
	unsigned char	*fileraw;
	t_list			*segments;
	unsigned char	*rootraw;
	size_t			rfs;
	void			*padding;
}				t_common;

# define SEGSIZE64	sizeof(struct segment_command_64)
# define SEGSIZE32	sizeof(struct segment_command)

#endif
