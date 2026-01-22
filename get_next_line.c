/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icoman <icoman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:02:19 by icoman            #+#    #+#             */
/*   Updated: 2026/01/22 18:56:35 by icoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list *buffers_head;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	
	buffers_head = get_node_by_fd(&buffers_head, fd);
	if (!buffers_head)
		return (NULL);
}

/* cerca nodo per fd, se non esiste crea nuovo nodo e lo mette in testa */
t_list	*get_node_by_fd(t_list **lst, int fd)
{
	t_list *curr;
	t_list *new_node;

	curr = *lst;
	while (curr != NULL)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	new_node = lst_new_node(fd, NULL);
	if (!new_node)
		return (NULL);
	new_node->next = *lst;
	*lst = new_node;
	return (new_node);
}

t_list	*lst_new_node(int fd, char *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->fd = fd;
	node->content = content;
	node->next = NULL;
	return (node);
}