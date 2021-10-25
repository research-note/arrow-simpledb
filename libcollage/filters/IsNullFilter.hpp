#ifndef IS_NULL_FILTER_H
#define IS_NULL_FILTER_H

#include <string>

#include "filters/Filter.hpp"
#include "tables/TableCursor.hpp"
#include "columns/BaseColumnCursor.hpp"

namespace db {

    class IsNullFilter : public Filter {
        public:

            explicit IsNullFilter(std::string column_name);

            void initialize(TableCursor &table_cursor) override;

            bool evaluate() override;

        private:

            std::string _column_name;

            std::shared_ptr <GenericColumnCursor> _cursor;

    };
};


#endif //IS_NULL_FILTER_H
