/*
** my_mutex.c for C in /home/delaco_c/rendu/PSU_2015_malloc
** 
** Made by Benjamin Delacour
** Login   <delaco_c@epitech.net>
** 
** Started on  Mon Feb  8 02:50:20 2016 Benjamin Delacour
** Last update Mon Feb  8 02:50:50 2016 Benjamin Delacour
*/

#include "my_malloc.h"

enum bool	lock_mutex()
{
  if (g_mutex == NULL)
    {
      if ((g_mutex = malloc_intern(sizeof(pthread_mutex_t))) == NULL)
      	return (FALSE);
      if (pthread_mutex_init(g_mutex, NULL))
      	return (FALSE);
    }
  if (pthread_mutex_lock(g_mutex))
    return (FALSE);
  return (TRUE);
}

enum bool	unlock_mutex()
{
  if (pthread_mutex_unlock(g_mutex))
    return (FALSE);
  return (TRUE);
}
