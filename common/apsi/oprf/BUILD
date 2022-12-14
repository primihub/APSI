load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
package(default_visibility = ["//visibility:public"])
cc_library(
    name = "apsi_oprf_lib",
    srcs = [
        "ecpoint.cpp",
        "oprf_sender.cpp",
        "oprf_receiver.cpp",
    ],
    hdrs = [
        "ecpoint.h",
        "oprf_common.h",
        "oprf_sender.h",
        "oprf_receiver.h",
    ],
    include_prefix = "apsi/oprf",
    deps = [
        "@com_github_primihub_seal_40//:seal",
        "@com_github_microsoft_gsl//:gsl_lib",
        #"//common/apsi:apsi_common_headers",
        "//common/apsi/fourq:apsi_fourq_lib",
        "//common/apsi/util:apsi_util_lib",
        "//common/apsi:apsi_common_lib",
    ],
    visibility = ["//visibility:public"],
)