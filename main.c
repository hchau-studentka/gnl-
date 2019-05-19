/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:40:16 by hchau             #+#    #+#             */
/*   Updated: 2019/05/17 17:40:19 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		main()
{
	int		fd_1;
	int		fd_2;
	char	*line;

	fd_1 = open("test1", O_RDONLY);
	fd_2 = open("./test2", O_RDONLY);

	get_next_line(fd_1, &line);
	ft_putendl(line);
	get_next_line(fd_2, &line);
	ft_putendl(line);
	while (get_next_line(fd_2, &line) == 1)
		ft_putendl(line);
	return (0);
}