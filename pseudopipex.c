/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudopipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:05:07 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/05 09:21:36 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	pipex_exec(t_exec *exec, t_parser *ps)
{
	int	ignore[2];
	int status;

	status = fs_check(exec->infile, &ignore[0]);
	if (status != 0)
		return (status);
	status = fs_check(exec->outfile, &ignore[1]);
	if (status != 0)
		return (status);
	status = cmd_findpath(exec->cmdarr, ps);
	if (status != 0)
		return (status);
	pipex_close(ps, ignore);
	dup2(exec->fd[0], STDIN_FILENO);
	file_close(&exec->fd[0]);
	dup2(exec->fd[1], STDOUT_FILENO);
	file_close(&exec->fd[1]);
	execve(exec->cmdarr[0], exec->cmdarr, ps->envp);
}

int	cmd_findpath(char **cmd, t_parser *ps);

void	pipex_close(t_parser *ps, int ignore[2])
{
	t_list	*exec;
	t_exec	*ex;

	exec = ps->exec;
	while (exec)
	{
		ex = (t_exec *) exec->content;
		fs_close(ex->infile, ignore);
		fs_close(ex->outfile, ignore);
		file_close(&ex->fd[0]);
		exec = exec->next;
	}
}

int			pipex_error(t_parser *ps, char *msg, t_error err, int errnum);
