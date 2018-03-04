/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 15:44:17 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 15:45:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FAT_H
# define FAT_H
# include "common.h"
# include <mach-o/fat.h>

void	fat(t_common *com, void (*callback)(struct fat_arch *, t_common *));

#endif
