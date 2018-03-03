/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 02:45:08 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 02:50:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHO_H
# define MACHO_H
# include "swap.h"
# include "flags.h"
# include "common.h"
# include "security.h"
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

void				macho(t_common *com,
	void (*symcall)(size_t, t_list *, t_common *));

#endif
