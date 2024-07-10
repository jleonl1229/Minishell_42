/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:40:50 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/29 10:43:36 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node ->content = content;
	node -> next = NULL;
	return (node);
}

/*int main() {
    // Creating a new node with content "Hello, World!"
    t_list *node = ft_lstnew("Hello, World!");

    // Checking if the node was created successfully
    if (node) {
        // Printing the content of the node
        printf("Content of the node: %s\n", (char *)node->content);

        // Freeing the memory allocated for the node
        free(node);
    } else {
        printf("Failed to create a new node.\n");
    }

    return 0;
}*/
