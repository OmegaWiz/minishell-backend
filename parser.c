/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:56:41 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/30 08:56:08 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

t_parser	*parser(t_listcmd *lc, char **envp)
{
	t_parser	*ps;

	ps = ps_init(envp);
	return (ps);
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
