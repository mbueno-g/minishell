/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:08:50 by aperez-b          #+#    #+#             */
/*   Updated: 2021/11/09 19:33:02 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

# define READ_END 0
# define WRITE_END 1

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
}			t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	PWD = 3,
	NCMD = 4,
};

/* C implementation of the cd shell command */
int		cd(char **argv);

/* Handles all builtin functions */
int		builtin(t_prompt *prompt);

/* C implementation of the pwd shell command */
int		pwd(void);

/* C implementation of the echo shell command */
int		echo(char **argv);

/* C implementation of the env shell command */
int		env(int argc, char **envp);

/* C implementation of the export shell command */
int		export(t_prompt *prompt, int argc, char **argv);

/* Splits command and args into a matrix, taking quotes into account */
char	**ft_cmdtrim(char const *s, char *set);

/* Strtrim from all occurrences of set */
char	*ft_strtrim_all(char const *s1, int squote, int dquote);

/* Parses all necessary stuff for a command matrix */
t_mini	*fill_node(char **args, t_mini *node);

/* Opens a file to a file descriptor with the adequate open flags */
int		get_fd(int oldfd, char *path, int is_outfile, int append);

/* Tries to open proper file as outfile (> case) */
t_mini	*get_outfile1(t_mini *node, char **args, char **arg, int ij[2]);

/* Tries to open proper file as outfile (>> case) */
t_mini	*get_outfile2(t_mini *node, char **args, char **arg, int ij[2]);

/* Tries to open proper file as infile (< case) */
t_mini	*get_infile1(t_mini *node, char **args, char **arg, int ij[2]);

/* Tries to open read heredoc as infile (<< case) */
t_mini	*get_infile2(t_mini *node, char **args, char **arg, int ij[2]);

/* Fills in linked list node with command info */
t_list	*parse_args(char **args);

/* Executes a command according to the info on our list */
int		exec_cmd(t_list *cmd, char **envp);

/* Checks if a command is in the PATH variable and retrieves the full_path */
void	get_cmd(t_mini *node);

/* Expand $-variables*/
char	*expand_vars(char *str, int ij[2], int quotes[2]);

/*Expand ~-variable*/
char	*expand_path(char *str, int i, int quotes[2]);

/**/
int		get_here_doc(char *str, char *full, char *limit, char *warn);

/**/
int		mini_perror(int err, char *param);

#endif
