#include<bits/stdc++.h>

/*
 * templated Fenwick Tree data structure.
 * 1) fenwick_tree<T>     (e.g. T=int) default functor is std::plus<T>
 * 2) fenwick_tree<T, F>  F is a new functor (e.g. F=max functor)
 * 		in this case it could be useful change the __default_ans (otherwise is 0)
 */

template<class T, class F=std::plus<T>>
class fenwick_tree {
private:
	int __size;
	T __default_ans;
	std::vector<T> __fenwick;

	F __apply;

public:

	fenwick_tree() { }
	fenwick_tree(int);

	T query(int);
	void update(int, T);
	void set_default(T def){ __default_ans = def; }

};

template<class T, class F>
fenwick_tree<T, F>:: fenwick_tree(int n) : __size(n+1), __fenwick(std::vector<T>(n+1)) { }

template<class T, class F>
T fenwick_tree<T, F>:: query(int pos)
{
	T ans = __default_ans;
	while(pos > 0) {
		ans = __apply(ans, __fenwick[pos]);
		pos -= (pos & -pos);
	}

	return ans;
}

template<class T, class F>
void fenwick_tree<T, F>:: update(int pos, T value)
{
	while(pos < __size) {
		__fenwick[pos] = __apply(__fenwick[pos], value);
		pos += (pos & -pos);
	}
}

/*
 * ****************************************************************
 * Driver program
 */

int main()
{
	int n, q;
	std::cin >> n >> q;

	fenwick_tree<double> fen1(n);

	class Max {
	public:
		double operator()(const double& x, const double& y) const {
			return x > y ? x : y;
		}
	};
	fenwick_tree<double, Max> fen2(n);

	for(int i=0; i<q; ++i) {
		int t;
		std::cin >> t;
		if(t == 0) {
			int pos;
			double value;
			std::cin >> pos >> value;
			fen1.update(pos, value);
			fen2.update(pos, value);
		}else {
			int pos;
			std::cin >> pos;
			std::cout << fen1.query(pos) << " " << fen2.query(pos) << "\n";
		}
	}
	
	return 0;
}
