
# A Simple In-Memory Database Using Apache Arrow

[Apache Arrow](https://arrow.apache.org/) provides a uniform in-memory columnar representation for data, and
a convenient set of C++ APIs (among others) for working with that representation.

This project explores how an extremely simple database query engine might be implemented on top of Arrow,
and thus how the complexities of Arrow's table and column representation (such as chunked columns) may be
abstracted away so that most of the query engine is oblivious to them. Of course, an important goal is to
preserve Arrow's performance advantages.

Iterators (here called table cursors) are used to process queries against tables.

# Queries Over Arrow Tables

The unit tests show how simple queries can be executed against tables created through Arrow APIs.

For example, a scan cursor can be used to simply scan a table:

    std::shared_ptr<Table> table = ... ; // create an Arrow table
    ScanTableCursor tc(table); // define a cursor to scan the entire table

    // get pointers to two columns named "id" and "cost"
    auto id_cursor =
        std::dynamic_pointer_cast<ColumnCursorWrapper<arrow::Int64Array>>(
                tc.getColumn(std::string("id")));
    auto cost_cursor =
        std::dynamic_pointer_cast<ColumnCursorWrapper<arrow::DoubleArray>>(
                tc.getColumn(std::string("cost")));

    // iterate through the table and print it
    while (tc.hasMore()) { // advances cursor -- must be called before first element
        std::print << "Row = " << tc.getPosition() <<
            ", id = " << id_cursor->get() <<
            ", cost = " << cost_cursor.get() <<
            std::endl;
        //
    }

Note that column cursors are automatically positioned by the table cursor positioned when accessed,
so any column (or part of a column) that is not needed for a query will not receive any memory accesses
when the query is executed.

Additionally, a filtering and projection cursor can be composed to fetch certain rows:

    ScanTableCursor tc(table);

    std::shared_ptr<Filter> leftFilter =
        std::make_shared<GreaterThanFilter<arrow::Int64Array>>("id", 31);
    std::shared_ptr<Filter> rightFilter =
        std::make_shared<GreaterThanFilter<arrow::DoubleArray>>("cost", 100);
    std::shared_ptr<Filter> andFilter =
            std::make_shared<AndFilter>("id", leftFilter, rightFilter);

    FilterProjectTableCursor fptc(tc, andFilter);

    // Note: the column cursors must always be obtained from the appropriate table cursor
    auto id_cursor =
        std::dynamic_pointer_cast<ColumnCursorWrapper<arrow::Int64Array>>(
            fptc.getColumn(std::string("id")));
    auto cost_cursor =
        std::dynamic_pointer_cast<ColumnCursorWrapper<arrow::DoubleArray>>(
            fptc.getColumn(std::string("cost")));

    while (tc.hasMore()) {
        // ...
    }

Table cursors can be composed arbitrarily:

    ScanTableCursor tc(table);

    std::shared_ptr<Filter> first_filter =
        std::make_shared<GreaterThanFilter<arrow::Int64Array>>("id", 11);
    FilterProjectTableCursor first_cursor(tc, first_filter);

    std::shared_ptr<Filter> second_filter =
        std::make_shared<LessThanFilter<arrow::DoubleArray>>("cost", 42);
    FilterProjectTableCursor second_cursor(first_cursor, second_filter);

# Things Not Yet Investigated

* A cleaner way to create tables
* Encodings (dictionary, ...)
* Data representation
** Nulls
** Non-relational data
* A full range of column types (currently just int64 and double)
* Vectorized execution
* Parallelism

# Dependencies

* GCC (using 5.4.0)
* CMake (using 3.5.1)
* Apache Arrow (using 0.7.1)
* Googletest (using 1.8.0)

# Building

    $ mkdir <build root>
    $ cd <build root>
    $ cmake <source root> -DCMAKE_BUILD_TYPE=Debug -DGTEST_ROOT=<googletest root> -DARROW_ROOT=<arrow root>
    $ make clean
    $ make

# Running Tests

    $ <build root>/testdb/testdb


