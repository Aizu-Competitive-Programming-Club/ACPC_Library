#pragma once

#include <bits/stdc++.h>
using namespace std;

// library section
template < class value_structure >
class SegmentTree {
  using V  = value_structure;
  using VT = typename V::value_type;

  vector< VT > tree;

  void evaluate(int index) {
    tree[index] = V::operation(tree[index << 1 | 0], tree[index << 1 | 1]);
  }

 public:
  using value_type = VT;

  SegmentTree() = default;

  explicit SegmentTree(const int n) : tree(n * 2, V::identity()) {}


  void build(const vector< VT > &vs) {
    int n = vs.size();
    assert(2 * n == tree.size());
    copy(vs.begin(), vs.end(), tree.begin() + n);
    for (int index = n; index > 0; index--) {
      evaluate(index);
    }
  }

  int size() const {
    return tree.size() / 2;
  }

  void set(int index, const VT x) {
    assert(0 <= index);
    assert(index < size());
    index += size();
    tree[index] = x;

    while (index != 1) {
      index >>= 1;
      evaluate(index);
    }
  }

  VT fold(int index) const {
    assert(0 <= index);
    assert(index < size());

    return tree[index + size()];
  }

  VT fold(int first, int last) const {
    assert(0 <= first);
    assert(first <= last);
    assert(last <= size());

    first += size();
    last += size();

    VT fold_l = V::identity();
    VT fold_r = V::identity();

    while (first != last) {
      if (first & 1) {
        fold_l = V::operation(fold_l, tree[first]);
        first += 1;
      }
      first >>= 1;

      if (last & 1) {
        last -= 1;
        fold_r = V::operation(tree[last], fold_r);
      }
      last >>= 1;
    }

    return V::operation(fold_l, fold_r);
  }

  VT fold_all() const {
    return (size() ? tree[1] : V::identity());
  }
};
// library section
