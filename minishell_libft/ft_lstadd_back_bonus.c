/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:49:07 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:32:03 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlast(*lst);
		temp -> next = new;
	}
}
/*int main(void)
{
    t_list *list = NULL;

    ft_lstadd_back(&list, (t_list*)malloc(sizeof(t_list)));
    printf("%p\n", (void *)list);

    ft_lstadd_back(&list, (t_list*)malloc(sizeof(t_list)));
    printf("%p %p\n", (void *)list, (void *)list->next);

    ft_lstadd_back(&list, (t_list*)malloc(sizeof(t_list)));
    printf("%p %p %p\n", (void *)list, (void *)list->next, //
	//(void *)list->next->next);
    printf("\n");
}*/
