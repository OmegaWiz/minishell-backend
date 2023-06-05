/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudopipex_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:18:11 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/05 10:21:03 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	cmd_findpath(char **cmd, t_parser *ps)
{
	if (ft_strchr(cmd[0], '/') == NULL)
		return (cmdcheck_path(cmd, ps));
	else
		return (cmdcheck_notpath(cmd, ps));
}

int	cmdcheck_path(char **cmd, t_parser *ps)
{
	int		i;
	char	*newpath;

	i = -1;
	newpath = NULL;
	while (pipex->path[++i] != NULL)
	{
		newpath = ft_strprepend(cmd[0], pipex->path[i], pipex);
		if (access(newpath, F_OK) == 0)
		{
			if (access(newpath, X_OK) != 0)
				return (126); //Permission denied
			cmd[0] = ft_free(cmd[0]);
			cmd[0] = newpath;
			return (0);
		}
		newpath = ft_free(newpath);
	}
	if (newpath == NULL)
		return (127); //command not found
}

int	cmdcheck_notpath(char **cmd, t_parser *ps)
{
	if (access(cmd[0], F_OK) == 0)
	{
		if (access(cmd[0], X_OK) != 0)
			return (126); //Permission denied
		else
			return (0);
	}
	else
		return (127); //No such file or directory
}
