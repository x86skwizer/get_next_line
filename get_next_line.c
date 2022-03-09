/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 22:57:35 by yamrire           #+#    #+#             */
/*   Updated: 2022/03/08 04:51:49 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	new_line_index(char *str)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	return (index);
}

char	*return_new_line(char **stash, int rd, char **buff)
{
	char	*tmp;
	char	*tmp1;
	int		index;
	int		len;

	free(*buff);
	if (rd < 0 || !(*stash))
		return (NULL);
	index = new_line_index(*stash);
	//len = ft_strlen(*stash);
	tmp = ft_substr(*stash, 0, index + 1);
	tmp1 = ft_substr(*stash, index + 1, ft_strlen(*stash) - index);
	free(*stash);
	if (tmp1[0] == '\0')
	{
		free (tmp1);
		*stash = NULL;
	}
	else
		*stash = tmp1;
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buff;
	char		*line;
	int			rd;

	if (fd < 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	rd = read(fd, buff, BUFFER_SIZE);
	while (rd > 0)
	{
		buff[rd] = '\0';
		if (!stash)
			stash = ft_strdup(buff);
		else if (buff)
		{
			line = ft_strjoin(stash, buff);
			free(stash);
			stash = line;
		}
		if (ft_strchr(stash, '\n') != NULL)
			break ;
		rd = read(fd, buff, BUFFER_SIZE);
	}
	return (return_new_line(&stash, rd, &buff));
}
