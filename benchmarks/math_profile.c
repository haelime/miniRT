#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
# include <windows.h>
#else
# include <time.h>
#endif
#include "Matrix.h"

#define DEFAULT_ITERATIONS 2000000ULL
#define SAMPLE_COUNT 256

#if defined(__GNUC__) || defined(__clang__)
# define NOINLINE __attribute__((noinline))
#else
# define NOINLINE
#endif

typedef float (*t_dot_fn)(t_vector, t_vector);
typedef void (*t_transform_fn)(t_vector *, const t_vector *, const t_matrix *);
typedef void (*t_concat_fn)(t_matrix *, const t_matrix *, const t_matrix *);

typedef struct s_result
{
	double	seconds;
	double	checksum;
} t_result;

static volatile double	g_sink;

static double	now_seconds(void)
{
#ifdef _WIN32
	LARGE_INTEGER	counter;
	LARGE_INTEGER	frequency;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&counter);
	return ((double)counter.QuadPart / (double)frequency.QuadPart);
#else
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((double)ts.tv_sec + (double)ts.tv_nsec * 1e-9);
#endif
}

static NOINLINE float	scalar_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

static NOINLINE float	scalar_dot_row(const t_vector *src, const float row[4])
{
	return (src->x * row[0] + src->y * row[1]
		+ src->z * row[2] + src->w * row[3]);
}

static NOINLINE void	scalar_transform(t_vector *dst, const t_vector *src,
		const t_matrix *mat_tr)
{
	dst->x = scalar_dot_row(src, mat_tr->m[0]);
	dst->y = scalar_dot_row(src, mat_tr->m[1]);
	dst->z = scalar_dot_row(src, mat_tr->m[2]);
	dst->w = scalar_dot_row(src, mat_tr->m[3]);
}

static NOINLINE void	scalar_concatenate(t_matrix *dst, const t_matrix *m0,
		const t_matrix *m1_tr)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			dst->m[i][j] = 0.f;
			k = -1;
			while (++k < 4)
				dst->m[i][j] += m0->m[i][k] * m1_tr->m[j][k];
		}
	}
}

static void	fill_inputs(t_vector vectors[SAMPLE_COUNT],
		t_matrix matrices[SAMPLE_COUNT], t_matrix *rhs)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < SAMPLE_COUNT)
	{
		vectors[i] = make_vector((float)(i + 1) * 0.003f,
				(float)(i % 17) * -0.017f, (float)(i % 29) * 0.011f, 1.f);
		j = -1;
		while (++j < 4)
		{
			k = -1;
			while (++k < 4)
				matrices[i].m[j][k] = (float)((i + 3 * j + 5 * k) % 31)
					* 0.013f + (j == k ? 1.f : 0.f);
		}
	}
	j = -1;
	while (++j < 4)
	{
		k = -1;
		while (++k < 4)
			rhs->m[j][k] = (float)((7 * j + 11 * k) % 19) * 0.021f
				+ (j == k ? 1.f : 0.f);
	}
}

static int	close_enough(float a, float b)
{
	return (fabsf(a - b) <= 1e-4f * fmaxf(1.f, fmaxf(fabsf(a), fabsf(b))));
}

static int	verify_results(const t_vector vectors[SAMPLE_COUNT],
		const t_matrix matrices[SAMPLE_COUNT], const t_matrix *rhs)
{
	t_vector	scalar_vec;
	t_vector	simd_vec;
	t_matrix	scalar_mat;
	t_matrix	simd_mat;
	int		i;
	int		j;

	if (!close_enough(scalar_dot(vectors[3], vectors[17]),
			vector_dot(vectors[3], vectors[17])))
		return (0);
	scalar_transform(&scalar_vec, &vectors[11], rhs);
	transform(&simd_vec, &vectors[11], rhs);
	if (!close_enough(scalar_vec.x, simd_vec.x)
		|| !close_enough(scalar_vec.y, simd_vec.y)
		|| !close_enough(scalar_vec.z, simd_vec.z)
		|| !close_enough(scalar_vec.w, simd_vec.w))
		return (0);
	scalar_concatenate(&scalar_mat, &matrices[23], rhs);
	concatenate(&simd_mat, &matrices[23], rhs);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (!close_enough(scalar_mat.m[i][j], simd_mat.m[i][j]))
				return (0);
	}
	return (1);
}

static t_result	profile_dot(t_dot_fn fn, const t_vector vectors[SAMPLE_COUNT],
		uint64_t iterations)
{
	t_result	result;
	double		start;
	double		checksum;
	uint64_t	i;

	checksum = 0.0;
	start = now_seconds();
	i = 0;
	while (i < iterations)
	{
		checksum += fn(vectors[i & (SAMPLE_COUNT - 1)],
				vectors[(i * 17 + 13) & (SAMPLE_COUNT - 1)]);
		++i;
	}
	result.seconds = now_seconds() - start;
	result.checksum = checksum;
	g_sink = checksum;
	return (result);
}

static t_result	profile_transform(t_transform_fn fn,
		const t_vector vectors[SAMPLE_COUNT], const t_matrix *rhs,
		uint64_t iterations)
{
	t_result	result;
	t_vector	out;
	double		start;
	double		checksum;
	uint64_t	i;

	checksum = 0.0;
	start = now_seconds();
	i = 0;
	while (i < iterations)
	{
		fn(&out, &vectors[i & (SAMPLE_COUNT - 1)], rhs);
		checksum += out.x + out.y + out.z + out.w;
		++i;
	}
	result.seconds = now_seconds() - start;
	result.checksum = checksum;
	g_sink = checksum;
	return (result);
}

static t_result	profile_concatenate(t_concat_fn fn,
		const t_matrix matrices[SAMPLE_COUNT], const t_matrix *rhs,
		uint64_t iterations)
{
	t_result	result;
	t_matrix	out;
	double		start;
	double		checksum;
	uint64_t	i;

	checksum = 0.0;
	start = now_seconds();
	i = 0;
	while (i < iterations)
	{
		fn(&out, &matrices[i & (SAMPLE_COUNT - 1)], rhs);
		checksum += out.m[0][0] + out.m[1][1] + out.m[2][2] + out.m[3][3];
		++i;
	}
	result.seconds = now_seconds() - start;
	result.checksum = checksum;
	g_sink = checksum;
	return (result);
}

static void	print_row(const char *operation, const char *implementation,
		uint64_t iterations, int flops, int packed_width, t_result result,
		double speedup)
{
	double	ns_per_call;
	double	gflops;

	ns_per_call = result.seconds * 1e9 / (double)iterations;
	gflops = (double)flops * (double)iterations / result.seconds / 1e9;
	printf("%s,%s,%llu,%d,%d,%.3f,%.3f,%.3f,%.3f,%.6f\n",
		operation, implementation, (unsigned long long)iterations, flops,
		packed_width, result.seconds * 1000.0, ns_per_call, gflops, speedup,
		result.checksum);
}

static uint64_t	parse_iterations(int argc, char **argv)
{
	char		*end;
	uint64_t	iterations;

	if (argc < 2)
		return (DEFAULT_ITERATIONS);
	errno = 0;
	iterations = strtoull(argv[1], &end, 10);
	if (errno != 0 || *end != '\0' || iterations < 1000)
	{
		fprintf(stderr, "iterations must be an integer >= 1000\n");
		exit(EXIT_FAILURE);
	}
	return (iterations);
}

int	main(int argc, char **argv)
{
	t_vector	vectors[SAMPLE_COUNT];
	t_matrix	matrices[SAMPLE_COUNT];
	t_matrix	rhs;
	t_result	dot_scalar;
	t_result	dot_simd;
	t_result	transform_scalar;
	t_result	transform_simd;
	t_result	concat_scalar;
	t_result	concat_simd;
	uint64_t	iterations;

	iterations = parse_iterations(argc, argv);
	fill_inputs(vectors, matrices, &rhs);
	if (!verify_results(vectors, matrices, &rhs))
	{
		fprintf(stderr, "scalar and SIMD results differ\n");
		return (EXIT_FAILURE);
	}
	dot_scalar = profile_dot(scalar_dot, vectors, iterations);
	dot_simd = profile_dot(vector_dot, vectors, iterations);
	transform_scalar = profile_transform(scalar_transform, vectors, &rhs,
			iterations);
	transform_simd = profile_transform(transform, vectors, &rhs, iterations);
	concat_scalar = profile_concatenate(scalar_concatenate, matrices, &rhs,
			iterations);
	concat_simd = profile_concatenate(concatenate, matrices, &rhs, iterations);
	printf("operation,implementation,iterations,math_flops_per_call,"
		"packed_float_width,total_ms,ns_per_call,gflops_per_second,"
		"speedup_vs_scalar,checksum\n");
	print_row("dot4", "scalar", iterations, 7, 1, dot_scalar, 1.0);
	print_row("dot4", "sse", iterations, 7, 4, dot_simd,
		dot_scalar.seconds / dot_simd.seconds);
	print_row("mat4xvec4", "scalar", iterations, 28, 1,
		transform_scalar, 1.0);
	print_row("mat4xvec4", "avx2", iterations, 28, 8, transform_simd,
		transform_scalar.seconds / transform_simd.seconds);
	print_row("mat4xmat4", "scalar", iterations, 112, 1,
		concat_scalar, 1.0);
	print_row("mat4xmat4", "avx2", iterations, 112, 8, concat_simd,
		concat_scalar.seconds / concat_simd.seconds);
	return (g_sink == 0.0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
