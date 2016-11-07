#pragma once

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>

typedef boost::shared_mutex Lock;
typedef boost::unique_lock<Lock> WriteLock;
typedef boost::shared_lock<Lock> ReadLock;

#include <gflags/gflags.h>
#include <glog/logging.h>

namespace pepper {

using std::cin;
using std::cout;
using std::equal;
using std::hash;
using std::istream;
using std::ifstream;
using std::istringstream;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::unique_ptr;
using std::unordered_set;
using std::unordered_map;
using std::vector;

bool HasPrefix(const string& a, const string& b);

}
