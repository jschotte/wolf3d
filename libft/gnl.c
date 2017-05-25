/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 09:30:10 by jschotte          #+#    #+#             */
/*   Updated: 2017/05/24 00:54:23 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		allocation(char **buff, char ***mem)
{
	char *tmp;

	tmp = ft_strjoin(**mem, *buff);
	free(**mem);
	**mem = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
}

static int		gnl_check(char **mem, char **line)
{
	int		size;
	char	*tmp;

	if (ft_strchr(*mem, '\n') != NULL)
	{
		size = ft_strchr(*mem, '\n') - *mem;
		tmp = ft_strsub(*mem, 0, size);
		*line = ft_strdup(tmp);
		ft_strdel(&tmp);
		tmp = ft_strdup(*mem);
		free(*mem);
		*mem = ft_strsub(tmp, (size + 1), ft_strlen(tmp));
		free(tmp);
		return (1);
	}
	return (0);
}

static void		gnl_read_check(char **buff, int count, char **line, char ***mem)
{
	int		size;
	char	*tmp;

	size = ft_strchr(*buff, '\n') - *buff;
	tmp = ft_strsub(*buff, 0, size);
	if (**mem)
	{
		*line = ft_strjoin(**mem, tmp);
		free(**mem);
	}
	else
		*line = ft_strdup(tmp);
	**mem = ft_strsub(*buff, (size + 1), count);
	free(tmp);
}

static int		gnl_read(int fd, int count, char **mem, char **line)
{
	char	*buff;

	buff = ft_strnew(BUFF_SIZE);
	while ((count = read(fd, buff, BUFF_SIZE)))
	{
		if (count == -1)
			return (-1);
		buff[count] = '\0';
		if (ft_strchr(buff, '\n') != NULL)
		{
			gnl_read_check(&buff, count, &line[0], &mem);
			break ;
		}
		if (*mem)
			allocation(&buff, &mem);
		else
			*mem = ft_strdup(buff);
	}
	free(buff);
	buff = NULL;
	return (count);
}

int				get_next_line(int fd, char **line)
{
	static char *mem;
	int			count;

	if (BUFF_SIZE <= 0 || fd < 0 || line == NULL)
		return (-1);
	if (mem)
	{
		if (gnl_check(&mem, &line[0]) == 1)
			return (1);
	}
	if ((count = gnl_read(fd, 0, &mem, &line[0])) == -1)
		return (-1);
	if (count > 0)
		return (1);
	if (mem == NULL)
		return (0);
	*line = ft_strdup(mem);
	free(mem);
	mem = NULL;
	if (line[0][0] == '\0')
		return (0);
	return (1);
}
