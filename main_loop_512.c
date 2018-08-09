#include "head_ssl.h"
#define ULLI unsigned long long int








void	prepare_message_schedule_512(t_info *info, ULLI m[], int n)
{
	int 	i;

	i = -1;
	while (++i < 16)
	{
		m[i] = rev_bit_512(info->mass[n - 1][i]);
		// printf("i = %d %08x\n",i, m[i]);
	}
	while (i < 80)
	{
		m[i] = (m[i - 16] + delta0_64(m[i - 15]) + m[i - 7] + delta1_64(m[i - 2]));
		++i;
	}
}

void	initializ_tmp_512(t_512 * tmp, t_512 *start)
{
	tmp->h0 = (start->h0);	//	a
	tmp->h1 = (start->h1);	//	b
	tmp->h2 = (start->h2);	//	c
	tmp->h3 = (start->h3);	//	d
	tmp->h4 = (start->h4);	//	e
	tmp->h5 = (start->h5);	//	f
	tmp->h6 = (start->h6);	//	g
	tmp->h7 = (start->h7);	//	h
	
		// print_debug(start);
	// sleep(32);
}
ULLI internal_loop_part(t_512 *tmp, ULLI m[], t_info *info, int i)
{
	float temp1;

	temp1 = (float)(tmp->h7) + (sigma1_64(tmp->h4));
	temp1 %= 18446744073709551615;
	temp1 += ch_64(tmp->h4, tmp->h5, tmp->h6);
	temp1 %= 18446744073709551615;
	temp1 += m[i];
	temp1 %= 18446744073709551615;
	temp1 += info->k[i];
	temp1 %= 18446744073709551615;
	return (temp1);
}

void	internal_loop_512(t_512 *tmp, ULLI m[], t_info *info)
{
	int 	i;
	ULLI temp1;
	ULLI temp2;
	float temporary;

	i = -1;
	while (++i < 64)
	{
		temp1 = internal_loop_part(tmp, m, info, i);
		temporary = (float)(sigma0(tmp->h0)) + (maj(tmp->h0, tmp->h1, tmp->h2));
		temp2 = (ULLI)(temporary % 18446744073709551615);
		tmp->h7 = 	(tmp->h6);
		tmp->h6 = 	(tmp->h5);
		tmp->h5 = 	(tmp->h4);
		temporary = (float)(tmp->h3) + temp1;
		tmp->h4 = 	(ULLI)(temporary % 18446744073709551615);
		tmp->h3 = 	(tmp->h2);
		tmp->h2 = 	(tmp->h1);
		tmp->h1 = 	(tmp->h0);
		temporary = ((float)temp1 + temp2);
		tmp->h0 = (ULLI)(temporary % 18446744073709551615);
	}
}

void	intermediate_512(t_512 * tmp, t_512 *start)
{
	start->h0 += tmp->h0;
	start->h1 += tmp->h1;
	start->h2 += tmp->h2;
	start->h3 += tmp->h3;
	start->h4 += tmp->h4;
	start->h5 += tmp->h5;
	start->h6 += tmp->h6;
	start->h7 += tmp->h7;
}

void	main_loop_512(t_info *info, t_512 *h)
{
	size_t 	i;
	ULLI mass[80];
	t_512 	tmp;

	i = 0;
	while (++i <= info->n)
	{
		prepare_message_schedule_512(info, mass, i);
		initializ_tmp_512(&tmp, h);
		internal_loop_512(&tmp, mass, info);
		intermediate_512(&tmp, h);


//		int j = -1;
//		while (++j < 64)
//			printf("%d %u\n",j, mass[j]);
	}
	// print_res_sha256(h);
}