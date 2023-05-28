/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:14:24 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/28 21:41:32 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	executor(t_parser *ps)
{
	t_list	*exec;

	exec = ps->exec;
	while (exec->next)
	{
		pipe(((t_exec *) (exec->content))->fd); //error
		exec = exec->next;
	}
	exec = ps->exec;
	while (exec)
	{
		((t_exec *) (exec->content))->pid = fork(); //error
		if (((t_exec *) (exec->content))->pid == 0)
			pipex_exec(exec->content, ps);
		else
			exec = exec->next;
	}
	pipex_close(ps->exec, -1);
	exec = ps->exec;
	while (exec)
	{
		waitpid(((t_exec *) (exec->content))->pid, &ps->status, 0);
		exec = exec->next;
	}
	return (exec_free(ps));
}

int	exec_free(t_parser *ps)
{
	int	status;

	status = ps->status;
	ps_free(ps);
	return (WEXITSTATUS(status));
}
