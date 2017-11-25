/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:04:12 by rcarette          #+#    #+#             */
/*   Updated: 2017/11/25 17:43:28 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void	*new_allocate(size_t size)
{
	void	*ptr;

	//printf("Size: %ld\n", size);
	ptr = mmap(NULL, size - 1, PROT_READ | PROT_WRITE, \
												MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

void	init_malloc()
{
	//printf("INIT_MALLOC\n");
	g_mem.pge_tiny = NULL;
	g_mem.pge_small = NULL;
	g_mem.pge_data = NULL;
	g_mem.tiny = NULL;
	g_mem.small = NULL;
	g_mem.large = NULL;
	g_mem.number_data = 0x0;
}

t_meta	*creat_block(size_t size, int type)
{
	t_meta	*new_blk;

	/*ALLOCATION DES PAGE TINY && SMALL [ START ]*/
	if (type == TINY && (!g_mem.pge_tiny \
								|| g_mem.octets_tiny + size > TINY_MAX_PAGE))
	{
		g_mem.pge_tiny = new_allocate(TINY_MAX_PAGE);
		g_mem.octets_tiny = 0x0;
	}
	else if (type == SMALL && (!g_mem.pge_small \
								|| g_mem.octets_small + size > SMALL_MAX_PAGE))
	{
		g_mem.pge_small = new_allocate(TINY_MAX_PAGE);
		g_mem.octets_small = 0x0;
	}
	/* ALLOCATION DES PAGE TINY && SMALL [ END ] */

	if (!g_mem.pge_data || g_mem.number_data + sizeof(t_meta) > PAGE_META)
	{
		printf("\n\n\n ****%d****\n\n", g_mem.number_data);
		printf("\n\n****Passage***\n\n");
		sleep(15);
		g_mem.pge_data = new_allocate(PAGE_META);
		g_mem.number_data = 0x0;
	}
	new_blk = (!g_mem.number_data) ? g_mem.pge_data : g_mem.pge_data + 1;
	g_mem.number_data += sizeof(t_meta) ;
	new_blk->next = NULL;
	new_blk->prev = NULL;
	new_blk->size = size;
	new_blk->address = (type == TINY) ? g_mem.pge_tiny : g_mem.pge_small;
	if (type == TINY)
		g_mem.pge_tiny = g_mem.pge_tiny + size + 1 ;
	else
		g_mem.pge_small = g_mem.pge_small + size + 1 ;
	printf(" ----%p\n", g_mem.pge_tiny);
	return (new_blk);
}

void	*manage_malloc(size_t size, int type)
{
	t_meta		*tmp;

	creat_block(size, type);

	return (NULL);
}


void	*malloc(size_t size)
{
	static int start_malloc = 0;

	(start_malloc++ == 0) ? init_malloc() : 0;
	if (!size)
		return (NULL);
	else if (IS_TINY(size))
		return (manage_malloc(size, TINY));
	else if (IS_SMALL(size))
		return (manage_malloc(size, SMALL));
	else
	{
		printf("LARGE\n");
	}

	return (NULL);
}

int main(int argc, const char *argv[])
{
	int i = 0;

	/*printf("%ld\n", sizeof(t_meta));
	
	char *ptr = new_allocate(PAGE_META);
	while (1)
	{
		printf("%d -- %c  - %p\n", i, ptr[i], &ptr[i]);
	}*/
	while(i < 400)
	{
		printf("%d -- %d\n", i, g_mem.number_data);
		malloc(4);
		i++;
		if (i > 370)
			sleep(1);
	}
	return 0;
}
