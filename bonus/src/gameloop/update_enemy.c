/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrogiste <vrogiste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:57:03 by vrogiste          #+#    #+#             */
/*   Updated: 2022/09/28 18:55:42 by vrogiste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void update_enemy_pos(t_game *g, t_enemy *enemy)
{
	t_vector	v;
	t_vector	dir;
	t_vector	np;

	v = vector(g->player.pos.x - enemy->s.x, g->player.pos.y - enemy->s.y);
	dir = vector_normalize(v);
	if (vector_norme(v) > 3)
	{
		enemy->state = WALK;
		np = vector(enemy->s.x + dir.x * (MOVE_SPEED * 3), enemy->s.y + dir.y * (MOVE_SPEED * 3));
		if (!g->map.data[(int)enemy->s.y * g->map.width + (int)np.x])
			enemy->s.x = np.x;
		if (!g->map.data[(int)np.y * g->map.width + (int)enemy->s.x])
			enemy->s.y = np.y;
		g->map.object_map[(int)((enemy->s.y)
				* g->map.width + enemy->s.x)] = 2;	
	}
	else
		enemy->state = SHOOT;
}

static int start(t_enemy *enemy)
{
	if (enemy->state == WALK)
		return (WALK_START);
	else if (enemy->state == SHOOT)
		return (SHOOT_START);
	else
		return (DIE_START);
}

static int end(t_enemy *enemy)
{
	if (enemy->state == WALK)
		return (WALK_END);
	else if (enemy->state == SHOOT)
		return (SHOOT_END);
	else
		return (DIE_END);
}

void	update_enemy(t_game *g)
{
	static int	accu;
	int			i;
	t_enemy *enemy;

	if (!(accu % 10))
	{
		i = 0;
		while (i < ENEMY_MAX)
		{
			if (g->list_enemy[i])
			{
				enemy = g->list_enemy[i];
				update_enemy_pos(g, enemy);
				enemy->s.image += 1;
				if (enemy->s.image > end(enemy))
					enemy->s.image = start(enemy);
				if (enemy->s.image > 7) {
					printf("fdsaojfilokdsahfikldsalhfdsahgfshdkfjusidaof\n");
				}
			}
			i++;
		}
	}
	accu++;
}
