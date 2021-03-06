/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprotsen <sprotsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:00:02 by sprotsen          #+#    #+#             */
/*   Updated: 2018/08/14 21:47:23 by sprotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head_ssl.h"

void	part1(t_info *info, const char *str, const char *filename)
{
	if ((info->flags & 32) == 32)
	{
		ft_printf("%.8x%.8x%.8x%.8x %s\n", rev_bit(info->a), rev_bit(info->b),
			rev_bit(info->c), rev_bit(info->d), filename);
		info->flags = info->flags & ~32;
	}
	else
		ft_printf("%.8x%.8x%.8x%.8x \"%s\"\n", rev_bit(info->a),
			rev_bit(info->b), rev_bit(info->c), rev_bit(info->d), str);
}

void	part2(t_info *info, const char *str, const char *filename)
{
	if ((info->flags & 32) == 32)
	{
		ft_printf("MD5 (%s) = %.8x%.8x%.8x%.8x\n", filename,
			rev_bit(info->a), rev_bit(info->b),
			rev_bit(info->c), rev_bit(info->d));
		info->flags &= ~32;
	}
	else
		ft_printf("MD5 (\"%s\") = %.8x%.8x%.8x%.8x\n", str,
			rev_bit(info->a), rev_bit(info->b),
			rev_bit(info->c), rev_bit(info->d));
}

void	print_result(t_info *info, const char *str, const char *filename)
{
	int		flag;

	flag = info->flags;
	if (ft_strcmp(str, "") == 0)
		info->flags = info->flags | 2;
	if ((info->flags & 4) == 4)
	{
		ft_printf("%.8x%.8x%.8x%.8x\n", rev_bit(info->a), rev_bit(info->b),
			rev_bit(info->c), rev_bit(info->d));
		info->flags &= ~4;
	}
	else if ((info->flags & 2) == 2)
	{
		ft_printf("%.8x%.8x%.8x%.8x\n", rev_bit(info->a), rev_bit(info->b),
			rev_bit(info->c), rev_bit(info->d));
		info->flags &= ~8;
	}
	else if ((info->flags & 1) == 1)
		part1(info, str, filename);
	else
	{
		part2(info, str, filename);
	}
	if (ft_strcmp(str, "") == 0 && (flag & 2) == 0)
		info->flags &= ~2;
}
