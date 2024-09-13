/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:19:41 by mvigara           #+#    #+#             */
/*   Updated: 2024/05/20 22:14:42 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>  //INT_MIN
# include <stdarg.h>  //va_list
# include <stdbool.h> //bool
# include <stddef.h>  // size_t
# include <stdint.h>  // INT_MAX
# include <stdlib.h>  // malloc, free
# include <unistd.h>  // write

# ifndef OPEN_MAX
#  define OPEN_MAX 1096
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_all
{
	char			*prv[OPEN_MAX];
	char			*buf;
	ssize_t			bread;
	int				i;
	int				j;
	int				len;
}					t_all;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_format
{
	char			c;
	int				(*f)(va_list);
}					t_format;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strmcmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(const char *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putunbr_fd(unsigned int n, int fd);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strrchr(const char *s, int c);
int					printf_char(va_list val);
int					printf_str(va_list val);
int					printf_percent(va_list val __attribute__((unused)));
int					printf_number(va_list val);
int					printf_u(va_list val);
int					printf_pointer(va_list val);
int					printf_upperhex(va_list val);
int					printf_hex(va_list val);
int					ft_printf(const char *format, ...);
char				*ft_strnchr(const char *s, int c, size_t max);
char				*get_next_line(int fd);
int					ft_iswhitespace(char c);
long long			ft_atoll(const char *str);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strtok(char *str, const char *delim);
bool				ft_isodd(int n);
int					ft_abs(int num);

#endif