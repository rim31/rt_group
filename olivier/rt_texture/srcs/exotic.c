/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exotic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 15:12:19 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/07 16:07:37 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	coef pour les figures exotics
** nappe bizarre
** a = 0.1;
** b = 0.1;
** c = 0.1;
** d = 0;
** e = 0;
** f = 1;
** g = -1;
** h = 1;
** i = 0;
** j = 0;
**
**oeuf
** a = 10;
** b = 10;
** c = 10;
** d = 0;
** e = 0;
** f = 10;
** g = -10;
** h = 10;
** i = 0;
** j = 0;
**
** elipsoide
** a = 4;
** b = 1;
** c = 4;
** d = 0;
** e = 0;
** f = 0;
** g = 0;
** h = 0;
** i = 0;
*/

static double solveur4(double x0, double x1, double x2, double x3, double x4)
{
	// double a[5] = { 4, 0, -5, 0, 1 };
	double a[5];
	double z[10];
	double res;
	int i;

	res = 0.00000000;
	a[0] = x0;
	a[1] = x1;
	a[2] = x2;
	a[3] = x3;
	a[4] = x4;
	gsl_poly_complex_workspace * w = gsl_poly_complex_workspace_alloc (5);
	gsl_poly_complex_solve (a, 5, w, z);
	gsl_poly_complex_workspace_free (w);
	i = 0;
	while(i < 4)
	{
		// printf ("z%d = %+.18f + i.%+.18f\n", i, z[2 * i], z[2 * i + 1]);
		if (z[2 * i + 1] == 0.000000000 && (((z[2 * i] < res) ||
		(res == 0.000000000)) && (z[2 * i] > 0.000000000)))
			res = z[2 * i];
	}
	i++;
	// printf ("%f = solution la plus petite", res);
	return (res);
}

static int	distance(double a, double b, double c, double *t)
{
	double	disc;
	double	t0;
	double	t1;
	double	tmp;

	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (0);
	t0 = (-b - sqrt(disc)) / (2 * a);
	t1 = (-b + sqrt(disc)) / (2 * a);
	tmp = (t0 < t1) ? (t0) : (t1);
	if (tmp < *t && tmp > 0.00001)
	{
		*t = tmp;
		return (1);
	}
	return (0);
}

/*
** A.x^2+ B.y^2 + C.z^2 + D.x.y + E.x.z + F.y.z + G.x + H.y + I.z + J = 0
*/

int			quadric(t_vector r, t_figure q, double *t, t_vector eye) // equation du 2nd degre
{
	float a;
	float b;
	float c;
	float d;
	float e;
	float f;
	float g;
	float h;
	float i;
	float j;

	float aa;
	float bb;
	float cc;
	// discrinimant avec les coef aa, bb, cc

	a = 10;
	b = 10;
	c = 10;
	d = 0;
	e = 0;
	f = 10;
	g = -10;
	h = 10;
	i = 0;
	j = 0;
	aa = a * r.x * r.x + b * r.y * r.y + c * r.z * r.z + d * r.x * r.y + e * r.x
	 * r.z + f * r.y * r.z;
	bb = 2 * a * eye.x * r.x + 2 * b * eye.y * r.y + 2 * c * eye.z * r.z + d *
	(eye.x * r.y + eye.y * r.x) + e * (eye.x * r.z + r.x * eye.z) + f * (eye.y *
	r.z + r.y  * eye.z) + g * r.x + f * r.y + i * r.z;
	cc = a * eye.x * eye.x + b * eye.y * eye.y + c * eye.z * eye.z + d * eye.x *
	 eye.y + e * eye.x * eye.z + f * eye.y * eye.z + g * eye.x + h * eye.y + i *
	  eye.z + j;
	return (distance(aa, bb, cc, t));
}

int			torus(t_vector ray, t_figure to, double *t, t_vector eye)
{
// //   float r2 = 1000;
// //   float R2 = 100;
// //   double tmp;
// //
// // (void)to.name;
// //   double a4 = pow(ray.x * ray.x +  ray.y * ray.y + ray.z * ray.z, 2);
// //   double a3 = 4 * (ray.x * ray.x +  ray.y * ray.y + ray.z * ray.z) * (ray.x * eye.x +  ray.y * eye.y + ray.z * eye.z);
// //   double a2 = 4 * (pow(ray.x * eye.x +  ray.y * eye.y + ray.z * eye.z, 2)) + 2 * (ray.x * ray.x +  ray.y * ray.y + ray.z * ray.z) * ((eye.x * eye.x +  eye.y * eye.y + eye.z * eye.z) - r2 - R2) + 4 * R2 * (ray.z * ray.z);
// //   double a1 = 4 * (ray.x * eye.x +  ray.y * eye.y + ray.z * eye.z) * ((eye.x * eye.x +  eye.y * eye.y + eye.z * eye.z) - r2 - R2) + 8 * R2 * eye.z * ray.z;
// //   double a0 = pow((eye.x * eye.x +  eye.y * eye.y + eye.z * eye.z) - r2 - R2, 2) + 4 * R2 * (eye.z * eye.z) - 4 * R2 * r2;
// //
// // 	tmp = solveur4(a0, a1, a2, a3, a4);
// // //	===========================================================================================
	float a = 10;
	float b = 3;

	float x1 = eye.x;
	float y1 = eye.y;
	float z1 = eye.z;
	float d1 = ray.x;
	float d2 = ray.y;
	float d3 = ray.z;
	float c[5];
	double tmp;
	(void)to.name;

	float sum_d_sqr = d1 * d1 + d2 * d2 + d3 * d3;
	float e = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	float f = x1 * d1 + y1 * d2 + z1 - d3;
	float four_a_sqr = 4.0 * a * a;
	c[0] = e * e - four_a_sqr * (b * b - y1 * y1);
	c[1] = 4.0 * f * e +2.0 * four_a_sqr * y1 * d2;
	c[2] = 2.0 * sum_d_sqr * e + 4.0 * f * f + four_a_sqr * d2 * d2;
	c[3] = 4.0 * sum_d_sqr * f;
	c[4] = sum_d_sqr * sum_d_sqr;
	tmp = solveur4(c[0], c[1], c[2], c[3], c[4]);
// 	if (tmp < *t && tmp > 0.00001)
// 	{
// 		*t = tmp;
// 		// ft_putstr("yes");
// 		return (1);
// 	}
// 	return (0);
// //===========================================================================================
// 	// float a;
// 	// float b;
// 	// float c0;
// 	// float c1;
// 	// float c2;
// 	// float c3;
// 	// float c4;
// 	// double tmp;
// 	//
// 	// // fornule : (z - a)^2 + y^2 - b^2 = 0
// 	// //((x*x + y*y + z*z)^2 - 2 * (a*a + b*b)*(x*x + y*y +z*z) + 4*a*a*y*y + (a*a - b*b)^2 = 0
// 	// // cercle de rayon b et de centre d'epaisseur z =a il faut aue a>>b pour avoir un beau donuts, si a =b
// 	//
// 	// // resolution de la quadric du 4eme degre
// 	// a = 1;
// 	// b = 2;
// 	// float trucdeouf;
// 	// trucdeouf =  pow((eye.x * eye.x + eye.y * eye.y + eye.z * eye.z -
// 	// 	(a * a + b * b)), 2);
// 	// c4 = pow((ray.x * ray.x + ray.y * ray.y + ray.z * ray.z), 2);
// 	// c3 = 4 * (ray.x * ray.x + ray.y * ray.y + ray.z * ray.z) * (eye.x * ray.x + eye.y * ray.y +
// 	// 	eye.z * ray.z);
// 	// c2 = 2 * (ray.x * ray.x + ray.y * ray.y + ray.z * ray.z) * trucdeouf + 4 *
// 	// (eye.x * ray.x + eye.y  * ray.y + eye.z * ray.z) + 4 * a * a * ray.y * ray.y;
// 	// c1 = 4 * trucdeouf * (eye.x * ray.x + eye.y * ray.y + eye.z * ray.z) + 8 * a
// 	// * a * eye.y * ray.y;
// 	// c0 = 4 * trucdeouf - 4 * a * a * (b * b - eye.y + eye.y);
//
// 	// double a;//a t4 + b t3 + c t² + d t + e = 0
// 	// double b;
// 	// double c;
// 	// double d;
// 	// double e;
// 	// unsigned int aa = 100;
// 	// unsigned int bb = 3;
// 	// double tmp;
// 	// //
// 	// // a = (vecdot(&r, &r), 2);
// 	// // b = 4 * vecdot(&r, &r) * vecdot(&r, &eye);
// 	// // c = 2 * vecdot(&r, &r) * (vecdot(&eye, &eye) - aa * aa - bb * bb) +
// 	// // 4 * pow(vecdot(&r, &eye), 2) + 4 * aa * aa * (r.y * r.y);
// 	// // d = 4 * ((vecdot(&eye, &eye) - aa * aa - bb * bb) * vecdot(&eye, &r)) + 8 * a * a * (r.y * eye.y);
// 	// // e = pow((vecdot(&eye, &eye) - aa * aa - bb * bb), 2) - 4 * a * a * (bb * bb - eye.y * eye.y);
// // double r2 = dsqr(torus.r1);
// // double R2 = dsqr(torus.r2);
// //
// // double a4 = dsqr(ddot(Dir, Dir));
// // double a3 = 4 * ddot(Dir, Dir) * ddot(O, Dir);
// // double a2 = 4 * dsqr(ddot(O, Dir)) + 2 * ddot(Dir, Dir) * (ddot(O, O) - r2 - R2)
// //     + 4 * R2 * dsqr(Dir.z);
// // double a1 = 4 * ddot(O, Dir) * (ddot(O, O) - r2 - R2) + 8 * R2 * O.z * Dir.z;
// // double a0 = dsqr(ddot(O, O) - r2 - R2) + 4 * R2 * dsqr(O.z) - 4 * R2 * r2;
// 	//
// 	// a = pow(r.x * r.x + r.y * r.y + r.z * r.z, 2);
// 	// b = 4 * (r.x * r.x + r.y * r.y + r.z * r.z) * (r.x * eye.x + r.y * eye.y + r.z * eye.z);
// 	// c = 2 * (r.x * r.x + r.y * r.y + r.z * r.z) * ((eye.x * eye.x + eye.y * eye.y + eye.z * eye.z) + aa * aa - bb * bb) +
// 	// pow(r.x * eye.x + r.y * eye.y + r.z * eye.z, 2) - 4 * aa * aa * (r.x * r.x + r.z * r.z);
// 	// d = 4 * (r.x * eye.x + r.y * eye.y + r.z * eye.z) * (eye.x * eye.x + eye.y * eye.y + eye.z * eye.z + aa * aa - bb * bb) - 8 * aa * aa * (r.x * eye.x + r.z * eye.z);
// 	// e = pow(eye.x * eye.x + eye.y * eye.y + eye.z * eye.z + aa * aa - bb * bb, 2) - 4 * a * a * (eye.x * eye.x + eye.z * eye.z);
//
// 	// (void)to.name;
// 	// if (a == 0.000000)
// 	// 	tmp = solveur3(e, d, c, b);
// 	// tmp = solveur4(e, d, c, b, a);
// 	if (tmp < *t && tmp > 0.00001)
// 	{
// 		*t = tmp;
// 		// ft_putstr("yes");
// 		return (1);
// 	}
// 	return (0);
}

//=====================================================================================
// int			torus(t_vector r, t_figure q, double *t, t_vector eye)//version paraboloide
// {
// 	double a;
// 	double b;
// 	double c;
//
// 	eye = rotations(eye, q.angle.x, q.angle.y, q.angle.z);
// 	r = rotations(r, q.angle.x, q.angle.y, q.angle.z);
// 	q.center = rotations(q.center, q.angle.x, q.angle.y, q.angle.z);
// 	q.radius = -3;
// 	eye = rotations(eye, q.angle.x, q.angle.y, q.angle.z);
// 	r = rotations(r, q.angle.x, q.angle.y, q.angle.z);
// 	q.center = rotations(q.center, q.angle.x, q.angle.y, q.angle.z);
// 	a = pow(r.x, 2) - pow(r.y, 2) + pow(r.z, 2);
// 	b = 2 * (r.x * (eye.x - q.center.x) - r.y * (eye.y - q.center.y) + r.z *
// 		(eye.z - q.center.z));
// 	c = (pow(eye.x - q.center.x, 2) - pow(eye.y - q.center.y, 2) +
// 		pow(eye.z - q.center.z, 2)) - q.radius;
// 	return (distance(a, b, c, t));
// }
//========================================================================================

// int			torus(t_vector r, t_figure q, double *t, t_vector eye)
// {
// 	double a;
// 	double b;
// 	double c;
//
// 	eye = rotations(eye, q.angle.x, q.angle.y, q.angle.z);
// 	r = rotations(r, q.angle.x, q.angle.y, q.angle.z);
// 	q.center = rotations(q.center, q.angle.x, q.angle.y, q.angle.z);
// 	q.radius = -3;
// 	eye = rotations(eye, q.angle.x, q.angle.y, q.angle.z);
// 	r = rotations(r, q.angle.x, q.angle.y, q.angle.z);
// 	q.center = rotations(q.center, q.angle.x, q.angle.y, q.angle.z);
// 	a = pow(r.x, 2) - pow(r.y, 2) + pow(r.z, 2);
// 	b = 2 * (r.x * (eye.x - q.center.x) - r.y * (eye.y - q.center.y) + r.z *
// 		(eye.z - q.center.z));
// 	c = (pow(eye.x - q.center.x, 2) - pow(eye.y - q.center.y, 2) +
// 		pow(eye.z - q.center.z, 2)) - q.radius;
//
// 	double	disc;
// 	double	t0;
// 	double	t1;
// 	double	tmp;
// 	double	tmp2;
//
// 	disc = b * b - 4 * a * c;
// 	if (disc < 0)
// 		return (0);
// 	t0 = (-b - sqrt(disc)) / (2 * a);
// 	t1 = (-b + sqrt(disc)) / (2 * a);
// 	tmp = (t0 < t1) ? (t0) : (t1);
// 	tmp2 = (t0 < t1) ? (t1) : (t0);
// 	if (q.negativ && tmp2 < *t)
// 		return (0);
// 	if (tmp < *t && tmp > 0.00001)
// 	{
// 		*t = tmp;
// 		return (1);
// 	}
// 	return (0);
// }
