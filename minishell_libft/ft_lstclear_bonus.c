/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:18:21 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:32:15 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst == NULL || *lst == NULL || del == NULL )
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
/*void delete_element(void *content)
{
    // Customize this function based on the type of data you are storing
    free(content);
}

int main(void)
{
    // Create a linked list with three nodes
    t_list *list = NULL;

    // Add the first node
    list = (t_list*)malloc(sizeof(t_list));
    list->content = malloc(sizeof(int));
    *(int*)list->content = 42;
    list->next = NULL;

    // Add the second node
    ft_lstadd_back(&list, (t_list*)malloc(sizeof(t_list)));
    list->next->content = malloc(sizeof(int));
    *(int*)list->next->content = 24;
    list->next->next = NULL;

    // Add the third node
    ft_lstadd_back(&list, (t_list*)malloc(sizeof(t_list)));
    list->next->next->content = malloc(sizeof(int));
    *(int*)list->next->next->content = 13;
    list->next->next->next = NULL;

    // Print the list
    t_list *current = list;
    while (current != NULL) {
        printf("%d ", *(int*)current->content);
        current = current->next;
    }
    printf("\n");

    // Clear the list 
    ft_lstclear(&list, delete_element);

    return 0;
}*/
