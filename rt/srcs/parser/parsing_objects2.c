/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 17:12:34 by svelhinh          #+#    #+#             */
/*   Updated: 2016/06/12 15:13:19 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parsing_material_textures(t_env *rt, t_material *materials, int i)
{
	materials->procedural.active = rt->materials[i].procedural.active;
	materials->procedural.scale = rt->materials[i].procedural.scale;
	materials->procedural.color1 = rt->materials[i].procedural.color1;
	materials->procedural.color2 = rt->materials[i].procedural.color2;
	materials->texture.width = rt->materials[i].texture.width;
	materials->texture.height = rt->materials[i].texture.height;
	materials->texture.scale = rt->materials[i].texture.scale;
	materials->texture.row = rt->materials[i].texture.row;
	materials->texture.path = ft_strdup(rt->materials[i].texture.path);
	materials->texture.buffer = rt->materials[i].texture.buffer;
	materials->texture.alpha = rt->materials[i].texture.alpha;
}

void		parsing_material(t_env *rt, t_material *materials, char *material)
{
	int i;

	i = 0;
	while (i < rt->nbmat)
	{
		if (!ft_strcmp(material, rt->materials[i].name))
		{
			materials->specular = rt->materials[i].specular;
			materials->specular_power = rt->materials[i].specular_power;
			materials->shiny = rt->materials[i].shiny;
			materials->transparent = rt->materials[i].transparent;
			materials->reflection = rt->materials[i].reflection;
			materials->refraction = rt->materials[i].refraction;
			materials->i_refract = rt->materials[i].i_refract;
			materials->ripple = rt->materials[i].ripple;
			parsing_material_textures(rt, materials, i);
			return ;
		}
		i++;
	}
	ft_exit("\033[31mA defined material doesn't exist\n");
}

void		missing_parameter_obj(char **tab)
{
	if (((!ft_strcmp(tab[0], "radius") ||
	!ft_strcmp(tab[0], "material") || !ft_strcmp(tab[0], "separation")) &&
	(!tab[2] || tab[3])) || ((!ft_strcmp(tab[0], "pos") ||
	!ft_strcmp(tab[0], "color") || !ft_strcmp(tab[0], "angle")) &&
	(!tab[2] || !tab[3] || !tab[4] || tab[5])) || ft_strcmp(tab[1], ":"))
		ft_exit("\033[31mWrong format for an object\n");
}
