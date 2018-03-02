/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 22:48:27 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 23:11:50 by snicolet         ###   ########.fr       */
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
# define MASK_TYPE		0x5

#endif
