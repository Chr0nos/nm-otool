/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_lookup.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 15:35:55 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/05 14:27:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARCH_LOOKUP_H
# define ARCH_LOOKUP_H
# include <mach-o/fat.h>
# include <string.h>

struct fat_arch	*arch_lookup(struct fat_arch *arch,
	unsigned int arch_left, const size_t flags);

#endif
