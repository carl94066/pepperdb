#include "common.h"

namespace tdb {

hash<string> string_hash;

// src_uid and predicate.
typedef pair<size_t, size_t> Key;
typedef set<size_t> UIDSet;

struct PairHash {
 public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

bool IsEnclosed(const string& s) {
  if (s.length() < 2) {
    return false;
  }
  return (s[0] == '<') && (s[s.length() - 1] == '>');
}

bool ParseRDF(const string& s, string* src, string* typ, string* dst,
              bool* is_value) {
  *is_value = false;
  istringstream is(s);

  // Read src entity.
  if (!(is >> *src)) {
    return false;
  }
  CHECK(IsEnclosed(*src));

  // Read edge type.
  if (!(is >> *typ)) {
    return false;
  }
  CHECK(IsEnclosed(*typ));

  // Read dst entity or value.
  if (!(is >> *dst)) {
    return false;
  }
  *is_value = !IsEnclosed(*dst);
  return true;
}

unordered_map<Key, UIDSet, PairHash> store_uid;
unordered_map<Key, string, PairHash> store_value;

void LoadFile(istream* is) {
  string line, src, typ, dst;
  bool is_value;
  while (std::getline(*is, line)) {
    CHECK(ParseRDF(line, &src, &typ, &dst, &is_value)) << line;

    const size_t src_uid = string_hash(src);
    const size_t pred = string_hash(typ);
    const Key key{src_uid, pred};
    if (!is_value) {
      const size_t dst_uid = string_hash(dst);
      auto v = store_uid.find(key);
      if (v != store_uid.end()) {
        v->second.insert(dst_uid);
      } else {
        CHECK(store_uid.insert({key, UIDSet()}).second) << line;
      }
    } else {
      store_value[key] = dst;
    }
  }
  LOG(INFO) << "Len(store_value)=" << store_value.size();
  LOG(INFO) << "Len(store_uid)=" << store_uid.size();
}

void DoMain() {
  const vector<string> filenames = {
    "freebasefilm/rdf-films",
    "freebasefilm/names",
  };
  for (const string& f : filenames) {
    LOG(INFO) << "Reading " << f;
    ifstream fin(f);
    LoadFile(&fin);
  }
}

}  // namespace tdb

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  tdb::DoMain();
}
