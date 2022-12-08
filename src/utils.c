#include <hexdump.h> 

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		*((char *) dst + i) = *((char *) src + i);
		i++;
	}
	return (dst);
}

void	ft_memjoin(char **s1, int l1, char const *s2, int l2)
{
	char	*result;

	if (!*s1 || !s2)
		return ;
	result = malloc((l1 + l2) * sizeof(char));
	if (!result)
		return ;
	ft_memcpy(result, *s1, l1);
	ft_memcpy(result + l1, s2, l2);
	free(*s1);
	*s1 = result;
}

char	*itohex(unsigned int n)
{
	int		i;
	char	base[16] = "0123456789abcdef";
	char	*out;

	out = malloc(9 * sizeof(char));
	if (!out)
		return (0);
	i = 7;
	out[8] = 0;
	while (i >= 0)
	{
		out[i--] = base[n % 16];
		n /= 16;
	}
	return (out);
}
