/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_sorts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 14:08:19 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 14:11:45 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		sort_by_names(t_sym *a, t_sym *b)
{
	const int	cmp = ft_strcmp(a->name, b->name);

	return ((cmp == 0) ? (int)(a->value - b->value) : cmp);
}

int		sort_by_addr(t_sym *a, t_sym *b)
{
	if (a->value == b->value)
		return (sort_by_names(a, b));
	if (a->value > b->value)
		return (1);
	return (-1);
}
