/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:44:42 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/29 10:48:10 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (i);
	i++;
	while (lst -> next != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

/*int main(void)
{
    // Creating a linked list for testing
    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");

    // Connecting the nodes
    node1->next = node2;
    node2->next = node3;

    // Getting the size of the linked list
    int size = ft_lstsize(node1);

    // Printing the size
    printf("Size of the linked list: %d\n", size);
}*/
