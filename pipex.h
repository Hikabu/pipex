/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:51:40 by vfedorov          #+#    #+#             */
/*   Updated: 2023/05/02 20:42:07 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include<unistd.h>
# include<stdio.h>
# include<stddef.h>
# include<stdlib.h>
# include<fcntl.h>
# include<sys/wait.h>
# include<libft.h>

typedef struct s_pipex
{
	char	*cmd;
	int		outfile;
	int		infile;
	int		fd[2];
	pid_t	r;
}		t_pipex;

char	*pasplit(char **env, char *av, int i);
char	**ft_split(char const *s, char c);
void	ft_putstr(char *str);
void	opel(char **av, t_pipex *pip, int ac);

#endif
