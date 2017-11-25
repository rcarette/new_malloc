/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:00:12 by rcarette          #+#    #+#             */
/*   Updated: 2017/11/25 15:27:45 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>


# define TINY_PAGE 8
# define TINY_MAX_PAGE (TINY_PAGE * getpagesize())
# define TINY 128


# define SMALL_PAGE 32
# define SMALL_MAX_PAGE (SMALL_PAGE * getpagesize())
# define SMALL 512

# define PAGE 3
# define PAGE_META (PAGE * getpagesize())

# define IS_TINY(x) (x <= TINY)
# define IS_SMALL(x) (x > TINY && x <= SMALL)


typedef struct		s_meta
{
	size_t			size; /* SIZE OCTETS BLOCK */
	void			*address; /* ADRESS DU BLOCK */
	struct s_meta	*next; /* POINTOR SUR LE BLOCK NEXT */
	struct s_meta	*prev; /* POINTOR SUR LE BLOCK PREV */
}					t_meta;


typedef struct		s_mem
{
	void			*pge_tiny;
	void			*pge_small;
	void			*pge_data;
	t_meta			*tiny;
	t_meta			*small;
	t_meta			*large;
	int				number_data;
	int				octets_tiny;
	int				octets_small;

}					t_mem;

t_mem				g_mem;


void				*new_alloc(size_t size);
void				*calloc(size_t count, size_t size);
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*reallocf(void *ptr, size_t size);
void				*valloc(size_t size);

#endif
