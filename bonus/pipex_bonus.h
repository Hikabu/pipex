/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:51:40 by vfedorov          #+#    #+#             */
/*   Updated: 2023/05/09 14:31:02 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include<unistd.h>
# include<stdio.h>
# include<stddef.h>
# include<stdlib.h>
# include<fcntl.h>
# include<sys/wait.h>
# include<libft.h>
# include "get_next_line.h"

typedef struct s_pipex
{
	char	*cmd;
	int		outfile;
	int		infile;
	int		fd[4242][2];
	int		ac;
	pid_t	r;
}		t_pipex;

char	*pasplit(char **env, char *av, int i);
char	**ft_split(char const *s, char c);
void	ft_putstr(char *str);
void	opel(char **av, t_pipex *pip, int ac);
void	closeall(t_pipex *pip);
void	here_doc(t_pipex *pip, char *lim);

#endif
