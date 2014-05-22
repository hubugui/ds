/*
 * kmp.c
 *
 * 0.1			hubugui	2011-05-17	create.
 */

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void kmp_print(const char *prefix, int lenp, int *next)
{
	int i;

	printf("%s", prefix);
	for (i = 0; i < lenp; i++)
	{
		printf("%d ", next[i]);
	}
	printf("\n");
}

static void kmp_next(const char *p, int *next)
{
	int i, j;

	next[0] = j = -1;
	for (i = 1; p[i] != '\0'; i++)
	{
		j = next[i - 1];
		while (j > -1 && p[i - 1] != p[j])
			j = next[j];

		if (j > -1)
			next[i] = j + 1;
		else
			next[i] = 0;
	}
}

static void kmp_next1(const char *p, int *next)
{
	int i, j;

	next[0] = j = -1;
	for (i = 1; p[i] != '\0'; i++)
	{
		while (j > -1 && p[i - 1] != p[j])
			j = next[j];

		if (j > -1)
			next[i] = ++j;
		else
			next[i] = j = 0;
	}
}

static void kmp_next2(const char *p, int *next)
{
	int i, j;

	next[0] = j = -1;
	while (p[i] != '\0')
	{
		if (p[i - 1] == p[next[i - 1]])
		{
			next[i] = next[i - 1] + 1;
			i++;
		}
		else
			j = next[i - 1];
	}
}

int kmp(const char *s, const char *p, int *next)
{
	int i, j;

	i = j = 0;
	while (s[i] != '\0' && p[j] != '\0')
	{
		if (s[i] == p[j])
		{
			i++;
			j++;
		}
		else if (j == 0)
			i++;
		else
			j = next[j];
	}

	return p[j] == '\0' ? i - j : -1;
}

void test(int argc, char **argv)
{
	int index;
	int *next;
	int lenp = strlen(argv[2]);

	printf("s:\t%s\n", argv[1]);
	printf("p:\t%s\n", argv[2]);

	next = malloc(lenp * 4);
	if (next)
	{
		kmp_next1(argv[2], next);
		kmp_print("next:\t", lenp, next);

		index = kmp(argv[1], argv[2], next);
		printf("index:\t%d\n", index);

		free(next);
	}
}

int main(int argc, char **argv)
{
	clock_t t1, t2;

	t1 = clock() / (CLOCKS_PER_SEC / 1000);
	test(argc, argv);
	t2 = clock() / (CLOCKS_PER_SEC / 1000);

	printf("consuming %d ms.\r\n", (int) (t2 - t1));

	return 0;
}
