/*
 * Build obj linking with cc_library Util Class.
 *
 * Copyright Bazel organization
 *
 */

#ifndef EDGE_STORE_UTIL_HPP_
#define EDGE_STORE_UTIL_HPP_

#include <vector>
#include <optional>
#include <cstddef>

using namespace std;

template <typename T>
class Util
{
public:
	explicit Util();
	virtual ~Util() = default;

private:

};

#include "Util.cc"

#endif  // EDGE_STORE_UTIL_HPP_
