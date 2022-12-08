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
		// Try to read BUF_SIZE bytes from the file
		read_chars = read(fd, temp, BUF_SIZE);
		if (read_chars == 0)
			break;
		if (!*file_contents)
		{
			// On the first lap, malloc file_contents and store read data there
			*file_contents = malloc((read_chars) * sizeof(char));
			if (!*file_contents)
				return (-1);
			ft_memcpy(*file_contents, temp, read_chars);
		}
		else
			// On the following laps, malloc another array, join previously read data, free file_contents and assign new array to it
			ft_memjoin(file_contents, total_chars, temp, read_chars);
		total_chars += read_chars;
	}
	return (total_chars);
}

void	write_contents(char *file_contents, unsigned int len)
{
	const char		base[16] = "0123456789abcdef";
	unsigned int	hex_count;
	unsigned int	i;
	unsigned char	c;
	char			*hex_str;
	int				jump_flag;
	int				repeating;
	int				skipped;

	jump_flag = 0;
	hex_count = 0;
	skipped = 0;
	while ((int)len - (int)hex_count > 0)
	{
		// Check for repeating lines, and skip them
		repeating = 1;
		i = 0;
		while (i < 15)
		{
			if (file_contents[hex_count + i] != file_contents[hex_count + i + 1])
			{
				repeating = 0;
				break;
			}
			i++;
		}
		if (!jump_flag && repeating)
			jump_flag = 1;
		else if (jump_flag && repeating)
		{
			hex_count += 16;
			skipped++;
			continue;
		}
		else if (jump_flag && !repeating)
		{
			if (skipped > 0)
				printf("*\n");
			skipped = 0;
			jump_flag = 0;
		}
		// Print line index in hex format
		hex_str = itohex(hex_count);
		printf("%s%s%s    ", C_RED, hex_str, C_RESET);
		if (hex_str)
			free(hex_str);
		// Print bytes in hex format
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
		// Add spaces at the end of the line if needed to align next part
		if (i < 16)
		{
			int pos = (2 * i) + i / 2;
			while (pos <= 42)
			{
				printf(" ");
				pos++;
			}
		}
		else
			printf("    ");
		printf("%s", C_RESET);
		// Print bytes in char format if printable, else print dots
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
