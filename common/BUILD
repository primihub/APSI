load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@com_github_google_flatbuffers//:build_defs.bzl", "flatbuffer_cc_library", "DEFAULT_FLATC_ARGS")

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
    include_prefix = "apsi",
    deps = [
        "@jsoncpp//:jsoncpp",
        ":apsi_common_headers",
        ":apsi_fbs_psi_params",
        "//common/apsi/util:apsi_util_base_lib"
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "apsi_common_headers",
    hdrs = [
        "item.h",
        "log.h",
        "version.h",
        "config.h",
    ],
    include_prefix = "apsi",
    deps = [
        "@com_microsoft_kuku//:kuku",
        "@com_github_microsoft_gsl//:gsl_lib",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "apsi_common_lib",
    srcs = [
        "item.cpp",
        "log.cpp",
        "powers.cpp",
        "thread_pool_mgr.cpp",
        "version.cpp"
    ],
    hdrs = [
        "apsi.h",
        "crypto_context.h",
        "powers.h",
        "requests.h",
        "responses.h",
        "seal_object.h",
        "thread_pool_mgr.h",
    ],
    include_prefix = "apsi",
    deps = [
        ":apsi_common_headers",
        # ":apsi_fbs_psi_params",
        "//common/apsi/util:apsi_util_lib",
    ],
    linkstatic=False,
    visibility = ["//visibility:public"],
)