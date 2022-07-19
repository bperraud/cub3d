/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:33:31 by vrogiste          #+#    #+#             */
/*   Updated: 2022/07/20 00:07:14 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "cub3d.h"

# define K_PRESS_EVENT 2
# define K_RELEASE_EVENT 3
# define DESTROY_NOTIFY_EVENT 17

# define NO_EVENT_MASK 0
# define K_PRESS_MASK 1
# define K_RELEASE_MASK 2

# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2

/*event*/
int	key_down(int code, t_game *game);
int	key_release(int code, t_game *game);

#endif
