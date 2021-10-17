
project(lib)

MESSAGE(STATUS "Arrow root = " ${ARROW_ROOT})

find_package(Threads REQUIRED)

set(ARROW_LIBS libarrow.a)

include_directories(${ARROW_INCLIDE_DIRS})

link_directories(${ARROW_LINK_DIRS})

set(SOURCE_FILES
    columns/BaseColumnCursor.hpp
    columns/ChunkedColumnCursor.cc
    columns/ChunkedDictColumnCursor.cc
    tables/ScanTableCursor.cc
    columns/GenericColumnCursor.cc tables/TableCursor.cc
    tables/FilterProjectTableCursor.cc
    filters/Filter.hpp
    filters/GreaterThanFilter.cc filters/GreaterThanFilter.hpp
    filters/LessThanFilter.cc filters/LessThanFilter.hpp
    filters/AndFilter.cc filters/AndFilter.hpp
    tables/DBTable.cc tables/DBTable.hpp
    tables/DBColumnBuilder.cc tables/DBColumnBuilder.hpp
    core/DBSchema.hpp core/DBSchema.cc
    filters/IsNullFilter.cc filters/IsNullFilter.hpp
    filters/NotFilter.cc filters/NotFilter.hpp
    columns/BaseColumnCursor.cc
    core/Status.hpp)

add_library(lib STATIC ${SOURCE_FILES})

target_link_libraries(lib ${ARROW_LIBS} ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})