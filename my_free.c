/*
** my_free.c for C in /home/delaco_c/rendu/PSU_2015_malloc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Thu Jan 28 14:51:33 2016 Delacour Benjamin
** Last update Wed Feb 10 16:45:58 2016 Delacour Benjamin
*/

#include "my_malloc.h"

static enum bool	is_empty(t_list *list)
{
  while (list)
    {
      if (list->used == TRUE)
	return (FALSE);
      list = list->next;
    }
  return (TRUE);
}

static enum bool	move_brk(void *end)
{
  int			number;

  if (end == g_alloc_list)
    {
      if (brk(end) == -1)
	return (FALSE);
      return (TRUE);
    }
  number = (sbrk(0) - (void *)g_alloc_list) / getpagesize()
    - ((end - (void *)g_alloc_list) / getpagesize() + 1);
  if (brk(sbrk(0) - getpagesize() * number) == -1)
    return (FALSE);
  return (TRUE);
}

static void	back_brk(t_list *elem)
{
  t_list	*buf;
  t_list	*prev;

  buf = g_alloc_list;
  while (buf->next_free && buf->next_free < elem)
    buf = buf->next_free;
  buf->next_free = NULL;
  prev = elem->prev;
  if (prev)
    prev->next = NULL;
  if (move_brk(elem) == FALSE)
    return ;
  if (elem == g_alloc_list)
    {
      g_alloc_list = NULL;
      g_alloc_list_end = NULL;
      return ;
    }
  if (sbrk(0) - (void *)(prev + 1) - GETMULT(prev->alloc) >= sizeof(t_list))
    divide_elem(prev, prev->alloc);
  else
    {
      prev->next_free = NULL;
      g_alloc_list_end = prev;
    }
}

void		free_intern(void *ptr)
{
  t_list	*elem;
  t_list	*buf;

  if (!ptr || !(elem = get_elem(ptr)))
    return ;
  memset(ptr, 0, elem->alloc);
  elem->used = FALSE;
  buf = g_alloc_list;
  while (buf->next_free && buf->next_free < elem)
    buf = buf->next_free;
  elem->next_free = buf->next_free;
  buf->next_free = elem;
  while (elem->prev && elem->prev->used == FALSE)
    elem = elem->prev;
  if (sbrk(0) - getpagesize() >= (void *)elem &&
      is_empty(elem))
    back_brk(elem);
  else
    merge_empty(elem);
}

void		free(void *ptr)
{
  if (lock_mutex() == FALSE)
    return ;
  free_intern(ptr);
  unlock_mutex();
}
