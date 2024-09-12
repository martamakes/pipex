/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:03:54 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 11:19:25 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * The ft_bzero() function writes n zeroed bytes to the string s.
 * It uses ft_memset() to perform the zeroing.
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
