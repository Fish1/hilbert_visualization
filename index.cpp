#include <bitset>
#include <iostream>

#include "Hilbert.hpp"

int main(void)
{
	Hilbert h(4,5);

	for(int x = 0; x <= h.getMaxH(); ++x)
	{
		std::vector<int> v  = h.getCoordinate(x);

		std::cout << "x = " << x << std::endl;	
		for(int i : v)
			std::cout << i << " ";
		std::cout << std::endl;
		std::cout << std::endl;
	}
	std::cout << h.getMaxH() + 1 << std::endl;
}
