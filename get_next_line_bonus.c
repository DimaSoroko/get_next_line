/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:21:36 by dsoroko           #+#    #+#             */
/*   Updated: 2022/05/23 17:33:09 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @brief
 * The function make_new_line takes the stash with a line containing '\n' or
 * end of file and eliminates everything that is after '\n'
 */

char	*make_new_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/**
 * @brief
 *  The function clean_up takes the stash and cleans it up, ie gets rid of the
 *	line that is retuned by get_next_line.
 */

char	*clean_the_rest(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	new_str = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (str[i] != '\0')
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

/**
 * @brief
 * The function read_and_stash reads the file referenced by fd and returns
 * what is read until '\n' or end of file is encountered.
 */

char	*read_and_stash(int fd, char *str)
{
	int		char_count;
	char	*temp;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	char_count = 1;
	while (!ft_strchr(str, '\n') && char_count != 0)
	{
		char_count = read(fd, temp, BUFFER_SIZE);
		if (char_count == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[char_count] = '\0';
		str = ft_strjoin(str, temp);
	}
	free(temp);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (stash[fd] == NULL)
		return (NULL);
	line = make_new_line(stash[fd]);
	stash[fd] = clean_the_rest(stash[fd]);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 	int fd;
// 	fd = open("t.txt", O_RDONLY);
// 	char *str;
// 	str = get_next_line(fd);
// 	printf("%s", str);
// 	while (str)
// 	{
// 		str = get_next_line(fd);
// 		printf("%s", str);
// 	}
// 	return 0;
// }
