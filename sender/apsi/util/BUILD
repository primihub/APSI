load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
package(default_visibility = ["//visibility:public"])
cc_library(
     name = "apsi_sender_util_lib",
    srcs = [
        "cuckoo_filter.cpp",
        "cuckoo_filter_table.cpp",
    ],
    hdrs = [
        "cuckoo_filter.h",
        "cuckoo_filter_table.h",
        "hash.h",
    ],
    include_prefix = "apsi/util/",
    deps = [
        "//common/apsi/util:apsi_util_lib",
        "@com_github_primihub_seal_40//:seal",
    ],
    visibility = ["//visibility:public"],
)