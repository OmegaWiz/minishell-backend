/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:27:46 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/07 11:25:06 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

t_exec	*exec_init(void)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->pid = INT_MIN;
	exec->cmdlst = NULL;
	exec->cmdarr = NULL;
	exec->infile = NULL;
	exec->outfile = NULL;
	exec->pipefd[0] = INT_MIN;
	exec->pipefd[1] = INT_MIN;
	if (pipe(exec->pipefd) == -1)
		return (exec_free(exec));
	return (exec);
}

t_exec	*exec_free(t_exec *exec)
{
	if (!exec)
		return (NULL);
	if (exec->pipefd[0] > 2)
		file_close(&exec->pipefd[0]);
	if (exec->pipefd[1] > 2)
		file_close(&exec->pipefd[1]);
	ft_arrclear(exec->cmdarr);
	ft_lstclear(&exec->cmdlst, free);
	ft_lstclear(&exec->infile, fs_free);
	ft_lstclear(&exec->outfile, fs_free);
	free(exec);
	return (NULL);
}
