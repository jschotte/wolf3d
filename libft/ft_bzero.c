/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:25:31 by jschotte          #+#    #+#             */
/*   Updated: 2015/11/30 16:07:24 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t len)
{
	size_t count;

	count = 0;
	while (count < len)
	{
		((char*)s)[count] = 0;
		count++;
	}
}
