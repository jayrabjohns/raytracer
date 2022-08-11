#include "colour.h"

void Colour::WriteColour(std::ostream& out, colour colour)
{
	out << static_cast<int>(255.999 * colour.x()) << ' '
		<< static_cast<int>(255.999 * colour.y()) << ' '
		<< static_cast<int>(255.999 * colour.z()) << '\n';
}
