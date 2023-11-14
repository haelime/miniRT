/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:26:15 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 19:32:43 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <immintrin.h>

typedef struct s_matrix
{
	__attribute__((aligned(64)))
	float		m[4][4];
}				t_matrix;

void	transpose(t_matrix *mat);
void	transform(t_matrix *dst, const t_matrix *src, const t_matrix *mat_tr);
void	concatenate(t_matrix *dst, const t_matrix *m0, const t_matrix *m1_tr);

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

#endif // MATRIX_H
