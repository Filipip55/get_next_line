/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icoman <icoman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:34:47 by icoman            #+#    #+#             */
/*   Updated: 2026/01/24 18:38:50 by icoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* legge linea per linea un file
	-una linea e' terminata da \n oppure EOF
	-trova o crea il nodo corrispondente al fd
	-legge dal file e accumula nello stash
	-estrae dallo stash la riga da restituire
	-ripulisce lo stash in caso di una eventuale prossima chiamata
	-se lo stash è vuoto abbiamo raggiunto EOF,
		quindi elimina il nodo di quel fd */
char	*get_next_line(int fd)
{
	static t_list	*buffers_head = NULL;
	t_list			*curr;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	curr = get_node_by_fd(&buffers_head, fd);
	if (!curr)
		return (NULL);
	curr->content = read_and_stash(fd, curr->content);
	if (!curr->content)
	{
		remove_node(&buffers_head, fd);
		return (NULL);
	}
	line = extract_line(curr->content);
	curr->content = update_stash(curr->content);
	if (!curr->content)
		remove_node(&buffers_head, fd);
	return (line);
}

/* legge dal file descriptor e aggiorna 
	lo stash (stringa contenente i dati letti finora) */
char	*read_and_stash(int fd, char *stash)
{
	char	*buf;
	int		read_bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (!search_newline(stash) && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		stash = strjoin_and_free(stash, buf);
	}
	free(buf);
	return (stash);
}

/* concatena stash e buf liberando poi stash */
char	*strjoin_and_free(char *stash, char *buf)
{
	char	*joined;
	int		i;
	int		j;

	if (!stash)
	{
		stash = malloc(sizeof(char));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	if (!buf)
		return (stash);
	joined = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buf) + 1));
	if (!joined)
		return (free(stash), NULL);
	i = -1;
	while (stash[++i])
		joined[i] = stash[i];
	j = -1;
	while (buf[++j])
		joined[i + j] = buf[j];
	joined[i + j] = '\0';
	free(stash);
	return (joined);
}

/* estrae la linea dalla stash */
char	*extract_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash || !stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + (stash[i] == '\n') + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/* aggiorna lo stash liberando la parte già estratta */
char	*update_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (free(stash), NULL);
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}
