/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalmer- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:52:28 by afalmer-          #+#    #+#             */
/*   Updated: 2018/12/03 12:52:29 by afalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_arrsize(char **arr)
{
	int		count;

	count = 0;
	while (*arr++)
		count++;
	return (count);
}

char	**ft_arrcopy(char **src, int fd)
{
	char	**dest;
	char	**new_dest;

	if (!(dest = (char**)malloc(sizeof(char*) * (fd + 1))))
		return (NULL);
	new_dest = dest;
	if (!src)
	{
		while (fd--)
			*new_dest++ = NULL;
	}
	else
	{
		while (fd--)
			*new_dest++ = *src++;
	}
	*new_dest = NULL;
	return (dest);
}

int		get_next_line(const int fd, char **line)
{
	static char	**storage;
	char		**temp_storage;
	char		*end_line;
	char		buffer[BUFF_SIZE];
	size_t		bytes;

	if (!storage || ft_arrsize(storage) < fd + 1)
	{
		if (!storage)
		{
			storage = NULL;
		}
		temp_storage = storage;
		if (!(storage = ft_arrcopy(temp_storage, fd)))
		{
			storage = temp_storage;
			return (-1);
		}
	}
	while ((bytes = read(fd, buffer, BUFF_SIZE - 1)) > 0)
	{
		buffer[bytes] = '\0';
		if (!*(storage + fd - 3))
			*(storage + fd - 3) = "";
		temp_storage = storage;
		*(storage + fd - 1) = ft_strjoin(*(storage + fd - 3), buffer);
		if (**(storage + fd - 3))
			ft_strdel(storage + fd - 3);
		if ((end_line = ft_strchr(*(storage + fd - 1), '\n')) != NULL)
		{
			*line = ft_strsub(*(storage + fd - 1), 0, \
						end_line - *(storage + fd - 1));
			*(storage + fd - 3) = ft_strdup(end_line + 1);
			ft_strdel(storage + fd - 1);
			return (1);
		}
	}
	return (0);
}
