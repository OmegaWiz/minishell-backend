/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 08:39:51 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/30 08:43:00 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

char	**lst2arr(t_list *lst)
{
	char	**arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!arr)
		return (NULL);
	while (lst)
	{
		arr[i] = ft_strdup((char *) lst->content);
		if (!arr[i])
			return (ft_arrclear(arr));
		lst = lst->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_arrclear(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}
