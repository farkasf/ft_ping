/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:52:46 by ffarkas           #+#    #+#             */
/*   Updated: 2023/08/24 14:36:03 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_list
{
	int				num;
	int				id;
	int				signal;
	struct s_list	*next;
}	t_list;

long			ft_atoi_long(char *str);
int				ft_atoi(const char *ptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t n, size_t size);
void			ft_free_tab(char **tab);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(int number);
int				ft_lstsize(t_list *lst);
void			*ft_memchr(const void *buf, int ch, size_t length);
int				ft_memcmp(const void *s1, const void *s2, size_t length);
void			*ft_memcpy(void *dst, const void *src, size_t length);
void			*ft_memmove(void *dst, const void *src, size_t length);
void			*ft_memset(void *dst, int c, size_t length);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *src);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin_gnl(char *s1, char *s2);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_get_next_line(int fd);
void			ft_putptr(unsigned long long int ptr);
void			ft_puthex(unsigned int num, char format);
char			*ft_uitoa(unsigned int num);
int				ft_printf(const char *str, ...);
int				ft_get_param(va_list *args, char format);
int				ft_print_c(va_list *args);
int				ft_print_s(va_list *args);
int				ft_print_percent(void);
int				ft_numlen(unsigned int num);
int				ft_print_di(va_list *args);
int				ft_hexlen(unsigned int num);
int				ft_print_x(va_list *args, char format);
int				ft_print_u(va_list *args);
int				ft_ptrlen(unsigned long long ptr);
int				ft_print_p(va_list *args);

#endif
