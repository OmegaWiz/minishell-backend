/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudopipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:05:07 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/05 09:07:40 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

void		pipex_exec(t_exec *exec, t_parser *ps)
{
	int	fd[2];

	fd[0] = fs_check(exec->infile);
	fd[1] = fs_check(exec->outfile);
}

void		pipex_close(t_parser *ps, int ignore[2])
{
	t_list	*exec;
	t_exec	*ex;

	exec = ps->exec;
	while (exec)
	{
		ex = (t_exec *) exec->content;
		fs_close(ex->infile, ignore);
		fs_close(ex->outfile, ignore);
		file_close(&ex->pipefd[0]);
		file_close(&ex->pipefd[1]);
		exec = exec->next;
	}
}

int			pipex_error(t_parser *ps, char *msg, t_error err, int errnum);
