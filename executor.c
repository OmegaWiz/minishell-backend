/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:14:24 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/30 09:58:18 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	executor(t_parser *ps)
{
	executor_pipe(ps);
	executor_fork(ps);
	pipex_close(ps->exec, -1);
	executor_wait(ps);
	return (exec_free(ps));
}

void	executor_pipe(t_parser *ps)
{
	t_list	*exec;

	exec = ps->exec;
	while (exec->next)
	{
		if (pipe(((t_exec *) (exec->content))->fd) == -1)
			executor_error(ps, "pipe", PIPE_ERROR, errno);
		exec = exec->next;
	}
}

void	executor_fork(t_parser *ps)
{
	t_list	*exec;

	exec = ps->exec;
	while (exec)
	{
		((t_exec *) (exec->content))->pid = fork(); //error
		if (((t_exec *) (exec->content))->pid == 0)
			pipex_exec(exec->content, ps);
		else
			exec = exec->next;
	}
}

void	executor_wait(t_parser *ps)
{
	t_list	*exec;

	exec = ps->exec;
	while (exec)
	{
		waitpid(((t_exec *) (exec->content))->pid, &ps->status, 0);
		exec = exec->next;
	}
}
