/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseng <oseng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 11:31:22 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/01 18:22:02 by oseng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"



// double rand_noise(int t)
// {
//     t = pow((t << 13), t);
//     t = (t * (t * t * 15731 + 789221) + 1376312589);
//     return (1.0 - (t & 0x7fffffff) / 1073741824.0);
// }
//
// double rand_set[W * H * K];

//Initialisation du tableau, etc.

// double noise_3d(int x, int y, int z)
// {
//     return (rand_set[x + y * w + z * w * h]);
// }
//
// //Bruit bidimensionnelSélectionnez
//
// double noise_2d(int x, int y)
// {
//     int tmp;
//
// 	tmp = rand_noise(x) * 850000;
//     return (rand_noise(tmp + y));
// }
//
// double noise_4d(int x, int y, int z, int t)
// {
//     int tmp_x;
//     int tmp_y;
//     int tmp_z;
//
// 	tmp_x = rand_noise(x) * 850000;
// 	tmp_y = rand_noise(tmp_x + y) * 850000;
// 	tmp_z = rand_noise(tmp_y + z) * 850000;
//     return (rand_noise(tmp_z + t));
// }

// double noise_nd(int *data_set, int dim)
// {
//     int i;
//     double r;
//
// 	i = 0;
// 	r = 0.0;
//     while(i < dim)
// 	{
//         r = rand_noise(data_set[i] + (int)(r * 850000) );
// 		i++;
// 	}
// 	return (r);
// }
//
// double linear_interpolate(double a, double b, double t)
// {
//     return ((1.0 - t) * a + t * b);
// }
//
// double cosine_interpolate(double a, double b, double t)
// {
//     double c;
//
// 	c = (1 - cos(t * M_PI)) * 0.5;
//     return ((1. - c) * a + c * b);
// }


  //___________________________________________________________________________________________________________________________


#define B 0x100
#define BM 0xff
#define N 0x1000
#define NP 12   /* 2^N */
#define NM 0xfff

#define s_curve(t) ( t * t * (3. - 2. * t) )
#define lerp(t, a, b) ( a + t * (b - a) )
#define setup(i,b0,b1,r0,r1)\
        t = vec[i] + N;\
        b0 = ((int)t) & BM;\
        b1 = (b0+1) & BM;\
        r0 = t - (int)t;\
        r1 = r0 - 1.;
#define at2(rx,ry) ( rx * q[0] + ry * q[1] )
#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )


static int p[B + B + 2];
static double g3[B + B + 2][3];
static double g2[B + B + 2][2];
static double g1[B + B + 2];
static int start = 1;

void normalize3(double v[3])
{
   double s;

   s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
   v[0] = v[0] / s;
   v[1] = v[1] / s;
   v[2] = v[2] / s;
}

void init(void)
{
   int i;
   int j;
   int k;

	i = 0;
	j = 0;
	k = 0;
   srand(time(NULL));
   // for (i = 0 ; i < B ; i++)

	while(i < B)
	{
      p[i] = i;
      g1[i] = (double)((rand() % (B + B)) - B) / B;

    //   for (j = 0 ; j < 3 ; j++)
	j = 0;
	while(j<3)
    {
			 g3[i][j] = (double)((rand() % (B + B)) - B) / B;
			 j++;
	}
      normalize3(g3[i]);
	  i++;
   }

   while (--i)
 	{
      k = p[i];
      p[i] = p[j = rand() % B];
      p[j] = k;
   }
	i = 0;
	while(i < B)   // for (i = 0 ; i < B + 2 ; i++) {
     {
		  p[B + i] = p[i];
      g1[B + i] = g1[i];
	  j = 0;
         while(j < 2)    //   for (j = 0 ; j < 2 ; j++)
		 {
			 g2[B + i][j] = g2[i][j];
			 j++;
		 }
		 j = 0;
             while(j < 3)//   for (j = 0 ; j < 3 ; j++)
		 {
			 g3[B + i][j] = g3[i][j];
			 j++;
		 }
		i++;
   }
}

double noise(double vec[3])
{
   int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
   double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
   int i, j;

   if (start)
   {
      start = 0;
      init();
   }

   setup(0, bx0,bx1, rx0,rx1);
   setup(1, by0,by1, ry0,ry1);
   setup(2, bz0,bz1, rz0,rz1);

   i = p[ bx0 ];
   j = p[ bx1 ];

   b00 = p[ i + by0 ];
   b10 = p[ j + by0 ];
   b01 = p[ i + by1 ];
   b11 = p[ j + by1 ];

   t  = s_curve(rx0);
   sy = s_curve(ry0);
   sz = s_curve(rz0);

   q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
   q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
   a = lerp(t, u, v);

   q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
   q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
   b = lerp(t, u, v);

   c = lerp(sy, a, b);

   q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
   q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
   a = lerp(t, u, v);

   q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
   q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
   b = lerp(t, u, v);

   d = lerp(sy, a, b);

   return lerp(sz, c, d);
}

// "alpha" is the weight when the sum is formed.
// Typically it is 2, As this approaches 1 the function is noisier.
// "beta" is the harmonic scaling/spacing, typically 2.

double perlin(t_vector inter, double alpha, double beta, int n)
{
   int i;
   double val;
   double scale;
   double sum;
   double p[3] = {inter.x, inter.y, inter.z};
   int bois = 1;//

   scale = 1;
   i = 0;
   sum = 0;
   while (i < n)
   {
      val = noise(p);
      sum += val / scale;
      scale *= alpha;
      inter.x *= beta;
      inter.y *= beta;
      inter.z *= beta;
      i++;
   }

	if (bois == 1)
	{
		double g = sum * 20;
		double grains = g - (int)g;
		return (grains);
	}
	// else if (bois == 2)
	// {
	// 	double bosses = perlin (x * 50, y * 50, z * 20)
	// 	if (bosses < 0.5)
	// 		bosses = 0
	// 	else
	// 		bosses = 1 * t;
	// }

   return (sum);
}




//_________________________________________________________________________________________________________________________


// float perlin(float x, float y, float res)
// {
//     float tempX,tempY;
//     int x0,y0,ii,jj,gi0,gi1,gi2,gi3;
//     float unit = 1.0f/sqrt(2);
//     float tmp,s,t,u,v,Cx,Cy,Li1,Li2;
//     float gradient2[][2] = {{unit,unit},{-unit,unit},{unit,-unit},{-unit,-unit},{1,0},{-1,0},{0,1},{0,-1}};
//
//     unsigned int perm[] =
//        {151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,
//         142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,
//         203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,
//         74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,
//         105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,
//         187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,
//         64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
//         47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,
//         153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,
//         112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,
//         235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,
//         127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,
//         156,180};
//
//     //Adapter pour la résolution
//     x /= res;
//     y /= res;
//
//     //On récupère les positions de la grille associée à (x,y)
//     x0 = (int)(x);
//     y0 = (int)(y);
//
//     //Masquage
//     ii = x0 & 255;
//     jj = y0 & 255;
//
//     //Pour récupérer les vecteurs
//     gi0 = perm[ii + perm[jj]] % 8;
//     gi1 = perm[ii + 1 + perm[jj]] % 8;
//     gi2 = perm[ii + perm[jj + 1]] % 8;
//     gi3 = perm[ii + 1 + perm[jj + 1]] % 8;
//
//     //on récupère les vecteurs et on pondère
//     tempX = x-x0;
//     tempY = y-y0;
//     s = gradient2[gi0][0]*tempX + gradient2[gi0][1]*tempY;
//
//     tempX = x-(x0+1);
//     tempY = y-y0;
//     t = gradient2[gi1][0]*tempX + gradient2[gi1][1]*tempY;
//
//     tempX = x-x0;
//     tempY = y-(y0+1);
//     u = gradient2[gi2][0]*tempX + gradient2[gi2][1]*tempY;
//
//     tempX = x-(x0+1);
//     tempY = y-(y0+1);
//     v = gradient2[gi3][0]*tempX + gradient2[gi3][1]*tempY;
//
//
//     //Lissage
//     tmp = x-x0;
//     Cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
//
//     Li1 = s + Cx*(t-s);
//     Li2 = u + Cx*(v-u);
//
//     tmp = y - y0;
//     Cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
//
//     return (Li1 + Cy * (Li2 - Li1));
// }
