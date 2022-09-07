/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:16:55 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/07 13:54:10 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_pos(t_game *g, t_vector *pos, t_vector *np)
{
	if ((!g->map.data[(int)pos->y * g->map.width + (int)np->x]
			&& !g->map.object_map[(int)pos->y * g->map.width + (int)np->x])
		|| can_pass_door((int)pos->y * g->map.width + (int)np->x, g))
		pos->x = np->x;
	if ((!g->map.data[(int)np->y * g->map.width + (int)pos->x]
			&& !g->map.object_map[(int)np->y * g->map.width + (int)pos->x])
		|| can_pass_door((int)np->y * g->map.width + (int)pos->x, g))
		pos->y = np->y;
}

static void	translate_rl(t_game *g, t_vector *pos, t_vector *dir)
{
	t_vector	np;

	if (g->state.right)
	{
		np = vector(pos->x + dir->y * MOVE_SPEED, pos->y - dir->x * MOVE_SPEED);
		update_pos(g, pos, &np);
	}
	if (g->state.left)
	{
		np = vector(pos->x - dir->y * MOVE_SPEED, pos->y + dir->x * MOVE_SPEED);
		update_pos(g, pos, &np);
	}
}

void	translate_cam(t_game *g)
{
	t_vector	*pos;
	t_vector	dir;
	t_vector	np;

	pos = &g->player.pos;
	dir = g->player.dir;
	if (g->state.up)
	{
		np = vector(pos->x + dir.x * MOVE_SPEED, pos->y + dir.y * MOVE_SPEED);
		update_pos(g, pos, &np);
	}
	if (g->state.down)
	{
		np = vector(pos->x - dir.x * MOVE_SPEED, pos->y - dir.y * MOVE_SPEED);
		update_pos(g, pos, &np);
	}
	translate_rl(g, pos, &dir);
}

void	rotate_cam(t_game *g)
{
	if (g->state.r_left)
	{
		g->player.dir = vector_rotate(g->player.dir, ROT_SPEED);
		g->player.plane = vector_rotate(g->player.plane, ROT_SPEED);
	}
	if (g->state.r_right)
	{
		g->player.dir = vector_rotate(g->player.dir, -ROT_SPEED);
		g->player.plane = vector_rotate(g->player.plane, -ROT_SPEED);
	}
	if (g->state.m_left)
	{
		g->player.dir = vector_rotate(g->player.dir, g->state.m_left * MRS);
		g->player.plane = vector_rotate(g->player.plane, g->state.m_left * MRS);
		g->state.m_left = 0;
	}
	if (g->state.m_right)
	{
		g->player.dir = vector_rotate(g->player.dir, -g->state.m_right * MRS);
		g->player.plane = vector_rotate(g->player.plane,
				-g->state.m_right * MRS);
		g->state.m_right = 0;
	}
}
