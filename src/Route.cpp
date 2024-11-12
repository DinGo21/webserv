/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:44:49 by diego             #+#    #+#             */
/*   Updated: 2024/11/04 09:09:51 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Route.hpp"

Route::Route(): _id(0), _autoindex(0) {}

Route::Route(const uint id, const std::string &modifier) : _id(id), _modifier(modifier)
{

}

Route::~Route() {}
