

load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

filegroup(
    name = "src",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"]
)

cmake(
   name = "seal",
   cache_entries = {
       "SEAL_THROW_ON_TRANSPARENT_CIPHERTEXT": "OFF",
   },
   defines = [
        "SEAL_USE_CXX17=ON",
        "SEAL_USE_INTRIN=ON",
        "SEAL_USE_MSGSL=ON",
        "SEAL_USE_ZLIB=OFF",
        "SEAL_BUILD_TESTS=OFF",
        "BUILD_SHARED_LIBS=OFF",
        "CMAKE_BUILD_TYPE=Release",
   ],
   install = True,
   lib_source = ":src",
   out_include_dir = "include/SEAL-4.0",
   out_static_libs = ["libseal-4.0.a"],
   visibility = ["//visibility:public"],
   tags = ["requires-network"],
)

