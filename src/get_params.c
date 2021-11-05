/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:48:14 by aperez-b          #+#    #+#             */
/*   Updated: 2021/11/05 12:55:41 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	get_here_doc(char *str, char *full, char *limit, char *warn)
{
	char	*temp;
	int		len;

	len = 0;
	while (!str || ft_strncmp(str, limit, len) || ft_strlen(limit) != len)
	{
		temp = full;
		full = ft_strjoin(full, str);
		free(temp);
		free(str);
		str = readline("> ");
		if (!str)
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		temp = str;
		str = ft_strjoin(str, "\n");
		free(temp);
		add_history(str);
		len = ft_strlen(str) - 1;
	}
	free(str);
	write(0, full, ft_strlen(full));
	free(full);
}

t_mini	*get_outfile1(t_mini *node, char **args, char **arg, int ij[2])
{
	char	**next;

	next = NULL;
	if (arg[ij[1] + 1])
		node->outfile = get_fd(node->outfile, &arg[ij[1] + 1][0], 1, 0);
	else
	{
		next = ft_subsplit(args[++ij[0]], "<>");
		if (next)
			node->outfile = get_fd(node->outfile, next[0], 1, 0);
	}
	ft_free_matrix(&next);
	return (node);
}

t_mini	*get_outfile2(t_mini *node, char **args, char **arg, int ij[2])
{
	char	**next;

	next = NULL;
	if (arg[ij[1] + 2])
		node->outfile = get_fd(node->outfile, &arg[ij[1] + 2][0], 1, 1);
	else
	{
		next = ft_subsplit(args[++ij[0]], "<>");
		if (next)
			node->outfile = get_fd(node->outfile, next[0], 1, 1);
	}
	ij[1]++;
	ft_free_matrix(&next);
	return (node);
}

t_mini	*get_infile1(t_mini *node, char **args, char **arg, int ij[2])
{
	char	**next;

	next = NULL;
	if (arg[ij[1] + 1])
		node->infile = get_fd(node->infile, &arg[ij[1] + 1][0], 0, 0);
	else
	{
		next = ft_subsplit(args[++ij[0]], "<>");
		if (next)
			node->infile = get_fd(node->infile, next[0], 0, 0);
	}
	ft_free_matrix(&next);
	return (node);
}

t_mini	*get_infile2(t_mini *node, char **args, char **arg, int ij[2])
{
	char	*limiter;
	char	*warn;
	char	**next;
	char	*temp;

	limiter = NULL;
	next = NULL;
	if (arg[ij[1] + 2])
		limiter = &arg[ij[1] + 2][0];
	else
	{
		next = ft_subsplit(args[++ij[0]], "<>");
		temp = args[ij[0]];
		args[ij[0]] = ft_substr(args[ij[0]], ft_strlen(next[0]), ft_strlen(args[ij[0]]));
		free(temp);
		printf("NEWSTR: %s\n", args[ij[0]]);
		if (next)
			limiter = next[0];
	}
	warn = "minishell: warning: here-document delimited by end-of-file";
	if (limiter)
		get_here_doc(NULL, NULL, limiter, warn);
	ij[1]++;
	ft_free_matrix(&next);
	return (node);
}
