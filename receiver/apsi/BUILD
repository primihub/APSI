load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
package(default_visibility = ["//visibility:public"])
cc_library(
    name = "apsi_receiver_lib",
    srcs = [
        "receiver.cpp",
        "plaintext_powers.cpp",
    ],
    hdrs = [
        "receiver.h",
        "itt.h",
        "match_record.h",
        "plaintext_powers.h",
    ],
    include_prefix = "apsi/",
    deps = [
        "@com_github_glog_glog//:glog",
        "@com_github_primihub_seal_40//:seal",
        "@com_github_microsoft_gsl//:gsl_lib",
        "//common/apsi:apsi_psi_params_lib",
        "//common/apsi:apsi_common_lib",
        "//common/apsi/util:apsi_util_base_lib",
        "//common/apsi/network:apsi_network_lib",
        "//common/apsi/oprf:apsi_oprf_lib",
    ],
    visibility = ["//visibility:public"],
)