

#include "FilterProjectTableCursor.h"
#include "filters/Filter.h"
#include "columns/ColumnCursorWrapper.h"

FilterProjectTableCursor::FilterProjectTableCursor(TableCursor &source_cursor, std::shared_ptr<Filter> &filter)
        : _source_cursor(source_cursor), _filter(filter)
{
    reset();
    filter->initialize(*this);
}

std::shared_ptr<ColumnCursorWrapper<arrow::StringType>>
FilterProjectTableCursor::getStringColumn(std::string colName)
{
    return std::dynamic_pointer_cast<ColumnCursorWrapper<arrow::StringType>>(_source_cursor.getStringColumn(colName));
}

std::shared_ptr<ColumnCursorWrapper<arrow::Int64Type>>
FilterProjectTableCursor::getLongColumn(std::string colName)
{
    return std::dynamic_pointer_cast<ColumnCursorWrapper<arrow::Int64Type>>(_source_cursor.getLongColumn(colName));
}

std::shared_ptr<ColumnCursorWrapper<arrow::DoubleType>>
FilterProjectTableCursor::getDoubleColumn(std::string colName)
{
    return std::dynamic_pointer_cast<ColumnCursorWrapper<arrow::DoubleType>>(_source_cursor.getDoubleColumn(colName));
}

bool
FilterProjectTableCursor::hasMore()
{
    while (_source_cursor.hasMore()) {
        if (satisfiesFilter()) return true;
    }
    return false;
}

void FilterProjectTableCursor::reset()
{
    _source_cursor.reset();
}

uint64_t
FilterProjectTableCursor::getPosition()
{
    return _source_cursor.getPosition();
}

bool
FilterProjectTableCursor::satisfiesFilter()
{
    return _filter->evaluate();
}