/*
 * datatypes.cpp
 *
 *  Created on: Aug 25, 2013
 *      Author: Alles Rebel
 */

#include "datatypes.h"

/*
 * Get magnitude of a 2D vector
 */
float Vec2::getMagnitude() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

/*
 * Both important comparison operators == and !=
 */
bool Vec2::operator ==(const Vec2& rhs) {
	if (this->x - rhs.x >= FLT_EPSILON)
		return false;
	if (this->y - rhs.y >= FLT_EPSILON)
		return false;
	return true;
}
bool Vec2::operator !=(const Vec2& rhs) {
	if (this->x - rhs.x >= FLT_EPSILON)
		return true;
	if (this->y - rhs.y >= FLT_EPSILON)
		return true;
	return false;
}
