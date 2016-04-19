/*
** my_malloc.c for C in /home/berny_m/rendu/PSU_2015_malloc
** 
** Made by Berny Matias
** Login   <berny_m@epitech.net>
** 
** Started on  Wed Jan 27 15:36:43 2016 Berny Matias
** Last update Wed Feb 10 16:51:16 2016 Delacour Benjamin
*/

#include "my_malloc.h"

static void		init_new_elem(t_list *new_elem, size_t size)
{
  new_elem->used = TRUE;
  new_elem->alloc = size;
  new_elem->next = NULL;
  new_elem->prev = g_alloc_list_end;
  new_elem->next_free = NULL;
  if (g_alloc_list == NULL)
    g_alloc_list = new_elem;
  else
    g_alloc_list_end->next = new_elem;
  g_alloc_list_end = new_elem;
}

static t_list		*alloc_new(size_t size)
{
  t_list		*new_elem;

  if (g_alloc_list == NULL || g_alloc_list_end->used == TRUE)
    {
      if ((new_elem = sbrk((getpagesize()
			    * ((GETMULT(size) + sizeof(t_list))
			       / getpagesize() + 1)))) == (void *)-1)
	return (NULL);
      init_new_elem(new_elem, size);
      if (sbrk(0) - (void *)(new_elem + 1) - GETMULT(size) > sizeof(t_list))
        divide_elem(new_elem, size);
      return (new_elem);
    }
  if ((new_elem = sbrk((getpagesize() * ((GETMULT(size)
					  - g_alloc_list_end->alloc)
					 / getpagesize() + 1)))) == (void *)-1)
    return (NULL);
  g_alloc_list_end->alloc = my_elem_size(g_alloc_list_end);
  return (g_alloc_list_end);
}

static void		*alloc_at(t_list *list, size_t size)
{
  t_list		*prev;

  prev = g_alloc_list;
  while (prev->next_free && prev->next_free < list)
    prev = prev->next_free;
  if (prev)
    prev->next_free = list->next_free;
  list->used = TRUE;
  list->next_free = NULL;
  list->alloc = size;
  if (my_elem_size(list) - GETMULT(size) >= sizeof(t_list))
    divide_elem(list, size);
  return (list + 1);
}

void			*malloc_intern(size_t size)
{
  t_list		*list;

  list = g_alloc_list;
  if ((list = best_fit(size)) != NULL)
    return (alloc_at(list, size));
  if ((list = alloc_new(size)) == NULL)
    return (NULL);
  if (list->used == TRUE)
    return (list + 1);
  return (alloc_at(list, size));
}

void	*malloc(size_t size)
{
  void	*res;

  if (lock_mutex() == FALSE)
    return (NULL);
  res = malloc_intern(size);
  if (unlock_mutex() == FALSE)
    return (NULL);
  return (res);
}
