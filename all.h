#ifndef __MYlIB_H_
#define __MYlIB_H_

#include <cassert>
#include <cerrno>
#include <cfloat>
#include <climits>
#include <cstdalign>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>
#include <system_error>
#include <typeinfo>

#if __has_include(<string_view>)
#include <string_view>
#endif

#include <algorithm>
#include <array>
#include <cfenv>
#include <cmath>
#include <deque>
#include <forward_list>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <streambuf>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#if __has_include(<filesystem>)
#include <filesystem>
#endif

#include <atomic>
#include <cinttypes>
#include <condition_variable>
#include <cstdio>
#include <filesystem>
#include <future>
#include <mutex>
#include <regex>
#include <shared_mutex>
#include <thread>

#include "cblas.h"
#include "lapacke.h"

void printmat(int n, double* A);
void fprintmat(FILE* file, int n, double* A);
void printvec(int n, double* B);
void fprintvec(FILE* file, int n, double* B);
void print2dvec(int n, double** C);
void fprint2dvec(FILE* file, int n, double** C);
void calc_ab(FILE* file, int n, double* A, double* eigenv);
void gso(int n, int k, double** u);
void sdz(int n, double* v);
void make_mat(int n, double* A);
#endif