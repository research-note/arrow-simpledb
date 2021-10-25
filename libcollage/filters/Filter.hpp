#ifndef FILTER_H
#define FILTER_H

namespace db {

    class TableCursor;

    class Filter {

    public:

        virtual void initialize(TableCursor &table_cursor) = 0;

        virtual bool evaluate() = 0;

        virtual ~Filter() = default;
    };

};

#endif // FILTER_H

