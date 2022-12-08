#include <hexdump.h>

int	main(int argc, char **argv)
{
	int		fd;
	int		fc_len;
	char	*file_contents;

	// Throw error if no arguments are provided
	if (argc < 2)
		error_msg("You need at least 1 parameter to run this program.\nUsage: ./hexdump [files-to-process]");
	for (int i = 1; i < argc; i++)
	{
		// Init variables to avoid weird stuff, specially file_contents
		fd = -1;
		file_contents = 0;
		// Print file name
		printf("%s>> %s%s\n", C_YELLOW, argv[i], C_RESET);
		fd = open(argv[i], O_RDWR);
		if (fd < 0)
		{
			printf("%sCouldn't open file %s%s\n\n", C_RED, argv[i], C_RESET);
			continue;
		}
		//	Read file contents and store it in file_contents
		fc_len = read_file(fd, &file_contents);
		if (fc_len <= 0)
		{
			// Error comp
			if (fc_len == 0)
				printf("Empty file\n\n");
			else if (fc_len == -1)
				printf("%sError reading file%s%s\n\n", C_RED, argv[i], C_RESET);
			continue;
		}
		else
		{
			// Write the actual hexdump and free malloc-ed data
			write_contents(file_contents, (unsigned int)fc_len);
			printf("\n");
			free(file_contents);
		}
	}
}
