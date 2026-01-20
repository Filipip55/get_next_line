/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icoman <icoman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:02:19 by icoman            #+#    #+#             */
/*   Updated: 2026/01/20 19:51:40 by icoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static int	line = 0;
	char	*buffer;

	buffer = (char *)malloc();
	line++;
}



	

void	*calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	unsigned int	total_size;
	size_t	i;
	char	*d;
	
	if (nmemb == 0 || size == 0)
		total_size = 1;
	else
		total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	d = (char *) ptr;
	i = 0;
	while (i < total_size)
		d[i++] = '\0';
	return (ptr);
}