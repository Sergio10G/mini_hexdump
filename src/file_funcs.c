#include <hexdump.h>

int	read_file(int fd, char **file_contents)
{
	char	temp[BUF_SIZE];
	int		read_chars;
	int		total_chars;

	read_chars = -1;
	total_chars = 0;
	while (read_chars != 0)
	{
		read_chars = read(fd, temp, BUF_SIZE);
		if (read_chars == 0)
			break;
		if (!*file_contents)
		{
			*file_contents = malloc((read_chars) * sizeof(char));
			if (!*file_contents)
				return (-1);
			ft_memcpy(*file_contents, temp, read_chars);
		}
		else
			ft_memjoin(file_contents, total_chars, temp, read_chars);
		total_chars += read_chars;
	}
	return (total_chars);
}

void	write_contents(char *file_contents, unsigned int len)
{
	unsigned int	hex_count;
	unsigned int	i;
	unsigned char	c;
	char			*hex_str;
	char			base[16] = "0123456789abcdef";

	hex_count = 0;
	while ((int)len - (int)hex_count > 0)
	{
		hex_str = itohex(hex_count);
		printf("%s%s%s    ", C_RED, hex_str, C_RESET);
		if (hex_str)
			free(hex_str);
		i = 0;
		printf("%s", C_GREEN);
		while (i < 16 && hex_count + i < len)
		{
			c = (unsigned char) file_contents[hex_count + i];
			printf("%c%c", base[(c / 16) % 16], base[c % 16]);
			if (i % 2 && i != 15)
				printf(" ");
			i++;
		}
		if (i < 16)
		{
			int pos = (2 * i) + i / 4;
			while (pos <= 40)
			{
				printf(" ");
				pos++;
			}
		}
		else
			printf("    ");
		printf("%s", C_RESET);
		printf("%s", C_CYAN);
		i = 0;
		while (i < 16 && hex_count + i < len)
		{
			c = file_contents[hex_count + i];
			if (c < 32 || c > 126)
				printf("· ");
			else
				printf("%c ", c);
			i++;
		}
		printf("%s\n", C_RESET);
		hex_count += 16;
	}
}
