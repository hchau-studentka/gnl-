/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:35:52 by hchau             #+#    #+#             */
/*   Updated: 2019/05/13 12:35:58 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void					ft_gnl_lstdel(t_gnlist *put_in)
{
	if (put_in == NULL)
		return ;
	if (put_in->content)
		free(put_in->content);
	put_in->fd = 0;
	put_in->next = NULL;
}

static t_gnlist			*ft_gnl_lstnew(char *put, int fd, t_gnlist *put_in)
{
	if (put == NULL || *put == '\0')
		return (NULL);
	if (!(put_in->content = malloc((sizeof(char)) * (ft_strlen(put) + 1))))
		return (NULL);
	put_in->fd = fd;
	put_in->content = ft_memcpy(put_in->content, put, (ft_strlen(put)));
	put_in->content[ft_strlen(put)] = '\0';
	put_in->next = NULL;
	return (put_in);
}

static int				join_line(t_gnlist *put_in, char **line)
{
	char				*to_free;

	if (put_in && put_in->content != NULL && put_in->content[0] != '\0')
	{
		to_free = *line;
		*line = ft_strcdup(put_in->content, '\n');
		ft_strdel(&to_free);
		to_free = put_in->content;
		if ((ft_strchr(put_in->content, '\n')))
			put_in->content = ft_strdup(ft_strchr(put_in->content, '\n') + 1);
		ft_strdel(&to_free);
		return (1);
	}
    if (put_in && put_in->content != NULL && put_in->content[0] != '\0')
		ft_gnl_lstdel(put_in);
	return (0);
}

static char				*to_read(int fd, char **line)
{
	char				buf[BUFF_SIZE + 1];
	ssize_t				ret;
	char				*to_free;
	char				*extra;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		to_free = *line;
		if (!(ft_strchr(buf, '\n')))
		{
			*line = ft_strjoin(*line, buf);
			ft_strdel(&to_free);
		}
		if ((ft_strchr(buf, '\n')))
		{
			extra = ft_strcdup(buf, '\n');
			*line = ft_strjoin(*line, extra);
			ft_strdel(&extra);
			ft_strdel(&to_free);
			extra = ft_strdup((ft_strchr(buf, '\n') + 1));
			return (extra);
		}
	}
	return (NULL);
}

int						get_next_line(int fd, char **line)
{
	char				buf[1];
	t_gnlist			*put_in;
	t_gnlist			priv;
	static t_gnlist		*head;
	char				*to_free;

	if (fd < 0 || !line || (read(fd, buf, 0)) < 0)
		return (-1);
	*line = ft_strnew(0);
	put_in = head;
	to_free = *line;
	while (put_in)
	{
		if (put_in->fd == fd)
		{
			if (join_line(put_in, line) == 1)
				return (1);
		}
		put_in = put_in->next;
	}
	if (put_in == NULL)
		put_in = ft_gnl_lstnew(to_read(fd, line), fd, &priv);
	if (to_free == *line)
		return (0);
	return (1);
}
