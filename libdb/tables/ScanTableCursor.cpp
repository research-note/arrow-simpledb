
#include "ScanTableCursor.h"

ScanTableCursor::ScanTableCursor(std::shared_ptr<arrow::Table> table)
: _table(table)
{
    for (int i = 0; i < table->num_columns(); i++) {
        addColumn(table->column(i));
    }
    _size = (uint64_t) table->num_rows();
    reset();
}

std::shared_ptr<GenericColumnCursor>
ScanTableCursor::getColumn(std::string colName)
{
    if (_cursors.count(colName) == 0) return nullptr;
    return _cursors[colName];
}

bool
ScanTableCursor::addColumn(std::shared_ptr<arrow::Column> column)
{
    switch (column->type()->id()) {
        case arrow::Type::INT64: {
            std::shared_ptr<BaseColumnCursor<arrow::Int64Type>> chunked =
                    std::make_shared<ChunkedColumnCursor<arrow::Int64Type>>(column);

            std::shared_ptr<ColumnCursorWrapper<arrow::Int64Type>> wrapper =
                    std::make_shared<ColumnCursorWrapper<arrow::Int64Type>>(chunked, *this);

            _cursors[column->name()] = wrapper;


            return true;
        }
        case arrow::Type::DOUBLE: {
            std::shared_ptr<ChunkedColumnCursor<arrow::DoubleType>> chunked =
                    std::make_shared<ChunkedColumnCursor<arrow::DoubleType>>(column);

            std::shared_ptr<ColumnCursorWrapper<arrow::DoubleType>> wrapper =
                    std::make_shared<ColumnCursorWrapper<arrow::DoubleType>>(chunked, *this);

            _cursors[column->name()] = wrapper;

            return true;
        }
        default:
            return false;
    }
}

bool
ScanTableCursor::hasMore()
{
    if (_initial_state) {
        _initial_state = false;
        _position = 0;
        return true;
    }
    if ((_position + 1) >= _size) return false;
    _position++;
    return true;
}

void
ScanTableCursor::reset()
{
    _position = 0;
    _initial_state = true;
    for (auto cursor =_cursors.begin(); cursor != _cursors.end(); cursor++) {
        cursor->second->reset();
    }
}

uint64_t
ScanTableCursor::getPosition()
{
    return _position;
}

