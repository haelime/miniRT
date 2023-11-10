/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:41:30 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/10 16:20:37 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix.h"

/*
    __asm {
        mov             eax, mat

        vmovups         ymm2, [eax];                    ymm2 = { x0, y0, z0, w0, x1, y1, z1, w1 }
        vmovups         ymm3, [eax + 32];               ymm3 = { x2, y2, z2, w2, x3, y3, z3, w3 }
        vperm2i128      ymm0, ymm2, ymm3, 00100000b;    ymm0 = { x0, y0, z0, w0, x2, y2, z2, w2 }
        vperm2i128      ymm1, ymm2, ymm3, 00110001b;    ymm1 = { x1, y1, z1, w1, x3, y3, z3, w3 }

        ; shuffle to each ymm contain the x,z or y,w elements of every row
        vshufps         ymm2, ymm0, ymm1, 10001000b;    ymm2 = { x0, z0, x1, z1, x2, z2, x3, z3 }
        vshufps         ymm3, ymm0, ymm1, 11011101b;    ymm3 = { y0, w0, y1, w1, y2, w2, y3, w3 }

        vinsertf128     ymm4, ymm2, xmm3, 1;            ymm4 = { x0, z0, x1, z1, y0, w0, y1, w1 }
        vperm2f128      ymm5, ymm2, ymm3, 00110001b;    ymm5 = { x2, z2, x3, z3, y2, w2, y3, w3 }

        vshufps         ymm6, ymm4, ymm5, 10001000b;    ymm6 = { x0, x1, x2, x3, y0, y1, y2, y3 }
        vshufps         ymm7, ymm4, ymm5, 11011101b;    ymm7 = { z0, z1, z2, z3, w0, w1, w2, w3 }

        vmovups         [eax], ymm6
        vmovups         [eax + 32], ymm7
    }
*/
void	transpose(t_matrix *mat)
{
	t_avx		y;

	y.ymm2 = _mm256_load_ps(&mat->m[0][0]);
	y.ymm3 = _mm256_load_ps(&mat->m[2][0]);
	y.ymm0 = _mm256_permute2f128_ps(y.ymm2, y.ymm3, 0x20);
	y.ymm1 = _mm256_permute2f128_ps(y.ymm2, y.ymm3, 0x31);
	y.ymm2 = _mm256_shuffle_ps(y.ymm0, y.ymm1, 0x88);
	y.ymm3 = _mm256_shuffle_ps(y.ymm0, y.ymm1, 0xdd);
	y.ymm4 = _mm256_insertf128_ps(y.ymm2, _mm256_extractf128_ps(y.ymm3, 1), 1);
	y.ymm5 = _mm256_permute2f128_ps(y.ymm2, y.ymm3, 0x31);
	y.ymm6 = _mm256_shuffle_ps(y.ymm4, y.ymm5, 0x88);
	y.ymm7 = _mm256_shuffle_ps(y.ymm4, y.ymm5, 0xdd);
	_mm256_store_ps(&mat->m[0][0], y.ymm6);
	_mm256_store_ps(&mat->m[2][0], y.ymm7);
}


/*
    __asm {
        mov             edi, dst
        mov             esi, src
        mov             eax, mat_tr

        vbroadcastf128  ymm0, [esi];                    ymm0 = { x, y, z, w, x, y, z, w }
        vmovups         ymm1, [eax];                    ymm1 = { x0, y0, z0, w0, x1, y1, z1, w1 }
        vmovups         ymm2, [eax + 32];               ymm2 = { x2, y2, z2, w2, x3, y3, z3, w3 }

        vdpps           ymm1, ymm0, ymm1, 11110001b;    ymm1 = { s0, 0, 0, 0, s1, 0, 0, 0 }
        vdpps           ymm2, ymm0, ymm2, 11110001b;    ymm2 = { s2, 0, 0, 0, s3, 0, 0, 0 }

        vpermq          ymm1, ymm1, 11111000b;          xmm1 = { s0, 0, s1, 0 }
        vpermq          ymm2, ymm2, 11111000b;          xmm2 = { s2, 0, s3, 0 }
        shufps          xmm1, xmm2, 10001000b;          xmm1 = { s0, s1, s2, s3 }

        movups          [edi], xmm1
    }
*/
void	transform(t_matrix *dst, const t_matrix *src, const t_matrix *mat_tr)
{
	t_avx		y;

	y.ymm0 = _mm256_broadcast_ps((__m128 *)&src->m[0][0]);
	y.ymm1 = _mm256_load_ps(&mat_tr->m[0][0]);
	y.ymm2 = _mm256_load_ps(&mat_tr->m[2][0]);
	y.ymm3 = _mm256_dp_ps(y.ymm0, y.ymm1, 0xf1);
	y.ymm4 = _mm256_dp_ps(y.ymm0, y.ymm2, 0xf1);
	y.ymm5 = _mm256_permute2f128_ps(y.ymm3, y.ymm4, 0x20);
	y.ymm6 = _mm256_permute2f128_ps(y.ymm3, y.ymm4, 0x31);
	y.ymm7 = _mm256_shuffle_ps(y.ymm5, y.ymm6, 0x88);
	_mm256_store_ps(&dst->m[0][0], y.ymm7);
}

/*
    __asm {
        mov             edi, dst
        mov             esi, m0
        mov             eax, m1_tr

        // load m1_tr
        vmovups         ymm2, [eax];                    ymm2 = { x0, y0, z0, w0, x1, y1, z1, w1 }
        vmovups         ymm3, [eax + 32];               ymm3 = { x2, y2, z2, w2, x3, y3, z3, w3 }

        // m0_r0
        vbroadcastf128  ymm0, [esi]
        vdpps           ymm4, ymm0, ymm2, 11110001b;    ymm4 = { x0, 0, 0, 0, y0, 0, 0, 0 }
        vdpps           ymm5, ymm0, ymm3, 11110001b;    ymm5 = { z0, 0, 0, 0, w0, 0, 0, 0 }
        vpermq          ymm4, ymm4, 11111000b;          xmm4 = { x0, 0, y0, 0 }
        vpermq          ymm5, ymm5, 11111000b;          xmm5 = { z0, 0, w0, 0 }
        shufps          xmm4, xmm5, 10001000b;          xmm4 = { x0, y0, z0, w0 }
        movups          [edi], xmm4
		
		...
*/
void	concatenate(t_matrix *dst, const t_matrix *m0, const t_matrix *m1_tr)
{
	t_avx		y;
	int			i;

	y.ymm2 = _mm256_load_ps(&m1_tr->m[0][0]);
	y.ymm3 = _mm256_load_ps(&m1_tr->m[2][0]);
	i = -1;
	while (++i < 4)
	{
		y.ymm0 = _mm256_broadcast_ps((__m128 *)&m0->m[i][0]);
		y.ymm4 = _mm256_dp_ps(y.ymm0, y.ymm2, 0xf1);
		y.ymm5 = _mm256_dp_ps(y.ymm0, y.ymm3, 0xf1);
		y.ymm6 = _mm256_permute2f128_ps(y.ymm4, y.ymm5, 0x20);
		y.ymm7 = _mm256_permute2f128_ps(y.ymm4, y.ymm5, 0x31);
		y.ymm0 = _mm256_shuffle_ps(y.ymm6, y.ymm7, 0x88);
		_mm256_store_ps(&dst->m[0][0], y.ymm0);
	}
}

