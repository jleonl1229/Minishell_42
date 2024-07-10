/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:42:11 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/29 09:53:24 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}
/*void delete_element(void *content)
{
    // Customize this function based on the type of data you are storing
    free(content);
}

int main(void)
{
    // Create a node
    t_list *node = (t_list*)malloc(sizeof(t_list));
    node->content = malloc(sizeof(int));
    *(int*)node->content = 42;
    node->next = NULL;

    // Print the content before deletion
    printf("Before deletion: %d\n", *(int*)node->content);

    // Delete the node
    ft_lstdelone(node, delete_element);

    // Attempt to print the content after deletion (undefined behavior)
    // The content is freed, so accessing it is invalid
    printf("After deletion: %d\n", *(int*)node->content);

    return 0;
}*/
