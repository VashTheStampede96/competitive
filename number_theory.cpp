
/*
 * Compute gcd(a, b) AND {x, y} s.t. ax + by = GCD(a, b)
 * Pre-condition: a < b
 */

template<class T>
std::vector<T> extended_euclid(T a, T b)
{
	if(a == 0)
		return {b, 0, 1};
	auto rec = extended_euclid(b%a, a);
	T gcd = rec[0],
	  y   = rec[1],
	  x   = rec[2];
	return {gcd, x-(b/a)*y, y};
}

/*
 * Compute x s.t. ax = 1 (mod m)
 * Pre-condition: GCD(a, m)=1
 */

template<class T>
T inverse_modulo(T a, T m)
{
	return (extended_euclid(a, m)[1] + m) % m;
}
