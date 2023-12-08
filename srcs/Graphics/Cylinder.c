/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:34:49 by haeem             #+#    #+#             */
/*   Updated: 2023/12/08 18:46:41 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Cylinder.h"
#include "Scene.h"
#include "Phong.h"

// typedef struct s_cylinder
// {
// 	t_object		object;
// 	double			radius;
// 	double			diameter;
// 	double			height;

// 	t_vector		v_world;
// 	t_vector		v_view;
// 	t_vector		normal_view;
// }				t_cylinder;
void	cylinder_func_init(t_cylinder *this)
{
	this->object.trace_ray = trace_ray;
	this->object.intersect = cylinder_intersect;
	this->object.init_world_coord = cylinder_init_world_coord;
	this->object.update_view_mat = cylinder_update_view_mat;
}

t_hit	cylinder_intersect(t_object *this, t_ray ray)
{
    t_cylinder *cylinder = (t_cylinder *)this;
    t_vector oc = vector_sub(ray.origin, cylinder->object.view_pos);
    double a = vector_dot(ray.dir, ray.dir) - pow(vector_dot(ray.dir, cylinder->normal_view), 2);
    double b = 2.0 * (vector_dot(ray.dir, oc) - (vector_dot(ray.dir, cylinder->normal_view) * vector_dot(oc, cylinder->normal_view)));
    double c = vector_dot(oc, oc) - pow(vector_dot(oc, cylinder->normal_view), 2) - (cylinder->radius * cylinder->radius);
    double discriminant = b * b - 4 * a * c;
	t_hit hit;

	hit.distance = -1.f;
	hit.obj = this;

    if (discriminant < 0)
        return (hit);
    else {
        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
        if (t1 > t2) {
            double temp = t1;
            t1 = t2;
            t2 = temp;
        }

        if (t2 < 0)
			return (hit);
		double t = (t1 > 0 ? t1 : t2);
		double max = sqrt(pow(cylinder->height / 2, 2) + pow(cylinder->radius, 2)); //pythagoras theorem
		t_vector point = vector_add(ray.origin, scalar_mul(t1, ray.dir));
		t_vector len = vector_sub(point, cylinder->v_view);
		if (vector_length(len) > max) // if t1 is too high we try with t2
		   t = t2;
		point = vector_add(ray.origin, scalar_mul(t1, ray.dir));
		len = vector_sub(point, cylinder->object.view_pos);
		if (vector_length(len) > max) // if t2 is too high too then there is no intersection, else t2 is the intersection. And t2 is in the second half of the cylinder
		   return(hit);

		hit.color = this->color;
		hit.distance = t1;
		hit.obj = this;
		hit.point = vector_add(ray.origin, scalar_mul(t1, ray.dir));
		hit.normal = vector_normalize(vector_sub(vector_sub(hit.point, cylinder->object.view_pos), scalar_mul(vector_dot(ray.dir, cylinder->normal_view), cylinder->normal_view)));
		return (hit);
	}
}

void	cylinder_init_world_coord(t_object *this)
{
	t_cylinder *const	cylinder = (t_cylinder *)this;

	cylinder->normal = vector_normalize(cylinder->normal);
	return ;
}

void	cylinder_update_view_mat(t_object *this, t_matrix *tr_view_mat)
{
	t_cylinder *const	cylinder = (t_cylinder *)this;

	this->tr_view_mat = *tr_view_mat;
	transform(&this->view_pos, &this->pos, tr_view_mat);
	transform(&cylinder->normal_view, &cylinder->normal, tr_view_mat);
}

