/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:37:17 by vfedorov          #+#    #+#             */
/*   Updated: 2023/05/09 17:56:12 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_fpath(char **env)
{
	char	*fin;
	int		i;

	i = 0;
	fin = "PATH=";
	while (env[i])
	{
		if (!ft_strncmp(env[i], fin, 5))
			return (env[i]);
		i++;
	}
	return (NULL);
}

void	error(char *av)
{
	if (ft_strncmp(av, "../", 3) == 0)
	{
		perror("Fatal blin mistaken error");
		system ("leaks pipex");
		exit(1);
	}
}

char	*pasplit(char **env, char *av, int i)
{
	char	*path;
	char	**split;
	char	*tmp;

	if (access(av, X_OK) == 0)
		return (av);
	path = ft_fpath(env);
	if (!path)
		return (NULL);
	split = ft_split(&path[5], ':');
	error(av);
	while (split[i])
	{
		tmp = ft_strjoin(split[i], "/");
		path = ft_strjoin(tmp, av);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	opel(char **av, t_pipex *pip, int ac)
{
	if (ft_strncmp(av[1], "here_doc", 8) != 0
		&& ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) != 0)
	{
		pip->infile = open(av[1], O_RDONLY);
		pip->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else
		pip->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (pip->outfile < 0)
		exit (1);
}

void	closeall(t_pipex *pip)
{
	int		c;

	c = 0;
	while (c < pip->ac - 1)
	{
		close (pip->fd[c][0]);
		close (pip->fd[c][1]);
		c++;
	}
}
