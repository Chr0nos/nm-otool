/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 16:13:21 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/16 22:18:31 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "nm.h"

static size_t	filesize(const int fd)
{
	struct stat		st;

	if (fstat(fd, &st) < 0)
		return (0);
	return ((size_t)st.st_size);
}

char			*loadfile(const char *filepath, size_t *usize)
{
	size_t			size;
	int				fd;
	char			*data;

	fd = 0;
	data = NULL;
	if ((!(fd = open(filepath, O_RDONLY))) ||
		(!(size = filesize(fd))) ||
		((data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0))
		== MAP_FAILED))
	{
		if (*usize)
			*usize = 0;
		if (fd)
			close(fd);
		return (NULL);
	}
	*usize = size;
	close(fd);
	return (data);
}
