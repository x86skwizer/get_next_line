/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 22:57:35 by yamrire           #+#    #+#             */
/*   Updated: 2022/03/12 17:33:09 by yamrire          ###   ########.fr       */
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
char *ft_line(char *str)
{
	char *line;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!str ||!str[0])
		return (NULL);
	line = (char *)malloc(new_line_index(str) + 2);
	while(str[i] && str[i] != '\n')
		line[j++] = str[i++];
	if (str[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char *ft_delete(char *str)
{
	char *res;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (NULL);
	res = (char *)malloc(ft_strlen(str) - new_line_index(str) + 1);
	while(str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while(str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	str = NULL;
	return (res);
}
/*char	*return_new_line(char **stash, int rd, char *buff)
{
	char	*tmp;
	char	*tmp1;
	int		index;

	free(buff);
	if (rd < 0 || !(*stash))
		return (NULL);
	index = new_line_index(*stash);
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
}*/

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*buff;
	char		*line;
	int			rd;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	//rd = read(fd, buff, BUFFER_SIZE);
	rd = 1;
	while (rd != 0 && ft_strchr(stash, '\n') == NULL)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buff);
			buff = NULL;
			return (NULL);
		}
		buff[rd] = '\0';
		stash = ft_strjoin(stash, buff);
		/*if (ft_strchr(stash, '\n') != NULL)
			break ;*/
	}
	free(buff);
	buff = NULL;
	line = ft_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = ft_delete(stash);
	return(line);
}
