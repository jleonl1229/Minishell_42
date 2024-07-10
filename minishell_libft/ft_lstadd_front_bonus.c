/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:11:29 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:32:09 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new -> next = *lst;
	*lst = new;
}

/*int main(void)
{
	t_list *list = NULL;

    ft_lstadd_front(&list, (t_list*)malloc(sizeof(t_list)));
    printf("%p\n", (void *)list);

    ft_lstadd_front(&list, (t_list*)malloc(sizeof(t_list)));
    printf("%p %p\n", (void *)list, (void *)list->next);

    ft_lstadd_front(&list, (t_list*)malloc(sizeof(t_list)));
    printf("%p %p %p\n", (void *)list, (void *)list->next, //
	// (void *)list->next->next);

	printf("\n");
}*/
