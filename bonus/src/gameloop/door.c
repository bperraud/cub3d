/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:43:00 by vrogiste          #+#    #+#             */
/*   Updated: 2022/10/02 22:14:30 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*get_door(int cell, t_game *g)
{
	t_node	*node;

	node = g->doors.head;
	while (node)
	{
		if (((t_door *)node->content)->cell == cell)
			return (node->content);
		node = node->next;
	}
	return (NULL);
}

bool	can_pass_door(int cell, t_game *g)
{
	t_door	*door;

	door = get_door(cell, g);
	if (door)
		return (door->opened && door->ratio < 0.2);
	return (false);
}
