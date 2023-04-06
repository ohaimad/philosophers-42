/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:46:07 by ohaimad           #+#    #+#             */
/*   Updated: 2023/04/06 20:14:19 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	ft_atoi(char *str)
{
	int		i;
	int		signe;
	int		res;

	res = 0;
	signe = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		res = res * 10;
		res = res + str[i] - '0';
		i++;
	}
	return (res * signe);
}
void	ft_design()
{
	printf("\033[1;31m");
	printf(" ______ _   _ _____ _     _____ \n");
	printf("| ___ \\ | | |_   _| |   |  _  |\n");
	printf("| |_/ / |_| | | | | |   | | | |\n");
	printf("|  __/|  _  | | | | |   | | | |\n");
	printf("| |   | | | |_| |_| |___\\ \\_/ /\n");
	printf("\\_|   \\_| |_/\\___/\\_____/\\___/ \n\n");
	printf("\033[0m");
}
