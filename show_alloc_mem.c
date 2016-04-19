/*
** show_alloc_mem.c for C in /home/berny_m/rendu/PSU_2015_malloc
** 
** Made by Berny Matias
** Login   <berny_m@epitech.net>
** 
** Started on  Thu Jan 28 11:48:48 2016 Berny Matias
** Last update Sun Feb 14 20:25:39 2016 Delacour Benjamin
*/

#include "my_malloc.h"

void		show_alloc_mem()
{
  t_list	*start;

  start = g_alloc_list;
  while (start != 0)
    {
      if (start->used)
	{
	  printf("%p - %p : %zu bytes\n", start + 1,
		 ((void *)(start + 1) + start->alloc), start->alloc);
	}
      start = start->next;
    }
}
