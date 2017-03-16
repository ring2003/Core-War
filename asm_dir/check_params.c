/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlenglin <tlenglin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:58:11 by tlenglin          #+#    #+#             */
/*   Updated: 2017/03/16 19:29:33 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	count_params(char *params, t_op top)
{
	int	i;
	int	comas;

	i = -1;
	comas = 1;
	while (params[++i])
		if (params[i] == SEPARATOR_CHAR)
			comas++;
	if (comas != top.nb_params)
		return (0);
	return (1);
}

int			check_params(char *params, t_op top, t_asm *tasm)
{
	int	i;
	int	p;

	if (!count_params(params, top))
		return (0);
	i = 0;
	p = 0;
	while (params[i] && p < top.nb_params)
	{
		if (params[i] == 'r' && !check_register(params + i, top, p))
			return (0);
		else if (params[i] == DIRECT_CHAR &&
			!check_direct(params + i, top, p, tasm))
			return (0);
		else if (params[i] != DIRECT_CHAR && params[i] != 'r' &&
			!check_indirect(params + i, top, p, tasm))
			return (0);
		if (ft_strchr(params + i, SEPARATOR_CHAR))
			i += ft_strchr(params + i, SEPARATOR_CHAR) - (params + i) + 1;
		else
			i = ft_strlen(params);
		p++;
	}
	return (1);
}
