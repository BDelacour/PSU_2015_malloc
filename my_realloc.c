/*
** my_realloc.c for C in /home/delaco_c/rendu/PSU_2015_malloc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Wed Jan 27 15:42:46 2016 Delacour Benjamin
** Last update Mon Feb  8 02:53:21 2016 Benjamin Delacour
*/

#include "my_malloc.h"

static void	merge_next(t_list *elem, size_t size)
{
  elem->next = elem->next->next;
  elem->next->prev = elem;
  if ((void *)elem->next - (void *)(elem + 1) - GETMULT(size)
      >= sizeof(t_list))
    divide_elem(elem, size);
}

static enum bool	merge_elem(t_list *elem, size_t size)
{
  t_list		*buf;

  elem->alloc = size;
  buf = g_alloc_list;
  while (buf->next_free && buf->next_free < elem->next)
    buf = buf->next_free;
  buf->next_free = elem->next->next_free;
  elem->next->next_free = NULL;
  if (elem->next->next)
    merge_next(elem, size);
  else
    {
      elem->next = NULL;
      if (sbrk(0) - getpagesize() >= (void *)(elem + 1) + GETMULT(size))
      	if (brk(sbrk(0) - getpagesize()) == -1)
	    return (FALSE);
      if (sbrk(0) - (void *)(elem + 1) - GETMULT(elem->alloc)
	  >= sizeof(t_list))
	elem->next = divide_elem(elem, size);
    }
  return (TRUE);
}

static void	*realloc_intern(void *ptr, size_t size)
{
  t_list	*elem;

  if (!(elem = get_elem(ptr)))
    return (NULL);
  if (size <= my_elem_size(elem))
    {
      if (my_elem_size(elem) - GETMULT(size) >= sizeof(t_list))
	divide_elem(elem, size);
      elem->alloc = size;
    }
  else if (elem->next && elem->next->used == FALSE &&
	   ((elem->next->next && (size_t)elem->next->next
	     - (size_t)(elem + 1) >= GETMULT(size)) ||
	    (elem->next->next == NULL && (size_t)sbrk(0) - (size_t)(elem + 1)
	     >= GETMULT(size))))
    merge_elem(elem, size);
  else
    {
      if ((ptr = malloc_intern(size)) == NULL)
	return (NULL);
      memcpy(ptr, elem + 1, elem->alloc);
      free_intern(elem + 1);
    }
  return (ptr);
}

void		*realloc(void *ptr, size_t size)
{
  if (ptr < (void *)g_alloc_list || ptr > sbrk(0))
    return (malloc(size));
  if (lock_mutex() == FALSE)
    return (NULL);
  ptr = realloc_intern(ptr, size);
  if (unlock_mutex() == FALSE)
    return (NULL);
  return (ptr);
}
