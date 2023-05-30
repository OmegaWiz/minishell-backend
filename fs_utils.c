/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:36:36 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/30 08:37:59 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

t_fileset	*fs_init(char *name, int fd, t_filetype type)
{
	t_fileset	*fs;

	fs = malloc(sizeof(t_fileset));
	if (!fs)
		return (NULL);
	fs->name = name;
	fs->fd = fd;
	fs->type = type;
	return (fs);
}

void	fs_free(t_fileset *fs)
{
	if (!fs)
		return ;
	if (fs->fd > 2)
		file_close(&fs->fd);
	if (fs->name)
		free(fs->name);
	free(fs);
}

void	file_close(int *fd)
{
	if (*fd > 2)
		close(*fd);
	*fd = INT_MIN;
}
