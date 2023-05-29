/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:56:03 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/29 15:11:05 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKEND_H
# define BACKEND_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

typedef enum e_filetype
{
	STDIN,
	STDOUT,
	INFILE,
	HEREDOC,
	OUTFILE,
	APPEND,
	PIPE,
} t_filetype;

typedef struct s_listcmd
{
	char				**cmd;
	struct s_listcmd	*next;
}						t_listcmd;
typedef struct s_fileset
{
	char		*name;
	int			fd;
	t_filetype	type;
}				t_fileset;

typedef struct s_exec
{
	int		pid; //change to pid_t in mac
	int		pipe[2];
	t_list	*cmdlst;
	char	**cmdarr;
	t_list	*infile;
	t_list	*outfile;
}			t_exec;

typedef struct s_parser
{
	char	**envp;
	char	**path;
	t_list	*exec;
	int		status;
}			t_parser;

/** parser_utils.c
/* *****************************************************************************
initializes the t_parser struct
***************************************************************************** */
t_parser	*ps_init(char **envp);
/* *****************************************************************************
get PATH from envp
***************************************************************************** */
char		**ps_getpath(char **envp)
/* *****************************************************************************
free t_parser struct
***************************************************************************** */
void		ps_free(t_parser *ps);

t_exec		*exec_init(...);
void		exec_free(t_exec *exec);
t_fileset	*fileset_init(...);
void		fileset_free(t_fileset *fileset);

t_parser	parser(void *toklist);
int			parser_error(t_parser *ps, ...);

int			executor(t_parser *ps);
int			exec_free(t_parser *ps);
int			exec_error(t_parser *ps, ...);

void		pipex_close(t_exec *exec, int ignore);
void		pipex_exec(t_exec *exec, t_parser *ps);
int			pipex_error(t_exec, *exec, t_parser *ps, ...);

#endif
