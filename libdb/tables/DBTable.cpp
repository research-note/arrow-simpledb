

#include "DBTable.h"

using arrow::Table;
using arrow::Field;

DBTable::DBTable(
        std::vector<std::string> names,
        std::vector<std::shared_ptr<db::DataType>> types,
        std::vector<db::ColumnEncoding> encodings)
{

    _encodings = encodings;

    std::vector<std::shared_ptr<arrow::Field>> schema_vector;

    for (uint64_t i = 0; i < names.size(); i++) {
        std::shared_ptr<db::DataType> tp = types.at(i);
        std::shared_ptr<Field> field = arrow::field(names.at(i), tp->getArrowType());
        db::ColumnEncoding encoding = encodings.at(i);
        schema_vector.push_back(field);

        switch (tp->id()) {
            case db::ColumnType::LONG_TYPE: {
                _builders.push_back(std::make_shared<DBColumnBuilder<db::LongType>>(field, encoding));
                break;
            }
            case db::ColumnType::DOUBLE_TYPE: {
                _builders.push_back(std::make_shared<DBColumnBuilder<db::DoubleType>>(field, encoding));
                break;
            }
            case db::ColumnType::STRING_TYPE: {
                _builders.push_back(std::make_shared<DBColumnBuilder<db::StringType>>(field, encoding));
                break;
            }
            default:
                // TODO: handle this
                break;
        }
    }

    _schema = std::make_shared<arrow::Schema>(schema_vector);

    // TODO: create column builders of the right type
}

void
DBTable::addRow(std::vector<std::shared_ptr<db::GenValue>> values)
{
    for (size_t i = 0; i < values.size(); i++) {
        _builders.at(i)->add(values.at(i));
    }
}

void
DBTable::endChunk()
{
    for (auto builder : _builders) {
        builder->endChunk();
    }
}

void
DBTable::make() {
    _columns.clear();
    for (auto builder : _builders) {
        _columns.push_back(builder->getColumn());
    }
    _table = std::make_shared<Table>(_schema, _columns);
}

std::shared_ptr<ScanTableCursor>
DBTable::getScanCursor()
{
    std::shared_ptr<ScanTableCursor> tc = std::make_shared<ScanTableCursor>(_table, _encodings);
    return tc;
}

std::shared_ptr<arrow::Table>
DBTable::getTable()
{
    return _table;
}

