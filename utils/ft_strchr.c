
char	*ft_strchr(const char *str, int c)
{
	unsigned char	uns_c;

	uns_c = (unsigned char)c;
	if (uns_c == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (*str != '\0')
	{
		if (*str == uns_c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

int	ft_strchr_n(const char *s, int c)
{
	unsigned char	uns_c;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	uns_c = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == uns_c)
			return (i);
		i++;
	}
	if (uns_c == '\0')
		return (i);
	return (-1);
}
