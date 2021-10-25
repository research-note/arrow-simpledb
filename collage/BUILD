load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "bin",
    hdrs = [
        "Util.hpp",
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
