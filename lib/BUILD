load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "lib",
    srcs = [
        "core/DBSchema.cc",
        "columns/ChunkedColumnCursor.cc",
        "columns/ChunkedDictColumnCursor.cc",
        "columns/BaseColumnCursor.cc",
        "columns/GenericColumnCursor.cc",
        "tables/ScanTableCursor.cc",
        "tables/TableCursor.cc",
        "tables/DBTable.cc",
        "tables/DBColumnBuilder.cc",
        "tables/FilterProjectTableCursor.cc",
        "filters/GreaterThanFilter.cc",
        "filters/LessThanFilter.cc",
        "filters/AndFilter.cc",
        "filters/IsNullFilter.cc",
        "filters/NotFilter.cc",
    ],
    hdrs = [
        "core/DBSchema.hpp",
        "core/Status.hpp",
        "columns/BaseColumnCursor.hpp",
        "tables/DBTable.hpp",
        "tables/DBColumnBuilder.hpp",
        "filters/Filter.hpp",
        "filters/GreaterThanFilter.hpp",
        "filters/LessThanFilter.hpp",
        "filters/AndFilter.hpp",
        "filters/IsNullFilter.hpp",
        "filters/NotFilter.hpp",
    ],

    visibility = [
        "//edge-store:__pkg__",
        "//testdb:__pkg__",
    ],
)
