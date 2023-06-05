/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:56:41 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/05 14:40:04 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

t_parser	*parser(t_listcmd *lc, char **envp)
{
	t_parser	*ps;
	t_exec		*exec;
	t_listcmd	*ptr;
	int			sz;

	ps = ps_init(envp);
	if (!ps)
		parser_error(ps, "malloc", MALLOC_ERROR, errno);
	ptr = lc;
	while (ptr)
	{
		sz = ft_lstsize(ps->exec);
		exec = parse2exec(ptr);
		if (!exec)
			parser_error(ps, "malloc", MALLOC_ERROR, errno);
		ft_lstadd_back(&ps->exec, ft_lstnew(exec));
		if (sz + 1 != ft_lstsize(ps->exec))
			parser_error(ps, "malloc", MALLOC_ERROR, errno);
		ptr = ptr->next;
	}
	return (ps);
}

t_exec	*parse2exec(t_listcmd *lc) //check malloc error
{
	t_exec		*exec;
	char		*str;
	int			i;

	exec = exec_init();
	if (!exec)
		return (NULL);
	i = -1;
	while (lc->cmd[++i])
	{
		str = lc->cmd[i];
		if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0 ||
			ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0)
			parse2fs(lc->cmd, i++, exec);
		else
			ft_lstadd_back(&exec->cmd, ft_lstnew(ft_strdup(str)));
	}
	return (exec);
}

void	parse2fs(char **cmd, int i, t_exec *exec)
{
	if (ft_strncmp(str[i], ">>", 2) == 0)
		ft_lstadd_back(&exec->fs, ft_lstnew(fs_init(str[i + 1], APPEND)));
	else if (ft_strncmp(str[i], "<<", 2) == 0)
		ft_lstadd_back(&exec->fs, ft_lstnew(fs_init(str[i + 1], HEREDOC)));
	else if (ft_strncmp(str[i], "<", 1) == 0)
		ft_lstadd_back(&exec->fs, ft_lstnew(fs_init(str[i + 1], READ)));
	else if (ft_strncmp(str[i], ">", 1) == 0)
		ft_lstadd_back(&exec->fs, ft_lstnew(fs_init(str[i + 1], WRITE)));
	//autopilot
}

int	parser_error(t_parser *ps, char *msg, t_error err, int errnum)
{
	ft_putstr_fd("minishell: ", 2);
	if (err == CMD_ERROR || err == FILE_ERROR || err == ACCESS_ERROR)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err == CMD_ERROR)
		ft_putendl_fd("command not found", 2);
	else
		ft_putendl_fd(strerror(errnum), 2);
	ps_free(ps);
	exit(errnum);
}
