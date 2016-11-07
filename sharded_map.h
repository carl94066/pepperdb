#pragma once

#include "common.h"

namespace pepper {

template<class K, class V>
class MapShard {
 public:
  MapShard() {}

  int size() const {
    ReadLock r_lock(lock_);
    return data_.size();
  }

 private:
  unordered_map<K, V> data_;
  Lock lock_;
};

template<class K, class V>
class ShardedMap {
 public:
  // n is number of shards.
  ShardedMap(size_t n) {
    shard_.resize(n);
  }

  size_t size() const {
    size_t out = 0;
    for (int i = 0; i < shard_.size(); ++i) {
      out += shard_[i].size();
    }
    return out;
  }

 private:
  vector<MapShard<K, V>> shard_;
};

}
