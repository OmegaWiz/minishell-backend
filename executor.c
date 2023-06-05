/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:14:24 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/05 08:43:00 by kkaiyawo         ###   ########.fr       */
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
	status = pipexpp(ps);
	if (status != 0)
		return (status); // needs fix when error is done
	pipes_close(ps);
	status = wait_all(ps);
	ps_free(ps);
	return (status);
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
