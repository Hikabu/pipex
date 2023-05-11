/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 16:37:17 by vfedorov          #+#    #+#             */
/*   Updated: 2023/05/09 17:49:25 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	pip->infile = open(av[1], O_RDONLY);
	pip->outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pip->outfile < 0)
		exit (1);
}
