/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:05:01 by aperez-b          #+#    #+#             */
/*   Updated: 2021/11/09 19:37:50 by mbueno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_fd(int oldfd, char *path, int is_outfile, int append)
{
	int	fd;

	if (!path)
		return (-1);
	if (oldfd > 2)
		close(oldfd);
	if (is_outfile && append)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (is_outfile && !append)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (!is_outfile)
		fd = open(path, O_RDONLY);
	return (fd);
}

static t_mini	*get_params(t_mini *node, char **args, char **arg, int ij[2])
{
	if (arg[ij[1]][0] == '>' && arg[ij[1] + 1] && arg[ij[1] + 1][0] == '>')
		node = get_outfile2(node, args, arg, ij);
	else if (arg[ij[1]][0] == '>')
		node = get_outfile1(node, args, arg, ij);
	else if (arg[ij[1]][0] == '<' && arg[ij[1] + 1] && arg[ij[1] + 1][0] == '<')
		node = get_infile2(node, args, arg, ij);
	else if (arg[ij[1]][0] == '<')
		node = get_infile1(node, args, arg, ij);
	else
		node->full_cmd = ft_extend_matrix(node->full_cmd, arg[ij[1]]);
	return (node);
}

t_mini	*fill_node(char **args, t_mini	*node)
{
	int		ij[2];
	char	**arg;

	ij[0] = 0;
	while (args[ij[0]])
	{
		ij[1] = -1;
		arg = ft_subsplit(args[ij[0]], "<>");
		if (!arg)
			return (NULL);
		while (arg[++ij[1]])
			get_params(node, args, arg, ij);
		ft_free_matrix(&arg);
		ij[0] += (args[ij[0]] != NULL);
	}
	return (node);
}
