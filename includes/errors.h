/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:43:42 by coverand          #+#    #+#             */
/*   Updated: 2022/06/24 16:48:36 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ARGS_COUNT_FAILURE		"MiniRT: wrong number of arguments."
# define WRONG_EXTENSION		"MiniRT: wrong extension."
# define MAP_ERROR_UNKNOWN_ID	"MiniRT: map error - unknown identifier."
# define MAP_ERROR_WRONG_INP	"MiniRT: map error - wrong input."
# define MAP_ERROR_DUPLICATE_A  "Ambient lightning can only be declared once."
# define MAP_ERROR_DUPLICATE_C  "Camera can only be declared once."
# define MAP_ERROR_DUPLICATE_L  "Light can only be declared once."
# define AMBIENT_RATIO_RANGE_ER "Ambient lighting ratio should be \
in range [0.0,1.0]"
# define RGB_COLORS_RANGE_ERR   "R,G,B colors should be in range [0-255]."
# define ORIENTATION_VECTOR_ERR " Orientation vector: \
range [-1,1] for each x,y,z axis."
# define FOV_RANGE_ERR          "FOV in degrees should be in range [0,180]."
# define BRIGHTNESS_RATIO_RANGE "Brightness ratio should be in range [0.0,1.0]."

#endif
