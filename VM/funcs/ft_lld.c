/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabbah <nsabbah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 17:07:21 by nsabbah           #+#    #+#             */
/*   Updated: 2017/03/29 10:50:22 by tlenglin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/vm.h"

/*
**
** Instructions:
** Means long-load. Same as ld, but without % IDX_MOD.
** No % IDX_MOD
** Modify the carry
**
*/

void	ft_lld(t_env *e, t_cursor *cursor)
{
	char		acb;
	int			value;
	int			opc_ind;
	short int	ind_value;

	opc_ind = cursor->index;
	acb = e->a[MODA(opc_ind + 1)].hex;
	if (((acb & 0xFF) >> 6) == DIR_CODE)
	{
		value = ft_cp_int(MODA(opc_ind + 2), *e);
		if (e->a[MODA(opc_ind + 2 + 4)].hex >= 1 && e->a[MODA(opc_ind + 2 + 4)].hex <= REG_NUMBER)
		{
			cursor->reg[e->a[MODA(opc_ind + 2 + 4)].hex] = value;
			if (value == 0)
				cursor->carry = 1;
			else
				cursor->carry = 0;
		}
		ft_update_cursor(e, cursor, 7);
	}
	else
	{
		ind_value = ((e->a[MODA(opc_ind + 2)].hex & 0xFF) << 8)
									+ (e->a[MODA(opc_ind + 3)].hex & 0xFF);
		ind_value = ind_value & 0xFFFF;
		value = ft_cp_int(MODA(opc_ind + ind_value), *e);
		if (e->a[MODA(opc_ind + 2 + 2)].hex >= 1 && e->a[MODA(opc_ind + 2 + 2)].hex <= REG_NUMBER)
		{
			cursor->reg[e->a[MODA(opc_ind + 2 + 2)].hex] = value;
			if (value == 0)
				cursor->carry = 1;
			else
				cursor->carry = 0;
		}
		ft_update_cursor(e, cursor, 5);
	}
	cursor->carry = 1;
}
