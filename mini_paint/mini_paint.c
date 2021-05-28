/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:03:13 by exam              #+#    #+#             */
/*   Updated: 2021/05/28 15:03:16 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini_paint.h"

typedef struct	s_zone
{
	int		width;
	int		height;
	char	background;
}				t_zone;

typedef struct	s_shape
{
	char	type;
	float	x;
	float	y;
	float	radius;
	char	color;
}				t_shape;

int		ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

int		ft_clear(FILE *file, char *buffer)
{
	if (buffer)
		free(buffer);
	fclose(file);
	return (1);
}

int		ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

char	*get_zone(FILE *file, t_zone *zone)
{
	char	*buf;
	int		i = 0;

	if (fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background) != 3)
		return (NULL);
	if (zone->width <= 0 || zone->width > 300 || zone->height <= 0 || zone->height > 300)
		return (NULL);
	if (!(buf = (char *)malloc(sizeof(*buf) * (zone->width * zone->height))))
		return (NULL);
	while (i < zone->width * zone->height)
	{
		buf[i] = zone->background;
		i++;
	}
	return (buf);
}

int		in_circle(float x, float y, t_shape *shape)
{
	float	distance;

	distance = sqrtf(powf(x - shape->x, 2.) + powf(y - shape->y, 2.));
	if (distance <= shape->radius)
	{
		if (shape->radius - distance < 1.00000000)
			return (2);
		return (1);
	}
	return (0);
}

void	draw_shape(char *buffer, t_shape *shape, t_zone *zone)
{
	int		is_in = 0;
	int		x = 0;
	int		y = 0;

	while (y < zone->height)
	{
		x = 0;
		while (x < zone->width)
		{
			is_in = in_circle(x, y, shape);
			if ((shape->type == 'c' && is_in == 2) || (shape->type == 'C' && is_in))
				buffer[y * zone->width + x] = shape->color;
			x++;
		}
		y++;
	}
}

int		draw_shapes(FILE *file, char *buffer, t_zone *zone)
{
	int		ret = 0;
	t_shape	shape;

	while ((ret = fscanf(file, "%c %f %f %f %c\n", &shape.type, &shape.x, &shape.y, &shape.radius, &shape.color)) == 5)
	{
		if (shape.radius < 0.00000000 || (shape.type != 'c' && shape.type != 'C'))
			return (0);
		draw_shape(buffer, &shape, zone);
	}
	if (ret != -1)
		return (0);
	return (1);
}

void	draw_buffer(char *buffer, t_zone *zone)
{
	int	i = 0;

	while (i < zone->height)
	{
		write(1, buffer + (i * zone->width), zone->width);
		write(1, "\n", 1);
		i++;
	}
}

int		main(int argc, char *argv[])
{
	FILE	*file;
	char	*buffer;
	t_zone	zone;
	
	zone.width = 0;
	zone.height = 0;
	zone.background = 0;
	buffer = NULL;
	if (argc != 2)
		return (ft_error("Error: argument\n"));
	if (!(file = fopen(argv[1], "r")))
		return (ft_error("Error: Operation file corrupted\n"));
	if (!(buffer = get_zone(file, &zone)))
		return (ft_clear(file, buffer) && ft_error("Error: Operation file corrupted\n"));
	if (!(draw_shapes(file, buffer, &zone)))
		return (ft_clear(file, buffer) && ft_error("Error: Operation file corrupted\n"));
	draw_buffer(buffer, &zone);
	ft_clear(file, buffer);
	// while (1)
	// 	;
	return (0);
}