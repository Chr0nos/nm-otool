/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 20:14:15 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 14:18:29 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_H
# define SWAP_H
# include <string.h>

unsigned int	swap(unsigned int x);
size_t			swap64(const size_t x);
size_t			smartswap64(const size_t x, const size_t flags);
unsigned int	smartswap32(const unsigned int x, const size_t flags);

#endif
