/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:03:03 by disantam          #+#    #+#             */
/*   Updated: 2024/12/20 11:10:01 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

uint	config_check_brackets(std::vector<std::string> &args, size_t i)
{
	uint	f = 1;

	if (i < args.size() && args[i][0] != '{')
		return 0;
	i++;
	while (i < args.size() && f != 0)
	{
		if (args[i][0] == '{')
			f++;
		if (args[i][0] == '}')
			f--;
		i++;
	}
	if (f != 0)
		return 0;
	return 1;
}
