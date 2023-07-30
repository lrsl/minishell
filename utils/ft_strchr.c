
char	*ft_strchr(const char *str, int c)
{
	unsigned char	c_unsigned;

	c_unsigned = (unsigned char)c;
	if (c_unsigned == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (*str != '\0')
	{
		if (*str == c_unsigned)
			return ((char *)str);
		str++;
	}
	return (NULL);
}