/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 22:42:51 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 22:43:21 by snicolet         ###   ########.fr       */
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
	void			*padding;
}				t_common;

#endif
