# define LIGHT 0
# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4
# define L_SPHERE 5
# define L_CYLINDER 6

/*
** USAGE
** Toute les fonctions a rajouter doivent etre declaree en static
** Une Seule fonction __kernel
**
*/

typedef struct			s_vector
{
	float				x;
	float				y;
	float				z;
}						t_vector;

typedef struct			s_color
{
	float				r;
	float				g;
	float				b;
}						t_color;

typedef struct			s_light
{
	t_vector			center;
	t_color				color;
}						t_light;
//
typedef struct			s_material
{
	float				specular;
	float				specular_power;
	int					shiny;
	float				reflection;
	int					transparent;
	float				refraction;
	float				i_refract;
}						t_material;
//
typedef struct			s_figure
{
	int					name;
	float				radius;
	float				separation;
	float				size;
	t_vector			center;
	t_color				color;
	t_vector			angle;
	t_material			material;
}						t_figure;

static t_vector	vecsub(t_vector *v1, t_vector *v2)
{
	t_vector result;

	result.x = v2->x - v1->x;
	result.y = v2->y - v1->y;
	result.z = v2->z - v1->z;
	return (result);
}

static t_vector	vecscale(t_vector *v, float factor)
{
	t_vector result;

	result.x = v->x * factor;
	result.y = v->y * factor;
	result.z = v->z * factor;
	return (result);
}

static float		vecdot(t_vector *v1, t_vector *v2)
{
	float	resx;
	float	resy;
	float	resz;
	float	result;

	resx = v1->x * v2->x;
	resy = v1->y * v2->y;
	resz = v1->z * v2->z;
	result = resx + resy + resz;
	return (result);
}

static t_vector	normalise(t_vector *v1)
{
	t_vector	res;
	float		vdist;

	vdist = sqrt(vecdot(v1, v1));
	res.x = v1->x / vdist;
	res.y = v1->y / vdist;
	res.z = v1->z / vdist;
	return (res);
}

static t_vector	calcul_ptinter(t_vector eye, t_vector r, float t)
{
	t_vector	ptinter;

	ptinter.x = eye.x + r.x * t;
	ptinter.y = eye.y + r.y * t;
	ptinter.z = eye.z + r.z * t;
	return (ptinter);
}

static t_vector	rotations(t_vector vec, float x, float y, float z)
{
	float	tmpx;
	float	tmpy;
	float	tmpz;

	tmpx = vec.x;
	tmpy = vec.y;
	tmpz = vec.z;
	vec.x = tmpx * cos(y) * cos(z) - tmpy * cos(y) * sin(z) + tmpz * sin(y);
	vec.y = tmpx * (cos(x) * sin(z) + sin(x) * sin(y) * cos(z)) + tmpy *
		(cos(x) * cos(z) - sin(x) * sin(y) * sin(z)) - tmpz * sin(x) * cos(y);
	vec.z = tmpx * (sin(x) * sin(z) - cos(x) * sin(y) * cos(z)) + tmpy *
		(sin(x) * cos(z) + cos(x) * sin(y) * sin(z)) + tmpz * cos(x) * cos(y);
	return (vec);
}

//
static int	dist(float a, float b, float c, float *t)
{
	float	disc;
	float	t0;
	float	t1;
	float	tmp;

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

static int			sphere(t_vector r, t_figure s, float *t, t_vector eye)
{
	float	a;
	float	b;
	float	c;

	a = pow(r.x, 2) + pow(r.y, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - s.center.x) + r.y * (eye.y - s.center.y) + r.z *
		(eye.z - s.center.z));
	c = (pow(eye.x - s.center.x, 2) + pow(eye.y - s.center.y, 2) +
		pow(eye.z - s.center.z, 2)) - pow(s.radius, 2);
	return (dist(a, b, c, t));
}

static int			plane(t_vector r, t_figure p, float *t, t_vector eye)
{
	float		tmp;

	tmp = -(-p.center.x * eye.x + p.center.y * eye.y + p.center.z *
		eye.z + p.radius) / (-p.center.x * r.x + p.center.y * r.y +
			p.center.z * r.z);
	if (tmp < *t && tmp > 0.00001)
	{
		*t = tmp;
		return (1);
	}
	return (0);
}

static int			cylinder(t_vector r, t_figure cy, float *t, t_vector eye)
{
	float		a;
	float		b;
	float		c;

	eye = rotations(eye, cy.angle.x, cy.angle.y, cy.angle.z);
	r = rotations(r, cy.angle.x, cy.angle.y, cy.angle.z);
	cy.center = rotations(cy.center, cy.angle.x, cy.angle.y, cy.angle.z);
	a = pow(r.x, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - cy.center.x) + r.z * (eye.z - cy.center.z));
	c = pow(eye.x - cy.center.x, 2) + pow(eye.z - cy.center.z, 2) -
		pow(cy.radius, 2);
	return (dist(a, b, c, t));
}

static int			cone(t_vector r, t_figure co, float *t, t_vector eye)
{
	float		a;
	float		b;
	float		c;

	eye = rotations(eye, co.angle.x, co.angle.y, co.angle.z);
	r = rotations(r, co.angle.x, co.angle.y, co.angle.z);
	co.center = rotations(co.center, co.angle.x, co.angle.y, co.angle.z);
	a = pow(r.x, 2) - pow(r.y, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - co.center.x) - r.y * (eye.y - co.center.y) + r.z *
		(eye.z - co.center.z));
	c = (pow(eye.x - co.center.x, 2) - pow(eye.y - co.center.y, 2) +
		pow(eye.z - co.center.z, 2));
	return (dist(a, b, c, t));
}

static float	distance2(float a, float b, float c)
{
	float	disc;
	float	t0;
	float	t1;
	float	tmp;

	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
		return (0);
	t0 = (-b - sqrt(disc)) / (2 * a);
	t1 = (-b + sqrt(disc)) / (2 * a);
	tmp = (t0 < t1) ? (t0) : (t1);
	return (tmp);
}

static int		disk_calcul(t_vector r, t_figure d, float *t, t_vector eye)
{
	float		tmp;
	t_vector	inter;

	tmp = -(0 * eye.x - 1 * eye.y + 0 *
		eye.z + d.radius) / (0 * r.x + - 1 * r.y +
			0 * r.z);
	if (tmp < *t && tmp > 0.00001)
	{
	   inter = calcul_ptinter(eye, r, tmp);
	   if ((inter.x - d.center.x) * (inter.x - d.center.x) +
	   (inter.z - d.center.z) * (inter.z - d.center.z) < pow(d.size, 2))
	   {
		   *t = tmp;
		   return (1);
	   }
	}
	return (0);
}

static int				limited_sphere(t_vector r, t_figure s, float *t, t_vector eye, int *disk)
{
	float		a;
	float		b;
	float		c;
	float		tmp;
	t_figure	tmp_1;
	t_vector	inter;

	eye = rotations(eye, s.angle.x, s.angle.y, s.angle.z);
	r = rotations(r, s.angle.x, s.angle.y, s.angle.z);
	s.center = rotations(s.center, s.angle.x, s.angle.y, s.angle.z);
	a = pow(r.x, 2) + pow(r.y, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - s.center.x) + r.y * (eye.y - s.center.y) + r.z *
		(eye.z - s.center.z));
	c = (pow(eye.x - s.center.x, 2) + pow(eye.y - s.center.y, 2) +
		pow(eye.z - s.center.z, 2)) - pow(s.radius, 2);
	tmp = distance2(a, b, c);
	if (tmp < *t && tmp > 0.00001)
	{
		inter = calcul_ptinter(eye, r, tmp);
		tmp_1 = s;
		tmp_1.size = sqrt(s.radius * s.radius - s.separation * s.separation);
		tmp_1.radius = tmp_1.center.y + s.separation;
		if (inter.y <= s.center.y + s.separation)
		{
			*t = tmp;
			*disk = 0;
			return (1);
		}
		if (disk_calcul(r, tmp_1, t, eye))
		{
			*disk = 2;
			return (1);
		}
	}
	return (0);
}

static int			limited_cylinder(t_vector r, t_figure cy, float *t, t_vector eye, int *disk)
{
	float		a;
	float		b;
	float		c;
	float		tmp;
	t_figure	tmp_1;
	t_vector	inter;

	eye = rotations(eye, cy.angle.x, cy.angle.y, cy.angle.z);
	r = rotations(r, cy.angle.x, cy.angle.y, cy.angle.z);
	cy.center = rotations(cy.center, cy.angle.x, cy.angle.y, cy.angle.z);
	a = pow(r.x, 2) + pow(r.z, 2);
	b = 2 * (r.x * (eye.x - cy.center.x) + r.z * (eye.z - cy.center.z));
	c = pow(eye.x - cy.center.x, 2) + pow(eye.z - cy.center.z, 2) -
		pow(cy.radius, 2);
	tmp = distance2(a, b, c);
	inter = calcul_ptinter(eye, r, tmp);
	tmp_1 = cy;
	tmp_1.size = cy.radius;
	if (tmp < *t && tmp > 0.00001)
	{
		if (inter.y <= cy.center.y + cy.separation && inter.y >= cy.center.y - cy.separation)
		{
			*t = tmp;
			*disk = 0;
			return (1);
		}
		if (inter.y > cy.center.y + cy.separation)
		{
			tmp_1.radius = tmp_1.center.y + cy.separation;
			if (disk_calcul(r, tmp_1, t, eye))
			{
				*disk = 2;
				return (1);
			}
		}
		if (inter.y < cy.center.y - cy.separation)
		{
			tmp_1.radius = tmp_1.center.y - cy.separation;
			if (disk_calcul(r, tmp_1, t, eye))
			{
				*disk = 3;
				return (1);
			}
		}
	}
	return (0);
}

static int	intersection(__global t_figure *object,
						int nbobj,
						float *t,
						t_vector ray,
						t_vector origin,
						int *disk_cy,
						int *disk_s)
{
	int			i;
	int i2 = -1;

	// *i2 = -1;
	i = 0;
	*t = 200000;
	*disk_cy = 0;
	*disk_s = 0;
	while (i < nbobj)
	{
		if ((object[i].name == SPHERE && sphere(ray, object[i], t,
				(origin))) ||
			(object[i].name == PLANE && plane(ray, object[i], t,
				(origin))) ||
			(object[i].name == CYLINDER && cylinder(ray, object[i],
				t, (origin))) ||
			(object[i].name == CONE && cone(ray, object[i], t,
				(origin))) ||
			(object[i].name == L_SPHERE && limited_sphere(ray, object[i], t,
				(origin), disk_s)) ||
			(object[i].name == L_CYLINDER && limited_cylinder(ray, object[i], t,
				(origin), disk_cy)))
			i2 = i;
		i++;
	}
	return (i2);
}
//
static int		shadows(int nbobj,
						__global t_figure *object,
						t_vector ray_light,
						t_vector inter)
{
	int			i;
	float		t;
	int			disk;

	i = 0;
	t = 1;
	disk = 0;
	while (i < nbobj)
	{
		if ((object[i].name == SPHERE && sphere(ray_light, object[i],
				&t, inter)) ||
			(object[i].name == PLANE && plane(ray_light,
				object[i], &t, inter)) ||
			(object[i].name == CYLINDER && cylinder(ray_light,
				object[i], &t, inter)) ||
			(object[i].name == CONE && cone(ray_light, object[i], &t,
				inter)) ||
			(object[i].name == L_SPHERE && limited_sphere(ray_light, object[i], &t,
				inter, &disk)) ||
			(object[i].name == L_CYLINDER && limited_cylinder(ray_light, object[i], &t,
				inter, &disk)))
			return (1);
		i++;
	}
	return (0);
}

static float	specular_light(t_vector n, t_vector light, t_figure object, t_vector ray)
{
	float		spec;
	t_vector	r;

	ray = normalise(&ray);
	light = vecscale(&light, -1);
	ray = normalise(&light);
	r.x = light.x - 2 * n.x * vecdot(&n, &light);
	r.y = light.y - 2 * n.y * vecdot(&n, &light);
	r.z = light.z - 2 * n.z * vecdot(&n, &light);
	r = normalise(&r);
	spec = object.material.specular * pow(vecdot(&r, &ray), object.material.specular_power);
	return (spec);
}

static t_vector	light_rotate(t_vector *tmp_l_center,
							t_vector *tmp_inter,
							t_vector *tmp_center,
							t_vector *tmp_rlight,
							t_vector inter,
							t_figure object,
							t_light light)
{
	t_vector	light_ray;

	if (object.name != SPHERE && object.name != PLANE)
	{
		*tmp_l_center = rotations(light.center, object.angle.x,
			object.angle.y, object.angle.z);
		*tmp_inter = rotations(inter, object.angle.x, object.angle.y,
			object.angle.z);
		*tmp_center = rotations(object.center, object.angle.x,
			object.angle.y, object.angle.z);
		light_ray = vecsub(tmp_inter, tmp_l_center);
		*tmp_rlight = vecsub(&inter, &light.center);
	}
	else
	{
		*tmp_l_center = light.center;
		*tmp_inter = inter;
		*tmp_center = object.center;
		*tmp_rlight = vecsub(&inter, &light.center);
		light_ray = *tmp_rlight;
	}
	return (light_ray);
}

static void		color_light(float angle, t_color *color, float spec, t_figure object, t_color light)
{
	t_color		tmp_color;

	tmp_color.r = angle * object.color.r * 255;
	tmp_color.g = angle * object.color.g * 255;
	tmp_color.b = angle * object.color.b * 255;
	tmp_color.r = (tmp_color.r > 0xff) ? (0xff) : (tmp_color.r);
	tmp_color.g = (tmp_color.g > 0xff) ? (0xff) : (tmp_color.g);
	tmp_color.b = (tmp_color.b > 0xff) ? (0xff) : (tmp_color.b);
	color->r += tmp_color.r + spec * angle + 255 * light.r * angle;
	color->g += tmp_color.g + spec * angle + 255 * light.g * angle;
	color->b += tmp_color.b + spec * angle + 255 * light.b * angle;
}

static void			light(t_color *color,
						t_figure object,
						t_light light,
						t_vector ray,
						int disk_s,
						int disk_cy,
						t_vector inter,
						__global t_figure *object_list,
						int nbobj)
{
	t_vector	n;
	t_vector	tmp_center;
	t_vector	tmp_rlight;
	t_vector	tmp_inter;
	t_vector	tmp_l_center;
	t_vector	light_ray;
	float		angle;
	float		spec;

	light_ray = light_rotate(&tmp_l_center, &tmp_inter, &tmp_center, &tmp_rlight, inter, object, light);
	if (!shadows(nbobj, object_list, tmp_rlight, inter))
	{
		n = vecsub(&tmp_center, &tmp_inter);
		n.y = (object.name == CYLINDER || object.name == L_CYLINDER || object.name == CONE) ? (0) : (n.y);
		n = (object.name == PLANE) ? (tmp_center) : (n);
		if ((disk_s == 2 && object.name == L_SPHERE) || (disk_cy == 2 && object.name == L_CYLINDER))
		{
			n.x = 0;
			n.y = 1;
			n.z = 0;
		}
		if (disk_cy == 3 && object.name == L_CYLINDER)
		{
			n.x = 0;
			n.y = -1;
			n.z = 0;
		}
		angle = vecdot(&n, &light_ray) / (sqrt(pow(light_ray.x, 2)
		+ pow(light_ray.y, 2) + pow(light_ray.z, 2)) * sqrt(pow(n.x, 2)
		+ pow(n.y, 2) + pow(n.z, 2)));
		if (angle > 0.0001)
		{
			spec = specular_light(n, light_ray, object, ray);
			color_light(angle, color, spec, object, light.color);
		}
	}
}

static void		calcul_light(t_color *color,
							__global t_figure *object,
							__global t_light *light_list,
							int i2,
							t_vector ray,
							int disk_s,
							int disk_cy,
							t_vector inter,
							int nbobj,
							int nblight)
{
	int			i;

	i = 0;
	color->r = 0;
	color->g = 0;
	color->b = 0;
	while (i < nblight)
	{
		light(color, object[i2], light_list[i], ray, disk_s, disk_cy, inter, object, nbobj);
		i++;
	}
	if (nblight != 0)
	{
		color->r /= nblight;
		color->g /= nblight;
		color->b /= nblight;
	}
	color->r = (color->r > 0xff) ? (0xff) : (color->r);
	color->g = (color->g > 0xff) ? (0xff) : (color->g);
	color->b = (color->b > 0xff) ? (0xff) : (color->b);
	color->r = (color->r < 0) ? (0) : (color->r);
	color->g = (color->g < 0) ? (0) : (color->g);
	color->b = (color->b < 0) ? (0) : (color->b);
}

__kernel void raytracer(__global int *image,
						__global t_figure *object,
						float w,
						float h,
						__global t_vector *eye,
						__global t_color *bg_color,
						__global t_vector *cam_angle,
						float xx,
						float zz,
						__global t_light *light,
						int nbobj,
						int nblight)
{
	int			w2 = (int)w;
	int			x = get_global_id(0) % w2;
	int			y = get_global_id(0) / w2;
	t_color		color;
	t_color		color2;
 	t_color		color3;
	t_vector	ray;
	int			i2 = -1;
	t_vector	inter;
	int			final_color = 0;
	float		t = 0;
	int			disk_s = 0;
	int			disk_cy = 0;

	ray.x = x - w / 2 - eye->x;
	ray.y = y - h / 2 - eye->y;
	ray.z = w - eye->z;
	ray = rotations(ray, 0, 0, 0);
	final_color = 0;
	i2 = intersection(object, nbobj, &t, ray, (t_vector)(*eye), &disk_cy, &disk_s);
	color2.r = bg_color->r * 255;
	color2.g = bg_color->g * 255;
	color2.b = bg_color->b * 255;
	if (i2 != -1)
	{
		inter = calcul_ptinter((t_vector)(*eye), ray, t);
		calcul_light(&color, object, light, i2, ray, disk_s, disk_cy, inter, nbobj, nblight);
		color2 = color;
		color3.r = object[i2].color.r * 255;
		color3.g = object[i2].color.g * 255;
		color3.b = object[i2].color.b * 255;
	}
	color2.r *= 0.8;
	color2.g *= 0.8;
	color2.b *= 0.8;
	color3.r *= 0.2;
	color3.g *= 0.2;
	color3.b *= 0.2;
	color2.r += color3.r;
	color2.g += color3.g;
	color2.b += color3.b;
	final_color = (int)color2.r * 0x10000 + (int)color2.g * 0x100 + (int)color2.b;
	image[x + w2 * y] = final_color;
}
