#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <optional>
#include <vector>

using namespace std;

struct tree_node_t {
  shared_ptr<tree_node_t> parent;
  vector<shared_ptr<tree_node_t>> children;

  int32_t cx, cy, r;
};

bool check_is_in_circle(const int32_t &c1x, const int32_t &c1y,
                        const int32_t &c1r, const int32_t &c2x,
                        const int32_t &c2y, const int32_t &c2r) {
  if (c2r > c1r)
    return false;

  int32_t dx = c1x - c2x;
  int32_t dy = c1y - c2y;

  return dx * dx + dy * dy < c1r * c1r;
}

optional<shared_ptr<tree_node_t>>
find_minimum_node(const shared_ptr<tree_node_t> &node, int32_t cx, int32_t cy,
                  int32_t r) {
  if (!check_is_in_circle(node->cx, node->cy, node->r, cx, cy, r)) {
    return nullopt;
  }

  for (auto child : node->children) {
    auto maybe_node = find_minimum_node(child, cx, cy, r);
    if (maybe_node.has_value()) {
      return maybe_node.value();
    }
  }

  return node;
}

int32_t find_lowest_common_ancestor(const shared_ptr<tree_node_t> &root,
                                    const shared_ptr<tree_node_t> &start,
                                    const shared_ptr<tree_node_t> &end) {
  shared_ptr<tree_node_t> start_cursor = start, end_cursor = end;
  int32_t start_depth = 0, end_depth = 0, distance = 0;

  for (shared_ptr<tree_node_t> current = start;;) {
    if (current == root)
      break;

    current = current->parent;
    start_depth++;
  }

  for (shared_ptr<tree_node_t> current = end;;) {
    if (current == root)
      break;

    current = current->parent;
    end_depth++;
  }

  if (start_depth > end_depth) {
    while (start_depth != end_depth) {
      start_cursor = start_cursor->parent;
      start_depth--;
      distance++;
    }
  } else {
    while (start_depth != end_depth) {
      end_cursor = end_cursor->parent;
      end_depth--;
      distance++;
    }
  }

  while (start_cursor != end_cursor) {
    start_cursor = start_cursor->parent;
    end_cursor = end_cursor->parent;

    distance += 2;
  }

  return distance;
}

int main() {
  size_t t;
  ::scanf("%ld", &t);

  for (size_t iter = 0; iter < t; iter++) {
    int32_t x1, y1, x2, y2;
    ::scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    size_t n;
    ::scanf("%ld", &n);

    shared_ptr<tree_node_t> root_ptr = make_shared<tree_node_t>();
    root_ptr->parent = nullptr;
    root_ptr->children = {};
    root_ptr->cx = 0;
    root_ptr->cy = 0;
    root_ptr->r = 10000;

    for (size_t planetary_system_idx = 0; planetary_system_idx < n;
         planetary_system_idx++) {
      int32_t cx, cy, r;
      ::scanf("%d %d %d", &cx, &cy, &r);

      auto target_node = find_minimum_node(root_ptr, cx, cy, r)
                             .value(); // assuming due root has range of 10000.

      auto node_ptr = make_shared<tree_node_t>();
      node_ptr->parent = target_node;
      node_ptr->children = {};
      node_ptr->cx = cx;
      node_ptr->cy = cy;
      node_ptr->r = r;

      target_node->children.erase(
          remove_if(target_node->children.begin(), target_node->children.end(),
                    [&](shared_ptr<tree_node_t> element) {
                      if (check_is_in_circle(cx, cy, r, element->cx,
                                             element->cy, element->r)) {
                        node_ptr->children.push_back(element);
                        element->parent = node_ptr;
                        return true;
                      } else {
                        return false;
                      }
                    }),
          target_node->children.end());
      target_node->children.push_back(node_ptr);
    }

    auto start_node = find_minimum_node(root_ptr, x1, y1, 0).value();
    auto end_node = find_minimum_node(root_ptr, x2, y2, 0).value();

    int32_t result =
        find_lowest_common_ancestor(root_ptr, start_node, end_node);

    ::printf("%d\n", result);
  }
}
