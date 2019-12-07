#include "../Libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/xattr.h>

#define TRUE (int8_t)1
#define FALSE (int8_t)0
#define ARG_MAX 262144
typedef int8_t	t_BOOL;

typedef struct	s_argument
{
	char	**tokens;
	char	**env;
}			t_argument;

typedef int t_builtin_function();

typedef struct	s_builtin_matcher
{
	char				*name;
	t_builtin_function	*function;
}				t_builtin_matcher;

char	**ft_tokenize(char *cmd, char **env);
char	*ft_search_vr(char **env, char *vr);