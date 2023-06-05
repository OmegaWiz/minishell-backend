/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:14:24 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/05 08:51:16 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	executor(t_listcmd *lc, char **envp)
{
	t_parser	*ps;
	int			status;

	ps = parser(lc, envp);
	if (!ps)
		return (ENOMEM); // needs fix when error is done
	status = executor_fork(ps);
	if (status != 0)
		return (status); // needs fix when error is done
	pipes_close(ps, {0, 1});
	status = executor_wait(ps);
	ps_free(ps);
	return (status);
}

int	executor_fork(t_parser *ps)
{
	t_list	*exec;

	exec = ps->exec;
	while (exec)
	{
		((t_exec *) (exec->content))->pid = fork();
		if (((t_exec *) (exec->content))->pid == -1)
			return (errno);
		else if (((t_exec *) (exec->content))->pid == 0)
		{
			pipex_exec(exec->content, ps);
			return (errno);
		}
		else
			exec = exec->next;
	}
	return (0);
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
