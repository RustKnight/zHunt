#include "spr_sqn.h"

ostream & spr_sqn::operator<<(ostream & os)
{
	{

		os << "x: " << x << endl;
		os << "y: " << y << endl;
		os << "w: " << w << endl;
		os << "h: " << h << endl << endl;

		return os;

	}
}
