#include <iostream>

#include <vector>

#include <bitset>

#include <cmath>

#include <climits>

#include <algorithm>

class Hilbert
{
private:
	// iterations to use in hilbert curve
	int p;
	// number of dimensions
	int n;

	// maximum distance along curve
	int max_h;

	// maximum coordinate value in any direction
	int max_x;

public:

	// Hilbert(int iterations, int dimension)	
	Hilbert(int p, int n)
	{
		if(p <= 0)
		{
			std::cout << "No" << std::endl;
		}

		if(n <= 0)
		{
			std::cout << "NO" << std::endl;
		}

		this->p = p;
		this->n = n;

		this->max_h = pow(2, p * n) - 1;
		this->max_x = pow(2, p) - 1;
	}

	int getMaxH()
	{
		return max_h;
	}
	
	std::string binary_repr(int n, int width)
	{
		std::string  result;
		int i = 0; 
		
		while(n > 0)
		{
			result.append(std::to_string(n % 2));
			n = n / 2;
			++i;
		}

		while(result.size() < width)
		{
			result.append(std::to_string(0));
		}

		std::reverse(result.begin(), result.end());

		return result;	
	}


	// h : distance along hilbert curve
	// return : transpose of h
			// (n components with values between 0 and 2^(p - 1)		
	std::vector<int> hilbert_integer_to_transpose(int h)
	{
		std::vector<int> result;
		
		std::string binary = binary_repr(h,p*n);

		for(int start = 0; start < n; ++start)
		{	
			std::string binary_transpose;
			for(int i = start; i < p*n; i += n)
			{
				char bit = binary[i];
				binary_transpose += bit;
			}
			
			int i = std::stoi(binary_transpose, nullptr, 2);

			result.push_back(i);
		}

		return result;
	}

	int traspose_to_hilbert_integer(std::vector<int> x)
	{

	}

	// h : distance along hilbert curve	
	std::vector<int> getCoordinate(int h)
	{
		if(h > max_h)
		{
			std::cout << "h to large: "  << h << std::endl;
			std::cout << "max h: " << max_h << std::endl;

			return {0,0};
		}
		
		if(h < 0)
		{
			std::cout << "h must be larger than 0" << std::endl;
			
			return {0,0};
		}

		std::vector<int> x = hilbert_integer_to_transpose(h);
	
		int Z = 2 << (p - 1);

		// gray decode by H ^ (H/2)
		int t = x[n-1] >> 1;
		for(int i =  n - 1; i > 0; i -= 1)
		{
			x[i] = x[i] ^ x[i-1];
		}

		x[0] = x[0] ^ t;

		// undo excess work?
		int Q = 2;
		while(Q != Z)
		{

			int P = Q - 1;
			for(int i = n - 1; i > -1; i -= 1)
			{
				if(x[i] & Q)
				{
					x[0] = x[0] ^ P;
				}
				else
				{
					t = (x[0] ^ x[i]) & P;
					x[0] = x[0] ^ t;
					x[i] = x[i] ^ t;
				}
			}
			
			Q = Q << 1;
		}

		return x;
	}

	int getDistance(std::vector<int> x)
	{
		if(x.size() != n)
		{
			std::cout << "Coords are wrong dimension" << std::endl;
			return -1;
		}

		for(int i : x)
		{
			if(i > max_x || i < 0)
			{
				std::cout << "Coordinates out of domain" << std::endl;
				return -1;
			}
		}
			
		int M = 1 << (p - 1);
		
		int Q = M;

		while(Q > 1)
		{
			int P = Q - 1;
			for(int i = 0; i < n; ++i)
			{
				if(x[i] & Q)
					x[0] = x[0] ^ P;
				else
				{
					int t = (x[0] ^ x[i]) & P;
					x[0] = x[0] ^ t;
					x[i] = x[i] ^ t;
				}
			}
			Q = Q >> 1;
		}	

		//gray encode
		for(int i = 1; i < n; ++i)
		{
			x[i] = x[i] ^ x[i - 1];
		}
		
		int t = 0;
		Q = M;
		while(Q > 1)
		{
			if( x[n-1] & Q)
			{
				t = t ^ (Q - 1);
			}	
			Q = Q >> 1;
		}

		for(int i = 0; i < n; ++i)
		{
			x[i] = x[i] ^ t;
		}

		int h = transpose_to_hilbert_integer(x);
		return h;
	}

};
