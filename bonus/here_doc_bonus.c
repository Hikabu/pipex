/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfedorov <vfedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:01:48 by vfedorov          #+#    #+#             */
/*   Updated: 2023/05/09 17:54:58 by vfedorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_pipex *pip, char *lim)
{
	char	*str;

	pip->infile = open("nadelete", O_CREAT | O_RDWR, 0644);
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		str = get_next_line(0);
		if (!str || !*str)
		{
			free (str);
			write(1, "\n", 1);
			break ;
		}
		if (!ft_strncmp(lim, str, ft_strlen(str) - 1)
			&& !ft_strncmp(lim, str, ft_strlen(lim)))
		{
			free (str);
			break ;
		}
		write(pip->infile, str, ft_strlen(str));
	}
	close(pip->infile);
	pip->infile = open("nadelete", O_RDONLY);
}
