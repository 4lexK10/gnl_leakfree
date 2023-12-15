/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:40:41 by akloster          #+#    #+#             */
/*   Updated: 2023/12/14 12:40:41 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int get_read(int fd, char **str)
{
	char	*buf;
	char	*temp;
	int		cnt;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (-1);
	cnt = read(fd, buf, BUFFER_SIZE);
	if (cnt > 0)
		buf[cnt] = '\0';
	if (cnt <= 0)
		return (free(buf), cnt);
	if (!*str)
		temp = ft_strdup(buf, -1);
	else
		temp = ft_strjoin(*str, buf);
	clear(str, &buf);
	if (!temp)
		return (-1);
	*str = temp;
	return (cnt);
}

static char *cleaner(char **str, char *nl)
{
	char	*temp;
	char	*res;

	if (!nl)
	{
		res = ft_strdup(*str, -1);
		clear(str, NULL);
		if (!res)
			return (NULL);
		return (res);
	}
	temp = ft_strdup(++nl, -1);
	if (!temp)
		return (clear(str, NULL));
	res = ft_strdup(*str, finder(*str));
	if (!res)
		return (clear(str, &temp));
	free(*str);
	*str = temp;
	return(res);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*nl;
	int			cnt;

	if (fd < 1 || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	cnt = get_read(fd, &str);
	if (cnt <= 0)
		return (clear(&str, NULL));
	while (cnt > 0 && cnt == BUFFER_SIZE)
		cnt = get_read(fd, &str);
	if (cnt < 0)
		return (clear(&str, NULL));
	cnt = finder(str);
	nl = str + cnt;
	if (cnt < 0)
		nl = NULL;
	return (cleaner(&str, nl));
}

char	*clear(char **str, char **buf)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	return (NULL);
}
