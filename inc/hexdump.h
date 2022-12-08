#ifndef HEXDUMP_H
# define HEXDUMP_H


//	External libs
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

//	Macros
# define BUF_SIZE	32768
# define C_RED		"\033[0;31m"
# define C_GREEN	"\033[0;32m"
# define C_YELLOW	"\033[0;33m"
# define C_BLUE		"\033[0;34m"
# define C_PURPLE	"\033[0;35m"
# define C_CYAN		"\033[0;36m"
# define C_RESET	"\033[0;0m"

//	Structs

//	Functions
//	hexdump.c functions

//	error_funcs.c functions
void	error_msg(char *msg);

//	file_funcs.c functions
int		read_file(int fd, char **file_contents);
void	write_contents(char *file_contents, unsigned int len);

//	utils.c functions
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_memjoin(char **s1, int l1, char const *s2, int l2);
char	*ft_strchr(const char *s, int c);
char	*itohex(unsigned int n);

#endif
