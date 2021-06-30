// SPDX-License-Identifier: MIT
// Copyright (c) 2021 ETH Zurich, Luc Grosheintz-Laval

#ifndef HAS_KEY_H_9TX4O
#define HAS_KEY_H_9TX4O

namespace zisa {

template <class Map, class Key>
auto has_key(const Map &map, const Key &key)
    -> decltype(map.find(key) != map.end()) {
  return map.find(key) != map.end();
}

} // namespace zisa

#endif
