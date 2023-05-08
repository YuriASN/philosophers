#include "philo.h"

/*The memset() function writes len bytes of value c (converted to an
unsigned char) to the string dest.	 Undefined behaviour from memset(),
resulting from storage overflow, will occur if len	is greater than	the
length of the dest	buffer.	 The behaviour is also undefined if dest is an
invalid pointer. */
static void	*ft_memset(void *str, int c, int bytes)
{
	int	index;

	index = 0;
	while (index < bytes)
		((unsigned char *)str)[index++] = c;
	return (str);
}

/*The calloc() function allocates space for number of objects, each size
bytes in length. The result is identical to calling malloc() with an
argument of number * size, with the exception that the allocated memory
is explicitly initialized to zero bytes. */
void	*ft_calloc(size_t number, size_t size)
{
	void	*a;

	if ((number * size) == 0)
		return (0);
	a = malloc(number * size);
	if (!a)
		return (0);
	ft_memset(a, 0, (number * size));
	return (a);
}
