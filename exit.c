#include "shell.h"

/**
 **_strncpy - copies string
 *@dest: destination string
 *@src: source
 *@n: number of char
 *Return: s
 */
char *_strncpy(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (s);
}

/**
 * _strncat - joins two strings
 * @dest: destination string
 *@src: source
 *@n: size of byte
 *Return: s
 */
char *_strncat(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;

	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
		dest[x] = '\0';
	return (s);
}
/**
 **_strchr - finds for char in a string
 *@s: string to parse
 *@c: char
 *Return: (s)
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
