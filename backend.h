/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:56:03 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/30 08:56:17 by kkaiyawo         ###   ########.fr       */
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
# include <limits.h>

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

typedef enum e_error
{
	ARGC_ERROR,
	PIPE_ERROR,
	FORK_ERROR,
	CMD_ERROR,
	FILE_ERROR,
	ACCESS_ERROR,
	OPEN_ERROR,
	CLOSE_ERROR,
	EXEC_ERROR,
	ALLOC_ERROR,
} t_error;

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
	int		pipefd[2];
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
t_parser	*ps_free(t_parser *ps);

/** exec_utils.c
/* *****************************************************************************
initializes the t_exec struct
***************************************************************************** */
t_exec		*exec_init();
/* *****************************************************************************
free t_parser struct
***************************************************************************** */
t_exec		*exec_free(t_exec *exec);

/** fs_utils.c
/* *****************************************************************************
initializes the t_fileset struct
***************************************************************************** */
t_fileset	*fs_init(char *name, int fd, t_filetype type);
/* *****************************************************************************
free t_fileset struct
***************************************************************************** */
void		fs_free(t_fileset *fs);
/* *****************************************************************************
close fd and set to INT_MIN
***************************************************************************** */
void		file_close(int *fd);

/** arr_utils.c
/* *****************************************************************************
convert t_list to char **arr
***************************************************************************** */
char		**lst2arr(t_list *lst);
/* *****************************************************************************
free char **arr
***************************************************************************** */
char		**ft_arrclear(char **arr)

/** parser.c
/* *****************************************************************************
parses the command line arguments
***************************************************************************** */
t_parser	*parser(t_listcmd *cmdlst, char **envp);
/* *****************************************************************************
handle the error in parser
***************************************************************************** */
int			parser_error(t_parser *ps, char *msg, t_error err, int errnum);

int			executor(t_parser *ps);
int			exec_free(t_parser *ps);
int			exec_error(t_parser *ps, char *msg, );

void		pipex_close(t_exec *exec, int ignore);
void		pipex_exec(t_exec *exec, t_parser *ps);
int			pipex_error(t_exec, *exec, t_parser *ps, ...);

#endif
