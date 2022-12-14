load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
package(default_visibility = ["//visibility:public"])
cc_library(
  name = "APSI",
  copts = [
    "-std=c++17",
  ],
  deps = [
    "//common/apsi:apsi_common_lib",
    "//receiver/apsi:apsi_receiver_lib",
    "//sender/apsi:apsi_sender_lib",
  ],
)
