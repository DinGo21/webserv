/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 08:47:34 by disantam          #+#    #+#             */
/*   Updated: 2025/02/25 08:51:27 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

bool	is_method(const std::string &str)
{
	if (str != "GET" && str != "POST" && str != "DELETE")
	{
		return (0);
	}
	return (1);
}
