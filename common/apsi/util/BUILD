load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
package(default_visibility = ["//visibility:public"])
DEFAULT_COPTS = ["-std=c++17",]
cc_library(
    name = "apsi_util_base_lib",
    srcs = [
        "utils.cpp",
        "stopwatch.cpp",
    ],
    hdrs = [
        "utils.h",
        "stopwatch.h",
    ],
    include_prefix = "apsi/util",
    deps = [
        "@com_github_primihub_seal_40//:seal",
        "@com_github_microsoft_gsl//:gsl_lib",
        "@com_microsoft_kuku//:kuku",
        # "//common/apsi:apsi_common_headers",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "apsi_util_lib",
    srcs = [
        "interpolate.cpp",
        "label_encryptor.cpp",
        "db_encoding.cpp",
        "utils.cpp",
        "csv_reader.cpp",
        "common_utils.cpp",
    ],
    hdrs = [
        "interpolate.h",
        "label_encryptor.h",
        "db_encoding.h",
        "thread_pool.h",
        "utils.h",
        "csv_reader.h",
        # "base_clp.h",
        "common_utils.h",
    ],
    include_prefix = "apsi/util",
    deps = [
        "@com_github_primihub_seal_40//:seal",
        "@com_microsoft_kuku//:kuku",
        "//common/apsi/fourq:apsi_fourq_lib",
        # "//common/apsi:apsi_common_headers",
        "//common/apsi:apsi_psi_params_lib",
        "//common/apsi:log_lib",
        "//common/apsi:item_lib",
    ],
    copts = DEFAULT_COPTS,
    visibility = ["//visibility:public"],
)