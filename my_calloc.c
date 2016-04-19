/*
** my_calloc.c for C in /home/delaco_c/rendu/PSU_2015_malloc
** 
** Made by Delacour Benjamin
** Login   <delaco_c@epitech.net>
** 
** Started on  Mon Feb  1 13:59:20 2016 Delacour Benjamin
** Last update Mon Feb  8 02:53:50 2016 Benjamin Delacour
*/

#include "my_malloc.h"

void		*calloc(size_t nmemb, size_t size)
{
  void		*res;
  t_list	*res_elem;

  if (lock_mutex() == FALSE)
    return (NULL);
  if ((res = malloc_intern(nmemb * size)) == NULL)
    {
      unlock_mutex();
      return (NULL);
    }
  if ((res_elem = get_elem(res)) == NULL)
    {
      unlock_mutex();
      return (NULL);
    }
  memset(res_elem + 1, 0, res_elem->alloc);
  if (unlock_mutex() == FALSE)
    return (NULL);
  return (res);
}
