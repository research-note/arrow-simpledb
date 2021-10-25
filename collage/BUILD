load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "bin",
    hdrs = [
        "Util.hpp",
    ],
)

cc_test(
    name = "test",
    srcs = ["test/TableTest.cc"],
    deps = [
        "@gtest//:gtest_main", # gtest_main already contains gtest
        ":library"
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":bin",
        "//lib:lib",
    ],
)
