/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 22:48:27 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 16:02:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

# define FLAG_OK		0
# define FLAG_NONE		0
# define FLAG_32BITS	(1u << 0)
# define FLAG_64BITS	(1u << 1)
# define FLAG_LIB		(1u << 2)
# define FLAG_FAT		(1u << 3)
# define FLAG_MACHO		(1u << 4)
# define FLAG_CIGAM		(1u << 5)
# define FLAG_UNKNKOW	(1u << 6)
# define FLAG_ERROR		(1u << 7)
# define FLAG_SYMTAB	(1u << 8)
# define FLAG_SNAME		(1u << 9)
# define FLAG_NM		(1u << 10)
# define FLAG_OTOOL		(1u << 11)
# define FLAG_NOSORT	(1u << 12)
# define FLAG_SKIPLINE	(1u << 13)
# define FLAG_BYADDR	(1u << 14)
# define FLAG_RECURSIVE	(1u << 15)
# define MASK_ARCH		(FLAG_32BITS | FLAG_64BITS)
# define MASK_TYPE		(FLAG_LIB | FLAG_FAT | FLAG_MACHO)

#endif
