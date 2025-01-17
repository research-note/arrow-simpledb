#include <memory>

#include "columns/BaseColumnCursor.hpp"
#include "core/DBSchema.hpp"
#include "columns/ChunkedColumnCursor.hpp"
#include "columns/ChunkedDictColumnCursor.hpp"


namespace db {

template<typename T>
BaseColumnCursor<T>::BaseColumnCursor(TableCursor &table_cursor)
: GenericColumnCursor(table_cursor) {}

template<typename T>
std::shared_ptr<BaseColumnCursor<T>>
BaseColumnCursor<T>::makeCursor(
        std::shared_ptr<arrow::ChunkedArray> column, ColumnEncoding encoding, TableCursor &table_cursor)
{
    switch (encoding) {
        case db::ColumnEncoding::PLAIN: {
            return std::make_shared<ChunkedColumnCursor<T>>(column, table_cursor);
        }
        case db::ColumnEncoding::DICT: {
            return std::make_shared<ChunkedDictColumnCursor<T>>(column, table_cursor);
        }
        default:
            return std::make_shared<ChunkedColumnCursor<T>>(column, table_cursor);
    }
}

}

template class db::BaseColumnCursor<db::LongType>;
template class db::BaseColumnCursor<db::DoubleType>;
template class db::BaseColumnCursor<db::StringType>;