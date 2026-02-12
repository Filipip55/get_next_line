#include "get_next_line.h"
#include <stdlib.h>

char *get_next_line(int fd);

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	int i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Linea %d --> %s", i++, line);
		free(line);
	}
	close(fd);
	return (0);
}
