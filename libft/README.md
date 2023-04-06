# frequently used functions
## no need to free() after use
### memset
The memset() function writes len bytes of value c (converted to an unsigned char) to the string b.
```c
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			count;
	unsigned char	*ptr;

	count = 0;
	ptr = (unsigned char *)b;
	while (count < len)
	{
		*(ptr + count) = (unsigned char)c;
		count++;
	}
	return (b);
}
```
### memcpy
The memcpy() function copies n bytes from memory area src to dst. If dst and src overlap, behavior is undefined. Applications in which dst and src might overlap should use memmove(3) instead.
```c 
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			count;
	unsigned char	*dummy_dst;
	unsigned char	*dummy_src;

	count = 0;
	dummy_dst = (unsigned char *)dst;
	dummy_src = (unsigned char *)src;
	if (dummy_dst == NULL && dummy_src == NULL)
		return (NULL);
	while (count < n)
	{
		*dummy_dst++ = *dummy_src++;
		count++;
	}
	return (dst);
}
```
### memmove
The memmove() function copies len bytes from string src to dst. The two strings may overlap; the copy is always done in a non-destructive manner.
```c
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dummy_src;
	unsigned char	*dummy_dst;

	dummy_src = (unsigned char *)src;
	dummy_dst = (unsigned char *)dst;
	if (dummy_dst == NULL && dummy_src == NULL)
		return (NULL);
	if (len == 0)
		return (dst);
	if (dummy_src > dummy_dst)
		return (ft_memcpy(dummy_dst, dummy_src, len));
	while (len--)
		*(dummy_dst + len) = *(dummy_src + len);
	return (dst);
}
```

### strlcpy
strlcpy() copies up to dstsize - 1 characters from the string src to dst, NUL-terminating the result if dstsize is not 0.

Copy the shorter length between "dstsize" and "srcsize"  
If src is shorter, append src after dst, "srcsize - 1"   
If dst is shorter, cover dst to src, "dstsize - 1"  
The end of the string is null.   
```c
static void	ft_nlen_cpy(unsigned char	*src, unsigned char	*dst, size_t len)
{
	size_t	count;

	count = 0;
	while (count < len)
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned char	*dummy_src;
	unsigned char	*dummy_dst;
	size_t			src_len;

	src_len = ft_strlen(src);
	dummy_src = (unsigned char *)src;
	dummy_dst = (unsigned char *)dst;
	if (dstsize == 0)
		return (src_len);
	if (src_len < dstsize - 1)
		ft_nlen_cpy(dummy_src, dummy_dst, src_len);
	else
		ft_nlen_cpy(dummy_src, dummy_dst, dstsize - 1);
	return (src_len);
}
```

### strlcat
strlcat() appends string src to the end of dst.  It will append at most dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless dstsize is 0 or the original dst string was longer than dstsize (in practice this should not happen as it means that either dstsize is incorrect or that dst is not a proper string). If the src and dst strings overlap, the behavior is undefined.
```c
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	if (len_src + len_dst < dstsize)
	{
		ft_memcpy(dst + len_dst, src, len_src);
		dst[len_dst + len_src] = '\0';
		return (len_dst + len_src);
	}
	ft_memcpy(dst + len_dst, src, dstsize - len_dst - 1);
	dst[dstsize - 1] = '\0';
	return (len_dst + len_src);
}
```

## need to free() after use
Need to free 'return value' after use.

### substr
```c
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*arr;
	size_t			len_s;

	len_s = ft_strlen(s);
	if (start >= len_s || s == NULL || len_s == 0)
		return (ft_strdup(""));
	if (len_s - start < len)
		len = len_s - start;
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, s + start, len + 1);
	return (arr);
}
```
### strjoin
```c
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, s1, len_s1 + 1);
	ft_strlcat(arr, s2, len_s1 + len_s2 + 1);
	return (arr);
}
```
### itoa
Convert int to string 
**itoa extension** : same as itoa but takes an 'unsigned long long' type as an argument. 
```c
static int	ft_numlen(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n / 10 >= 1)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_putnum(char *arr, int n, int len)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		arr[0] = '-';
		n *= -1;
	}
	while (n / 10 >= 1)
	{
		arr[len - 1 - i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	arr[len - 1 - i] = n + '0';
	return (arr);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_numlen(n);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	arr = ft_putnum(arr, n, len);
	arr[len] = '\0';
	return (arr);
}
```

### new string
```c
char *ft_new_string(size_t strlen)
{
	char	*new_string;
	
	new_string = (char *)malloc(sizeof(char) * (strlen));
	if (!new_string)
		return (NULL);
	return (new_string);
}
```

### strdup : new string with value
```c
char	*ft_strdup(const char *s1)
{
	char	*arr;
	size_t	arr_size;

	arr_size = ft_strlen(s1) + 1;
	arr = (void *)malloc(sizeof(char) * (arr_size));
	if (!arr)
		return (NULL);
	ft_memmove(arr, s1, arr_size);
	return (arr);
}
```
