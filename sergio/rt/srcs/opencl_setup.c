/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnieto-m <lnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 09:26:41 by lnieto-m          #+#    #+#             */
/*   Updated: 2016/05/20 11:32:21 by lnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cl_free(t_opencl *cl)
{
	clFinish(cl->commands);
	clReleaseMemObject(cl->image);
	clReleaseProgram(cl->program);
	clReleaseKernel(cl->kernel);
	clReleaseCommandQueue(cl->commands);
	clReleaseContext(cl->context);
}

void		cl_init(t_opencl *cl, char *source)
{
	int		err;

	err = clGetPlatformIDs(1, &cl->platform_id, NULL);
	err = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_ALL, 1, &cl->device_id, NULL);
	cl->context = clCreateContext(NULL, 1, &cl->device_id, NULL, NULL, &err);
	cl->program = clCreateProgramWithSource(cl->context, 1,
				(const char **)&source, NULL, &err);
	err = clBuildProgram(cl->program, 0, NULL, "", NULL, NULL);
	cl->commands = clCreateCommandQueue(cl->context, cl->device_id, 0, &err);
	cl->kernel = clCreateKernel(cl->program, "raytracer", &err);
}

char		*read_file(char *path)
{
	char	*source;
	char 	*line = NULL;
	char 	*tmp;
	char	*tmp2;
	int		fd;

	if (!(source = (char *)malloc(sizeof(char) * 1)))
		exit(1);
	ft_strclr(source);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(1);
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_strjoin(source, line);
		tmp2 = ft_strjoin(tmp, "\n");
		free(tmp);
		free(source);
		source = tmp2;
		free(line);
	}
	close(fd);
	return (source);
}

void		opencl_setup(t_opencl *cl, int height, int width)
{
	char	*source;

	source = read_file("./opencl/raytracer.cl");
	cl_init(cl, source);
	cl->image = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				sizeof(char) * height * width, NULL, NULL);
	if (!cl->image)
	free(source);
}
