/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobounya <mobounya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:35:53 by mobounya          #+#    #+#             */
/*   Updated: 2020/01/14 21:36:15 by mobounya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../Libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/xattr.h>

# define ARG_MAX 262144

int						g_errno;

typedef struct			s_argument
{
	char				**tokens;
	char				**env;
}						t_argument;

typedef int				t_builtin_function();

typedef struct			s_builtin_matcher
{
	char				*name;
	t_builtin_function	*function;
}						t_builtin_matcher;

/*
** Helpers
*/

int						ft_count_args(char *cmd);
char					**ft_tokenize(char *cmd, char **env);
char					*ft_search_vr(char **env, char *vr);
int						ft_count_args(char *cmd);
char					*ft_search_vr(char **env, char *var);
char					*joinfree(const char *a, const char *b, int flag);
void					ft_replace_home(char **str, char **env);
int						ft_compare_env(char *env, char *var);
int						ft_replace_env(t_argument *arguments);
t_argument				*ft_init_env(void);
int						ft_env(t_argument *arguments);
void					ft_not_found(char *command);
void					ft_errors(char *prefix);
void					ft_free_double(void **ptr);
void					ft_split_args(char **tokens, const char *command);

/*
** builtins
*/

int						ft_exit(t_argument	*arguments);
int						ft_echo(t_argument	*arguments);
int						ft_changedir(t_argument	*arguments);
int						ft_setenv(t_argument *arguments);
int						ft_env(t_argument	*arguments);
int						ft_unsetenv(t_argument	*arguments);

#endif
