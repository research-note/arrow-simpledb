

#ifndef DB_SCHEMA_H
#define DB_SCHEMA_H

#include <arrow/api.h>

namespace db {

    /**
     * THe data type of a column
     */
    enum ColumnType {
        STRING_TYPE, LONG_TYPE, DOUBLE_TYPE
    };

    /**
     * Encoding scheme for a column
     */
    enum ColumnEncoding { PLAIN = 0, DICT };

    /**
     * Common base class for type fo a column
     */
    class DataType {
    public:
        virtual ~DataType() = default;
        /**
         * Column type ID for switch statements
         * @return
         */
        virtual ColumnType id() = 0;

        /**
         * The corresponding Arrow datatype for a column
         * @return
         */
        virtual std::shared_ptr<arrow::DataType> getArrowType() = 0;
    };

    /**
     * String column type
     */
    class StringType : public DataType {
    public:
        typedef typename arrow::StringArray ArrayType;
        typedef std::string ElementType;
        typedef arrow::StringBuilder BuilderType;
        typedef arrow::StringDictionaryBuilder DictionaryBuilderType;
        const ColumnType TYPE_ID = ::db::STRING_TYPE;
        ColumnType id() override { return TYPE_ID; };
        std::shared_ptr<arrow::DataType> getArrowType() override { return arrow::utf8(); }
    };

    /**
     * (64 bit) Long column type
     */
    class LongType : public DataType  {
    public:
        typedef typename arrow::NumericArray<arrow::Int64Type> ArrayType;
        typedef typename arrow::Int64Type::c_type ElementType;
        typedef arrow::Int64Builder BuilderType;
        typedef arrow::DictionaryBuilder<arrow::Int64Type> DictionaryBuilderType;
        const ColumnType TYPE_ID = ::db::LONG_TYPE;
        ColumnType id() override { return TYPE_ID; };
        std::shared_ptr<arrow::DataType> getArrowType() override { return arrow::int64(); }
    };

    /**
     * Double precision column type.
     */
    class DoubleType : public DataType  {
    public:
        typedef typename arrow::NumericArray<arrow::DoubleType> ArrayType;
        typedef typename arrow::DoubleType::c_type ElementType;
        typedef arrow::DoubleBuilder BuilderType;
        // TODO: what if there _is_ no corresponding dictionary type ???
        typedef arrow::DoubleBuilder DictionaryBuilderType;
        const ColumnType TYPE_ID = ::db::DOUBLE_TYPE;
        ColumnType id() override { return TYPE_ID; };
        std::shared_ptr<arrow::DataType> getArrowType() override { return arrow::float64(); }
    };

    /**
     * Create a string type element (for specifying a table type)
     * @return
     */
    std::shared_ptr<DataType> string_type();

    /**
     * Create a long type element (for specifying a table type)
     * @return
     */
    std::shared_ptr<DataType> long_type();

    /**
     * Create a double precision type element (for specifying a table type)
     * @return
     */
    std::shared_ptr<DataType> double_type();

};


#endif //DB_SCHEMA_H
