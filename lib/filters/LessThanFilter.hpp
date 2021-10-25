#ifndef LESSTHANFILTER_H
#define LESSTHANFILTER_H

#include <string>
#include "filters/Filter.hpp"
#include "tables/TableCursor.hpp"
#include "columns/BaseColumnCursor.hpp"

namespace db {

    template<typename T>
    class LessThanFilter : public Filter {
    public:

        LessThanFilter(std::string column_name, typename T::ElementType value);

        void initialize(TableCursor &table_cursor) override;

        bool evaluate() override;

    private:

        std::string _column_name;

        double _value;

        std::shared_ptr<BaseColumnCursor<T>> _cursor;
    };

};

#endif // LESSTHANFILTER_H
