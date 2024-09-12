/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:59:42 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:05:32 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Counts the number of elements in a linked list.
** @param {t_list*} lst The head of the list
** @return {int} The number of elements in the list
*/
int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp;

	count = 0;
	temp = lst;
	if (temp == NULL)
		return (0);
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
