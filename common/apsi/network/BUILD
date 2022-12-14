load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@com_github_google_flatbuffers//:build_defs.bzl", "flatbuffer_cc_library", "DEFAULT_FLATC_ARGS")
package(default_visibility = ["//visibility:public"])
flatc_args = [
    "--gen-object-api",
    "--gen-compare",
    "--gen-mutable",
    # "--gen-all",
    "--reflect-names",
    "--cpp-ptr-type flatbuffers::unique_ptr",
    "--force-empty",
    # "--grpc",
    "--cpp",
]

flatbuffer_cc_library (
    name = "apsi_network_fbs_lib",
    srcs = [
        "ciphertext.fbs",
        # "psi_params.fbs",
        # "sender_db.fbs",
        "sop_header.fbs",
        "sop_response.fbs",
        "sop.fbs",
        "result_package.fbs",
        # "keyword_pir_service.fbs",
    ],
    # out_prefix = "apsi/network/",
    flatc_args = flatc_args,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "apsi_network_lib",
    srcs = [
        "result_package.cpp",
        "sender_operation.cpp",
        "sender_operation_response.cpp",
        "stream_channel.cpp",
    ],
    hdrs = [
        "channel.h",
        "network_channel.h",
        "result_package.h",
        "sender_operation.h",
        "sender_operation_response.h",
        "stream_channel.h",
    ],
    defines = ["BAZEL_BUILD"],
    # includes = ["primihub/app/apsi/common/network/",],
    # copts = ["-Iprimihub/app/apsi/common/network/"],
    include_prefix = "apsi/network",
    deps = [
        "@com_github_primihub_seal_40//:seal",
        # "@com_github_grpc_grpc//:grpc++",
        "@com_github_google_flatbuffers//:flatbuffers",
        "//common/apsi:apsi_common_lib",
        ":apsi_network_fbs_lib",

    ],
    linkstatic=False,
    visibility = ["//visibility:public"],
)