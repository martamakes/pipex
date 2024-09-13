/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:49:20 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 11:15:39 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the last element of the list
** @param {t_list*} lst The beginning of the list
** @return {t_list*} The last element of the list, or NULL if the list is empty
*/
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*aux;

	aux = lst;
	if (aux == NULL)
		return (NULL);
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}
