/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 16:13:21 by snicolet          #+#    #+#             */
/*   Updated: 2017/11/11 16:26:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "nm.h"

static size_t	filesize(const char *filepath)
{
	struct stat		st;

	if (stat(filepath, &st) != 0)
		return (0);
	return ((size_t)st.st_size);
}

char			*loadfile(const char *filepath, size_t *usize)
{
	const size_t	size = filesize(filepath);
	int				fd;
	char			*data;

	fd = 0;
	data = NULL;
	if ((!size) || (!(fd = open(filepath, O_RDONLY))) ||
		(!(data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, -1))))
	{
		if (*usize)
			*usize = 0;
		if (fd)
			close(fd);
		return (NULL);
	}
	close(fd);
	*usize = size;
	return (data);
}
