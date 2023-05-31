/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:16:24 by vfedorov          #+#    #+#             */
/*   Updated: 2023/05/31 13:53:34 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		perror("innvlaid");
		exit (1);
	}
	dup2(pip->infile, STDIN_FILENO);
	close(pip->infile);
	dup2(pip->fd[0][1], STDOUT_FILENO);
	close(pip->fd[0][1]);
	close(pip->fd[0][0]);
	if (!ft_strncmp(av[1], "here_doc", 8)
		&& !ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		forex(av[3], env);
	else
		forex(av[2], env);
	write(2, "ERRORINCHILD\n", 13);
	exit(1);
}

void	piping(t_pipex *pip, char **env, char **av, int i)
{
	if (i == 0)
		child(pip, env, av);
	else if (i < pip->ac - 4)
	{
		dup2(pip->fd[i - 1][0], STDIN_FILENO);
		dup2(pip->fd[i][1], STDOUT_FILENO);
		closeall(pip);
		forex(av[i + 2], env);
	}
	else
	{
		dup2(pip->fd[i - 1][0], STDIN_FILENO);
		dup2(pip->outfile, STDOUT_FILENO);
		close(pip->outfile);
		closeall(pip);
		forex(av[pip->ac - 2], env);
		write(2, "ERROR\n", 6);
		exit(1);
	}
	close(pip->infile);
	close(pip->outfile);
	closeall(pip);
}

void	opipip(int ac, t_pipex *pip, char **av, char **env)
{
	int		i;
	int		picre;

	i = 0;
	picre = 0;
	opel(av, pip, ac);
	while (picre < ac - 1)
	{
		if (pipe(pip->fd[picre]) == -1)
		{
			write(2, "An error with opening the pipe \n", 33);
			return ;
		}
		picre++;
	}
	while (i < ac - 3)
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

	pip.ac = ac;
	if (ac >= 5)
	{
		if (!ft_strncmp(av[1], "here_doc", 8)
			&& !ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		{
			here_doc(&pip, av[2]);
		}
		opipip(ac, &pip, av, env);
		close(pip.infile);
		close(pip.outfile);
		closeall(&pip);
		unlink("nadelete");
		while (wait(NULL) != -1)
			;
	}
	else
	{
		write(2, "Duuuuude, podumay v chem mistake!\n", 35);
	}
	return (0);
}
