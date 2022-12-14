load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@com_github_google_flatbuffers//:build_defs.bzl", "flatbuffer_cc_library", "DEFAULT_FLATC_ARGS")
package(default_visibility = ["//visibility:public"])
flatc_args = [
    "--gen-object-api",
    "--gen-compare",
    "--gen-mutable",
    "--gen-all",
    "--reflect-names",
    "--cpp-ptr-type flatbuffers::unique_ptr",
    "--force-empty",
    "--grpc",
    "--cpp",
]

flatbuffer_cc_library (
    name = "apsi_fbs_psi_params",
    srcs = [
        "psi_params.fbs",
    ],
    flatc_args = flatc_args,
    visibility = ["//visibility:public"],
)

cc_library(
     name = "apsi_psi_params_lib",
    srcs = [
        "psi_params.cpp",
    ],
    hdrs = [
        "psi_params.h",
    ],
    defines = ["BAZEL_BUILD"],
    include_prefix = "apsi",
    deps = [
        ":version_lib",
        ":log_lib",
        "@jsoncpp//:jsoncpp",
        # ":apsi_common_headers",
        ":apsi_fbs_psi_params",
        "//common/apsi/util:apsi_util_base_lib"
    ],
    visibility = ["//visibility:public"],
)

# cc_library(
#     name = "apsi_common_headers",
#     hdrs = [
#         "item.h",
#         "log.h",
#         "version.h",
#         "config.h",
#     ],
#     include_prefix = "apsi",
#     deps = [
#         "@com_microsoft_kuku//:kuku",
#         "@com_github_microsoft_gsl//:gsl_lib",
#     ],
#     visibility = ["//visibility:public"],
# )
cc_library(
    name = "version_lib",
    srcs = [
        "version.cpp",
    ],
    hdrs = [
        "version.h",
        "config.h",
    ],
    include_prefix = "apsi",
)

cc_library(
    name = "item_lib",
    srcs = [
        "item.cpp",
    ],
    hdrs = [
        "item.h",
    ],
    include_prefix = "apsi",
    deps = [
        "@com_microsoft_kuku//:kuku",
        "@com_github_microsoft_gsl//:gsl_lib",
        "@com_github_primihub_seal_40//:seal",
        "//common/apsi/util:apsi_util_base_lib",
    ],
)
cc_library(
    name = "log_lib",
    srcs = [
        "log.cpp",
    ],
    hdrs = [
        "log.h",
        "config.h",
    ],
    include_prefix = "apsi",
    deps = [
        "@com_github_glog_glog//:glog",
    ],
)
cc_library(
    name = "powers_lib",
    srcs = [
        "powers.cpp",
    ],
    hdrs = [
        "powers.h",
    ],
    include_prefix = "apsi",
    deps = [
        "@com_github_primihub_seal_40//:seal",
        "//common/apsi/util:apsi_util_lib",
        ":thread_pool_mgr",
    ],
)
cc_library(
    name = "thread_pool_mgr",
    srcs = [
        "thread_pool_mgr.cpp",
    ],
    hdrs = [
        "thread_pool_mgr.h",
    ],
    include_prefix = "apsi",
    deps = [
        "//common/apsi/util:apsi_util_lib",
    ],
)
cc_library(
    name = "apsi_common_lib",
    hdrs = [
        # "version.h"
        # "apsi.h",
        "crypto_context.h",
        # "powers.h",
        "requests.h",
        "responses.h",
        "seal_object.h",
    ],
    include_prefix = "apsi",
    deps = [
        ":version_lib",
        ":log_lib",
        ":item_lib",
        ":powers_lib",
        ":thread_pool_mgr",
        # ":apsi_common_headers",
        # ":apsi_fbs_psi_params",
        "//common/apsi/util:apsi_util_lib",
    ],
    linkstatic=False,
    visibility = ["//visibility:public"],
)