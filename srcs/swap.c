/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 20:32:51 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/13 21:30:44 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint32_t	swap(uint32_t x)
{
	return ((x & 0xff000000) >> 24 |
		(x & 0x00ff0000) >> 8 |
		(x & 0x0000ff00) << 8 |
		(x & 0x000000ff) << 24);
}

size_t		swap64(const size_t x)
{
	return (
		(x & 0xff00000000000000) >> 56 |
		(x & 0x00ff000000000000) >> 40 |
		(x & 0x0000ff0000000000) >> 24 |
		(x & 0x000000ff00000000) >> 8 |
		(x & 0x00000000ff000000) << 8 |
		(x & 0x0000000000ff0000) << 24 |
		(x & 0x000000000000ff00) << 40 |
		(x & 0x00000000000000ff) << 56
	);
}