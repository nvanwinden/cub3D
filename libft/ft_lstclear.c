/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nvan-win <nvan-win@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 15:15:12 by nvan-win      #+#    #+#                 */
/*   Updated: 2020/05/12 13:36:53 by nvan-win      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*delnode;

	tmp = *lst;
	delnode = *lst;
	if (lst == NULL || del == NULL)
		return ;
	while (tmp != NULL)
	{
		del(tmp->content);
		delnode = tmp;
		tmp = tmp->next;
		free(delnode);
	}
	*lst = NULL;
}
