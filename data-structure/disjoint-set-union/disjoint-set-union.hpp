#pragma once

#include <bits/stdc++.h>
using namespace std;

// library section
class DisjointSetUnion {
  int n;
  vector<int> vals;

  public:
    DisjointSetUnion() = default;
    explicit DisjointSetUnion(int n) : n(n), vals(n,-1){}


    int leader(int v){
      assert(v < n);
      if(vals[v] < 0) return v;
      return vals[v] = leader(vals[v]);
    }
    
    bool same(int u, int v){
      assert(v < n);
      assert(u < n);
      return leader(u) == leader(v);
    }

    
    int merge(int u, int v){
      assert(u < n);
      assert(v < n);

      int x = leader(u);
      int y = leader(v);

      if(x == y) return x;
      if(-vals[x] < -vals[y]) swap(x,y);
      vals[x] += vals[y];
      vals[y] = x;
      return x;
    }

    
    int group_size(int v){
      assert(v < n);
      return -vals[leader(v)];
    }
    
    vector<vector<int>> groups() {
      vector<vector<int>> result(n);
      vector<int> leaders(n), g_size(n);

      for(int v = 0; v<n; v++){
        leaders[v] = leader(v);
        g_size[leaders[v]]++;
      }
      for(int v = 0; v < n; v++){
        result[v].reserve(g_size[v]);
      }
      for(int v = 0; v  < n; v++){
        result[leaders[v]].emplace_back(v);
      }
      auto empty_check = [](const vector<int> &vs){
        return vs.empty();
      };
      result.erase(
      remove_if(result.begin(), result.end(), empty_check),
      result.end());

      return result;
    }
    // === no need to implement form here ===
};
//library section
