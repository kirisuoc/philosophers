/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecousill <ecousill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:06:37 by ecousill          #+#    #+#             */
/*   Updated: 2024/12/13 16:24:16 by ecousill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	print_timestamp(void)
{
	// imprime la diferencia de tiempo entre cuando se ejecutó el programa y cuando se llama esta función
}

long	get_timestamp(void)
{
	struct	timeval start;
	struct	timeval end;
	long	seconds;
	long	microseconds;
	long	milliseconds;


}

void	funcion_x(void)
{
	struct	timeval start;
	struct	timeval end;
	long	seconds, microseconds;
	long	milliseconds;
	int		counter = 0;

	gettimeofday(&start, NULL);

	for (int i = 0; i < 10000000; i++)
	{
		counter++;
	}

	gettimeofday(&end, NULL);

	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	milliseconds = seconds * 1000 + microseconds / 1000;

	printf("Tiempo transcurrido: %ld milliseconds\n", milliseconds);

}

int	main(void)
{
	/* if (ac == 1)
		return (0); */
	funcion_x();
	return (0);
}
