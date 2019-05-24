/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mplutarc <mplutarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:27:59 by mplutarc          #+#    #+#             */
/*   Updated: 2019/05/24 13:35:43 by mplutarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static t_list	*find_fd(int fd, t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	tmp->content_size = fd;
	ft_lstadd(list, tmp);
	return (tmp);
}

static char		*ft_strnjoin(const char *s1, const char *s2, int len)
{
	char	*str;
	int		nbr;
	char	*d;

	nbr = ft_strlen(s1) + ++len;
	str = ft_strnew(nbr);
	d = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2 && --len > 0)
		*str++ = *s2++;
	*str = '\0';
	return (str - (str - d));
}

static int		find_n_cut(t_list *list, char **line)
{
	int i;

	i = 0;
	while (((char *)list->content)[i] && ((char *)list->content)[i] != '\n')
		++i;
	*line = ft_strndup(list->content, i);
	if (((char *)list->content)[i] == '\n')
		++i;
	list->content = ft_strdup(list->content + i);
	return (i);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*list;
	int				ret;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	list = find_fd(fd, &list);
	while (!ft_strchr(list->content, '\n') && (ret = read(fd, buf, BUFF_SIZE)))
	{
		list->content = ft_strnjoin(list->content, buf, ret);
		printf("this is my str %s \n", list->content);
	}
	ret = find_n_cut(list, line);
	if (ret > 0)
		return (1);
	return (0);
}

int				main(void)
{
	char		*line = NULL;
	int			fd = open("./tests/test1.txt", O_RDONLY);
	int 		i = get_next_line(fd, &line);
	return (0);
}
