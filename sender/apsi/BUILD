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

flatbuffer_cc_library(
    name = "apsi_fbs_bin_bundle",
    srcs = [
        "bin_bundle.fbs",
    ],
    flatc_args = flatc_args,
    visibility = ["//visibility:public"],
)

flatbuffer_cc_library(
    name = "apsi_fbs_sender_db",
    srcs = [
        "sender_db.fbs",
        "psi_params.fbs",
    ],
    # deps = [
    #     "//common/apsi:apsi_fbs_psi_params",
    # ],
    flatc_args = flatc_args,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "apsi_sender_lib",
    srcs = [
        "bin_bundle.cpp",
        "query.cpp",
        "sender.cpp",
        "sender_db.cpp",
        # "grpc_sender_dispatcher.cc",
    ],
    hdrs = [
        "bin_bundle.h",
        "query.h",
        "sender.h",
        "sender_db.h",
        # "grpc_sender_dispatcher.h",
    ],
    include_prefix = "apsi/",
    deps = [
        # "@com_github_grpc_grpc//:grpc++",
        "@com_github_glog_glog//:glog",
        "@com_github_google_flatbuffers//:flatbuffers",
        "//sender/apsi/util:apsi_sender_util_lib",
        "//common/apsi:apsi_common_lib",
        "//common/apsi/network:apsi_network_lib",
        "//common/apsi/oprf:apsi_oprf_lib",
        ":apsi_fbs_bin_bundle",
        ":apsi_fbs_sender_db",
    ],
    visibility = ["//visibility:public"],
)