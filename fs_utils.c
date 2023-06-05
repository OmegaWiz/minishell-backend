/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:36:36 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/05 12:43:47 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

t_fileset	*fs_init(char *name, int fd, t_filetype type)
{
	t_fileset	*fs;

	fs = malloc(sizeof(t_fileset));
	if (!fs)
		return (NULL);
	fs->fd = fd;
	fs->type = type;
	fs->name = ft_strdup(name);
	if (fs->name == NULL && fs->name != NULL)
	{
		fs_free(fs);
		return (NULL);
	}
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

int			fs_check(t_list *fslst, int *fd)
{
	t_fileset	*fs;
	t_list		*ptr;
	int			status;

	status = 0;
	ptr = fslst;
	while (ptr)
	{
		fs = ptr->content;
		if (fs->type == INFILE || fs->type == OUTFILE || fs->type == HEREDOC)
			status = file_open(fs);
		else if (fs->type == HEREDOC)
			status = heredoc_open(fs);
		if (status != 0)
			break ; //error
		fslst = ptr->next;
	}
	return (status);
}
