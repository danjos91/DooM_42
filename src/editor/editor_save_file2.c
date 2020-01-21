/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_file2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:20:51 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/21 21:49:16 by tjuana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static char	*ft_str_vertex(int i)
{
	char	*itoa;
	char	*join;
	char	*tmp;

	itoa = ft_itoa(i);
	join = ft_strjoin("vertex\t", itoa);
	tmp = ft_strdup(join);
	ft_strdel(&itoa);
	ft_strdel(&join);
	join = ft_strjoin(tmp, "\t");
	ft_strdel(&tmp);
	return (join);
}

static char	*ft_space(int k, int j)
{
	char	*itoa;
	char	*join;
	char	*tmp;

	itoa = ft_itoa(j);
	if (!k)
		return (itoa);
	join = ft_strjoin(" ", itoa);
	ft_strdel(&itoa);
	return (join);
}

void	ft_print_to_file(t_wolf3d *w, int f)
{
	char	*sy;
	char	*sx;
	char	*space_or_not;
	int		k;

	sy = ft_str_vertex(w->file.i);
	k = 1;
	if (!f && w->file.count == 0)
	{
		ft_putstr_fd(sy, w->file.fd);
		k = 0;
	}
	else if (!f)
	{
		k = 0;
		ft_putstr_fd("\n", w->file.fd);
		ft_putstr_fd(sy, w->file.fd);
	}
	sx = ft_space(k, w->file.j);
	ft_putstr_fd(sx, w->file.fd);
	ft_strdel(&sx);
	ft_strdel(&sy);
}

static char	*ft_my_join_baby(int height, int floor)
{
	char	*itoa;
	char	*join;
	char	*tmp;

	itoa = ft_itoa(floor);
	join = ft_strjoin("sector\t", itoa);
	tmp = ft_strdup(join);
	ft_strdel(&itoa);
	ft_strdel(&join);
	join = ft_strjoin(tmp, " ");
	ft_strdel(&tmp);
	tmp = ft_strdup(join);
	ft_strdel(&join);
	itoa = ft_itoa(height);
	join = ft_strjoin(tmp, itoa);
	ft_strdel(&itoa);
	ft_strdel(&tmp);
	tmp = ft_strjoin(join, "\t");
	ft_strdel(&join);
	return (tmp);
}

void		ft_print_sectors_to_file(t_wolf3d *w, t_list *list)
{
	char		*str;
	t_sector	*sector;
	t_list		*ptr_list;
	int			j;

	ptr_list = list;
	if (ptr_list == NULL)
		return ;
	ft_print_sectors_to_file(w, ptr_list->next);
	sector = (t_sector*)ptr_list->content;
	str = ft_my_join_baby(sector->height, sector->floor);
	ft_putstr_fd(str, w->file.fd);
	ft_strdel(&str);
	j = -1;
	while (++j < sector->vertex_count)
	{
		str = ft_space(1, sector->vertex[j]->w);
		ft_putstr_fd(str, w->file.fd);
	}
	ft_putstr_fd("    ", w->file.fd);
	ft_save_neighbour(sector, w->file.fd);
	ft_putstr_fd("\n", w->file.fd);
	ft_strdel(&str);
}
