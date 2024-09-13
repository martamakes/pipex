/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:51:30 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:05:15 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_lstmap() iterates through the given linked list 'lst' and applies
** the function 'f' to each element's content to create a new list
** consisting of the results.
** 'f' is a function that takes a void* and returns a transformed void*.
** 'del' is a function that takes a void* and deletes/frees it when
** necessary if an allocation fails.
** Returns a new list with the transformed content on success,
** or NULL if allocation fails.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newnode;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		temp = f(lst->content);
		newnode = ft_lstnew(temp);
		if (!newnode)
		{
			del(temp);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, newnode);
		lst = lst->next;
	}
	return (newlist);
}
