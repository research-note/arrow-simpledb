#ifndef DB_SCHEMA_H
#define DB_SCHEMA_H

#include <arrow/api.h>

namespace db {

    /**
     * THe data type of a column
     */
    enum class ColumnType {
        STRING, LONG, DOUBLE
    };

    /**
     * Encoding scheme for a column
     */
    enum class ColumnEncoding { PLAIN = 0, DICT };

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
        using ArrayType = arrow::StringArray;
        using ElementType = std::string;
        using BuilderType = arrow::StringBuilder ;
        using DictionaryBuilderType = arrow::StringDictionaryBuilder;
        const ColumnType TYPE_ID = ::db::ColumnType::STRING;
        ColumnType id() override { return TYPE_ID; };
        std::shared_ptr<arrow::DataType> getArrowType() override { return arrow::utf8(); }
    };

    /**
     * (64 bit) Long column type
     */
    class LongType : public DataType  {
    public:
        using ArrayType = arrow::NumericArray<arrow::Int64Type>;
        using ElementType = arrow::Int64Type::c_type;
        using BuilderType = arrow::Int64Builder;
        using DictionaryBuilderType = arrow::DictionaryBuilder<arrow::Int64Type>;
        const ColumnType TYPE_ID = ::db::ColumnType::LONG;
        ColumnType id() override { return TYPE_ID; };
        std::shared_ptr<arrow::DataType> getArrowType() override { return arrow::int64(); }
    };

    /**
     * Double precision column type.
     */
    class DoubleType : public DataType  {
    public:
        using ArrayType = arrow::NumericArray<arrow::DoubleType>;
        using ElementType = arrow::DoubleType::c_type;
        using BuilderType = arrow::DoubleBuilder;
        // TODO: what if there _is_ no corresponding dictionary type ???
        using DictionaryBuilderType = arrow::DoubleBuilder;
        const ColumnType TYPE_ID = ::db::ColumnType::DOUBLE;
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


    class GenValue {

    public:

        virtual ~GenValue() = default;

    };

    template <typename T>
    class Value : public GenValue {

    public:

        explicit Value(T value) : _value(value) {};

        T get() { return _value; }

    private:
        T _value;
    };

    class NullValue : public GenValue {

    };

    /**
     * Create int64 value suitable for passing into addRow().
     * @param i
     * @return
     */
    std::shared_ptr<GenValue> long_val(int64_t i);

    /**
     * Create float64 value suitable for passing into addRow().
     * @param d
     * @return
     */
    std::shared_ptr<GenValue> double_val(double d);

    /**
     * Create string value suitable for passing into addRow().
     * @param s
     * @return
     */
    std::shared_ptr<GenValue> string_val(std::string s);

    std::shared_ptr<GenValue> null_val();
};


#endif //DB_SCHEMA_H
