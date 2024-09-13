/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:43:31 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:04:40 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*Clears and frees the given t_list and all successors of that list,
*using the function del and free(3).
*Finally, the pointer to the list is set to NULL.
*@param lst The address of a pointer to the first link of a list that needs
*to be freed and set to NULL
*@param del The address of the function used to delete the content of a list 
*link
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = aux;
	}
}
