#include "get_next_line.h"

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

char	*ft_delete_line(char *stock)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		ft_free(&stock);
		return (NULL);
	}
	res = (char *)malloc(ft_strlen(stock) - i + 1);
	if (!res)
		return (NULL);
	i++;
	while (stock[i])
		res[j++] = stock[i++];
	res[j] = '\0';
	ft_free(&stock);
	return (res);
}

char	*ft_read_line(char *stock, int fd)
{
	char	*buff;
	int		check_error;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	check_error = 1;
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	while (!ft_strchr(stock, '\n') && check_error != 0)
	{
		check_error = read(fd, buff, BUFFER_SIZE);
		if (check_error == -1)
		{
			ft_free(&buff);
			return (NULL);
		}
		buff[check_error] = '\0';
		if (buff[0])
			stock = ft_strjoin(stock, buff);
	}
	ft_free(&buff);
	return (stock);
}

int	ft_strlen_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char		*stock = NULL;
	char			*line;
	int				i;

	i = 0;
	stock = ft_read_line(stock, fd);
	if (!stock)
		return (NULL);
	if (!stock[i])
	{
		ft_free(&stock);
		return (NULL);
	}
	line = (char *)malloc(ft_strlen_newline(stock) + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (stock[++i] && stock[i] != '\n')
		line[i] = stock[i];
	if (stock[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	stock = ft_delete_line(stock);
	return (line);
}
