load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
package(default_visibility = ["//visibility:public"])
config_setting(
    name = "cpu_arm64",
    values = {"define": "cpu=arm64"},
)
config_setting(
    name = "cpu_amd64",
    values = {"define": "cpu=amd64"},
)


cc_library(
    name = "apsi_fourq_lib",
    srcs = [
        "crypto_util.c",
        "eccp2_core.c",
        "eccp2_no_endo.c",
        "eccp2.c",
        "hash_to_curve.c",
        "random.c",
    ] + select({
        ":cpu_amd64": ["amd64/fp2_1271.S" ],
        ":cpu_arm64": [],
        "//conditions:default": [],
    }),
    hdrs = [
        "FourQ_api.h",
        "FourQ_internal.h",
        "FourQ_params.h",
        "FourQ_tables.h",
        "FourQ.h",
        "table_lookup.h",
        "random.h",
    ] + select({
        ":cpu_amd64": ["amd64/fp_x64.h"],
        ":cpu_arm64": ["arm64/fp_arm64.h"],
        "//conditions:default": ["generic/fp.h"],
    }),
    defines = select({
        ":cpu_amd64": ["_AMD64_"],
        ":cpu_arm64": ["_ARM64_"],
        "//conditions:default": [],
    }),
    include_prefix = "apsi/fourq",
    # deps = [
    #     ":apsi_network_fbs_lib",
    # ],
    visibility = ["//visibility:public"],
)