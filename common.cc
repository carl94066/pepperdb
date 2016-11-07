#include "common.h"

namespace tdb {

// HasPrefix returns whether a begins with b.
bool HasPrefix(const string& a, const string& b) {
  return b.length() <= a.length() &&
         equal(b.begin(), b.end(), a.begin());
}

}  // namespace tdb
