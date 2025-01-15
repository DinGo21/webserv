/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:44:49 by diego             #+#    #+#             */
/*   Updated: 2025/01/15 15:20:07 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Route.hpp"

Route::Route(): _path(), _index(), _root(), _redir(), _methods(), _autoindex() {}

Route::~Route() {}

// Route::Route(const Route &route): Server(route)
// {
// 	*this = route;
// }

// Route::~Route() {}
