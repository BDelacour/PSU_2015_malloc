/*
** my_malloc_tool.c for C in /home/delaco_c/rendu/PSU_2015_malloc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Mon Feb  1 19:03:19 2016 Delacour Benjamin
** Last update Mon Feb  8 02:52:29 2016 Benjamin Delacour
*/

#include "my_malloc.h"

t_list	*get_elem(void *ptr)
{
  if (ptr < sbrk(0) && ptr > (void *)g_alloc_list)
    return (ptr - sizeof(t_list));
  return (NULL);
}

size_t	my_elem_size(t_list *elem)
{
  if (elem->next)
    return ((void *)(elem->next) - (void *)(elem + 1));
  else
    return (sbrk(0) - (void *)(elem + 1));
}

void		merge_empty(t_list *elem)
{
  t_list	*tmp;

  tmp = elem->next;
  while (tmp && tmp->used == FALSE)
    {
      elem->next = tmp->next;
      elem->next_free = tmp->next_free;
      tmp = tmp->next;
    }
  if (tmp)
    tmp->prev = elem;
  elem->alloc = my_elem_size(elem);
  if (!elem->next)
    g_alloc_list_end = elem;
}

t_list		*divide_elem(t_list *elem, size_t size)
{
  t_list	*new;
  t_list	*buf;

  new = (void *)(elem + 1) + GETMULT(size);
  new->next = elem->next;
  new->used = FALSE;
  new->prev = elem;
  elem->next = new;
  new->alloc = my_elem_size(new);
  buf = g_alloc_list;
  while (buf->next_free && buf->next_free < new)
    buf = buf->next_free;
  new->next_free = buf->next_free;
  buf->next_free = new;
  merge_empty(new);
  return (new);
}

t_list		*best_fit(size_t size)
{
  t_list	*save;
  t_list	*elem;

  elem = g_alloc_list;
  if (elem == NULL)
    return (NULL);
  if (elem->used == 1)
    elem = elem->next_free;
  save = NULL;
  while (elem != NULL)
    {
      if (my_elem_size(elem) >= GETMULT(size))
	{
	  if (save == NULL || my_elem_size(save) > my_elem_size(elem))
	    save = elem;
	}
      elem = elem->next_free;
    }
  return (save);
}
