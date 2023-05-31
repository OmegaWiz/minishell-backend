/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudopipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:05:07 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/30 16:34:57 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

void		pipex_exec(t_exec *exec, t_parser *ps);

void		pipex_close(t_exec *exec, int ignore);

int			pipex_error(t_parser *ps, char *msg, t_error err, int errnum);
