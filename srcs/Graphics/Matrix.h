/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:26:15 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 21:55:37 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <immintrin.h>
# include "Vector.h"

/* Matrix should aligned by 64byte for LFB(WC) flush */
typedef struct s_matrix
{
	__attribute__((aligned(64)))
	float		m[4][4];
}				t_matrix;

void	transpose(t_matrix *mat);
void	transform(t_vector *dst, const t_vector *src, const t_matrix *mat_tr);
void	concatenate(t_matrix *dst, const t_matrix *m0, const t_matrix *m1_tr);
void	make_diagonal_matrix(t_matrix *mat, t_vector vec);

typedef struct s_avx
{
	__m256		ymm0;
	__m256		ymm1;
	__m256		ymm2;
	__m256		ymm3;
	__m256		ymm4;
	__m256		ymm5;
	__m256		ymm6;
	__m256		ymm7;
}				t_avx;

typedef struct s_sse
{
	__m128		xmm0;
	__m128		xmm1;
	__m128		xmm2;
	__m128		xmm3;
	__m128		xmm4;
	__m128		xmm5;
	__m128		xmm6;
	__m128		xmm7;
}				t_sse;

#endif // MATRIX_H
