#include <arrow/api.h>

#include "filters/AndFilter.hpp"

using namespace db;

AndFilter::AndFilter(std::shared_ptr<Filter> left, std::shared_ptr<Filter> right)
        : _left(left), _right(right)
{

}

void
AndFilter::initialize(TableCursor& table_cursor) {
    _left->initialize(table_cursor);
    _right->initialize(table_cursor);
}

bool
AndFilter::evaluate()
{
    // short circuit explicitly
    if (_left->evaluate()) {
        return _right->evaluate();
    } else {
        return false;
    }
}
