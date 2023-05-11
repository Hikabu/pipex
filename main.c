/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:16:24 by vfedorov          #+#    #+#             */
/*   Updated: 2023/05/09 17:51:14 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	forex(char *cm, char **env)
{
	char	**cmd;
	char	*way;

	cmd = ft_split(cm, ' ');
	way = pasplit(env, cmd[0], 0);
	execve(way, cmd, env);
}

void	child(t_pipex *pip, char **env, char **av)
{
	if (pip->infile < 0)
	{
		perror("ERROR s infile");
		exit (1);
	}
	dup2(pip->infile, STDIN_FILENO);
	close(pip->infile);
	dup2(pip->fd[1], STDOUT_FILENO);
	close(pip->fd[1]);
	close(pip->fd[0]);
	forex(av[2], env);
	write(2, "ERROR", 6);
}

void	piping(t_pipex *pip, char **env, char **av, int i)
{
	if (i == 0)
	{
		child(pip, env, av);
	}
	else
	{
		close(pip->fd[1]);
		dup2(pip->fd[0], STDIN_FILENO);
		dup2(pip->outfile, STDOUT_FILENO);
		close(pip->outfile);
		close(pip->fd[0]);
		forex(av[3], env);
		write(2, "ERROR", 6);
	}
	close(pip->infile);
	close(pip->outfile);
	close(pip->fd[0]);
	close(pip->fd[1]);
}

void	opipip(int ac, t_pipex *pip, char **av, char **env)
{
	int		i;

	i = 0;
	opel(av, pip, ac);
	if (pipe(pip->fd) == -1)
	{
		write(2, "An error with opening the pipe \n", 33);
		return ;
	}
	while (i < 2)
	{
		pip->r = fork();
		if (pip->r == 0)
			piping(pip, env, av, i);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pip;

	if (ac == 5)
	{
		opipip(ac, &pip, av, env);
		close(pip.infile);
		close(pip.outfile);
		close(pip.fd[0]);
		close(pip.fd[1]);
		while (wait(NULL) != -1)
			;
	}
	else
		write(2, "Duuuuude, podumay v chem mistake!\n", 35);
	return (0);
}
