/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:41:30 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 22:09:47 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix.h"

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

void	transform(t_vector *dst, const t_vector *src, const t_matrix *mat_tr)
{
	t_avx		y;
	t_sse		x;

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
    } */
	y.ymm0 = _mm256_broadcast_ps((__m128 *)&src->x);
	y.ymm1 = _mm256_load_ps(&mat_tr->m[0][0]);
	y.ymm2 = _mm256_load_ps(&mat_tr->m[2][0]);
	y.ymm1 = _mm256_dp_ps(y.ymm0, y.ymm1, 0xf1);
	y.ymm2 = _mm256_dp_ps(y.ymm0, y.ymm2, 0xf1);
	y.ymm1 = _mm256_permute2f128_ps(y.ymm1, y.ymm1, 0xf8);
	y.ymm2 = _mm256_permute2f128_ps(y.ymm2, y.ymm2, 0xf8);
	x.xmm1 = _mm_shuffle_ps(_mm256_extractf128_ps(y.ymm1, 0),
			_mm256_extractf128_ps(y.ymm2, 0), 0x88);
	_mm_store_ps(&dst->x, x.xmm1);
}

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

void	make_diagonal_matrix(t_matrix *mat, t_vector vec)
{
	mat->m[0][0] = vec.x;
	mat->m[0][1] = 0.f;
	mat->m[0][2] = 0.f;
	mat->m[0][3] = 0.f;
	mat->m[1][0] = 0.f;
	mat->m[1][1] = vec.y;
	mat->m[1][2] = 0.f;
	mat->m[1][3] = 0.f;
	mat->m[2][0] = 0.f;
	mat->m[2][1] = 0.f;
	mat->m[2][2] = vec.z;
	mat->m[2][3] = 0.f;
	mat->m[3][0] = 0.f;
	mat->m[3][1] = 0.f;
	mat->m[3][2] = 0.f;
	mat->m[3][3] = vec.w;
}

