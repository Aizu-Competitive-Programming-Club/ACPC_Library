#pragma once

#include <bits/stdc++.h>
using namespace std;

// library section
class DisjointSetUnion {
	using isize = ptrdiff_t;
	using usize = size_t;
	size_t n_;

	vector<ptrdiff_t> vals_;
	void bound_check(size_t v) const{
		assert(v < n_);
	}
	
	size_t impl_leader(size_t v){
		if( vals_[v] < 0 ) return v;
		return vals_[v] = leader(vals_[v]);
	}

	public:
		DisjointSetUnion() = default;
		explicit DisjointSetUnion(size_t n) : n_(n), vals_(n,-1){}

		size_t size() const{
			return n_;
		}
		
		size_t leader(size_t v){
			bound_check(v);
			return impl_leader(v);
		}
		
		bool same(size_t u, size_t v){
			bound_check(u),bound_check(v);
			return impl_leader(u) == impl_leader(v);
		}

		
		size_t merge(size_t u, size_t v){
			bound_check(u);
			bound_check(v);

			ptrdiff_t x = impl_leader(u);
			ptrdiff_t y = impl_leader(v);

			if(x == y) return x;
			if(-vals_[x] < -vals_[y]) swap(x,y);
			vals_[x] += vals_[y];
			vals_[y] = x;
			return x;
		}

		
		size_t group_size(size_t v){
			bound_check(v);
			return -vals_[impl_leader(v)];
		}
		
		vector<vector<size_t>> groups() {
			vector<vector<size_t>> result(n_);
			vector<size_t> leaders(n_), g_size(n_);

			for(size_t v = 0; v<n_; v++){
				leaders[v] = impl_leader(v);
				g_size[leaders[v]]++;
			}
			for(size_t v = 0; v < n_; v++){
				result[v].reserve(g_size[v]);
			}
			for(size_t v = 0; v  < n_; v++){
				result[leaders[v]].emplace_back(v);
			}
			auto empty_check = [](const vector<size_t> &vs){
				return vs.empty();
			};
			result.erase(
			remove_if(result.begin(), result.end(), empty_check),
			result.end());

			return result;
		}
};
//library section
