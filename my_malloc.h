/*
** my_malloc.h for C in /home/delaco_c/rendu/PSU_2015_malloc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Wed Jan 27 15:36:43 2016 Delacour Benjamin
** Last update Sun Feb 14 20:24:51 2016 Delacour Benjamin
*/

#ifndef MYMALLOC_H_
# define MYMALLOC_H_

# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# define GETMULT(x) (x + 8 * (x % 8 != 0) - x % 8)

enum	bool
{
  TRUE = 1,
  FALSE = 0
};

typedef struct	s_list
{
  enum bool	used;
  size_t	alloc;
  struct s_list	*next;
  struct s_list	*next_free;
  struct s_list	*prev;
}		t_list;

t_list		*g_alloc_list;
t_list		*g_alloc_list_end;
pthread_mutex_t	*g_mutex;

void		*malloc_intern(size_t);
void		*malloc(size_t);
void		*realloc(void *, size_t);
void		*calloc(size_t, size_t);
void		free(void *);
void		free_intern(void *);
void		show_alloc_mem();
t_list		*get_elem(void *);
size_t		my_elem_size(t_list *);
void		merge_empty(t_list *);
t_list		*divide_elem(t_list *, size_t);
enum bool	lock_mutex();
enum bool	unlock_mutex();
t_list		*best_fit(size_t);

#endif /* !MYMALLOC_H_ */
