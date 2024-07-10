/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:16:32 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 10:29:23 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst != NULL)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}
/*int main() {
    // Creating a linked list for testing
    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");

    // Connecting the nodes
    node1->next = node2;
    node2->next = node3;
    
    // Finding the last node
    t_list *lastNode = ft_lstlast(node1);

    // Printing the content of the last node
    if (lastNode) {
        printf("The content of the last node is: %s\n", //
		// (char *)lastNode->content);
    } else {
        printf("The list is empty.\n");
    }


    return 0;
}*/