/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 20:32:51 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 14:18:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

unsigned int	swap(unsigned int x)
{
	return ((x & 0xff000000) >> 24 |
		(x & 0x00ff0000) >> 8 |
		(x & 0x0000ff00) << 8 |
		(x & 0x000000ff) << 24);
}

size_t			swap64(const size_t x)
{
	return (
		(x & 0xff00000000000000) >> 56 |
		(x & 0x00ff000000000000) >> 40 |
		(x & 0x0000ff0000000000) >> 24 |
		(x & 0x000000ff00000000) >> 8 |
		(x & 0x00000000ff000000) << 8 |
		(x & 0x0000000000ff0000) << 24 |
		(x & 0x000000000000ff00) << 40 |
		(x & 0x00000000000000ff) << 56);
}

size_t			smartswap64(const size_t x, const size_t flags)
{
	if (flags & FLAG_CIGAM)
		return (swap64(x));
	return (x);
}

unsigned int	smartswap32(const unsigned int x, const size_t flags)
{
	if (flags & FLAG_CIGAM)
		return (swap(x));
	return (x);
}
