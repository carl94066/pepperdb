#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>

namespace tdb {

using std::istream;
using std::ifstream;
using std::unique_ptr;
using std::istringstream;
using std::string;
using std::equal;
using std::hash;
using std::set;
using std::map;
using std::unordered_set;
using std::unordered_map;
using std::pair;
using std::vector;

using std::cin;
using std::cout;

bool HasPrefix(const string& a, const string& b);

}  // namespace tdb

