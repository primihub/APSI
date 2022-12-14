
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def apsi_dependencies():
    maybe(
        http_archive,
        name = "rules_foreign_cc",
        sha256 = "6041f1374ff32ba711564374ad8e007aef77f71561a7ce784123b9b4b88614fc",
        strip_prefix = "rules_foreign_cc-0.8.0",
        url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.8.0.tar.gz",
    )
    maybe(
        http_archive,
        name = "openssl",
        url = "https://github.com/openssl/openssl/archive/refs/tags/OpenSSL_1_1_1o.tar.gz",
        sha256 = "0f745b85519aab2ce444a3dcada93311ba926aea2899596d01e7f948dbd99981",
        strip_prefix = "openssl-OpenSSL_1_1_1o",
        build_file = "//bazel:openssl.BUILD",
    )
    maybe(
        http_archive,
        name = "com_github_glog_glog",
        sha256 = "cbba86b5a63063999e0fc86de620a3ad22d6fd2aa5948bff4995dcd851074a0b",
        strip_prefix = "glog-c8f8135a5720aee7de8328b42e4c43f8aa2e60aa",
        urls = [
            "https://github.com/google/glog/archive/c8f8135a5720aee7de8328b42e4c43f8aa2e60aa.zip"
        ],
    )
    #maybe(
    #    http_archive,
    #    name = "com_github_google_flatbuffers",
    #    url = "https://github.com/google/flatbuffers/archive/refs/tags/v2.0.8.tar.gz",
    #    strip_prefix = "flatbuffers-2.0.8",
    #    # sha256 = "fec6281e4109115c5157ca720b8fe20c8f655f773172290b03f57353c11869c2",
    #)
    maybe(
        http_archive,
        name = "com_github_google_flatbuffers",
        # sha256 = "9ddb9031798f4f8754d00fca2f1a68ecf9d0f83dfac7239af1311e4fd9a565c4",
        strip_prefix = "flatbuffers-2.0.0",
        urls = [
            "https://github.com/google/flatbuffers/archive/refs/tags/v2.0.0.tar.gz"
        ],
    )

    maybe(
        # gflags Needed for glog
        http_archive,
        name = "com_github_gflags_gflags",
        sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
        strip_prefix = "gflags-2.2.2",
        urls = [
            "https://github.com/gflags/gflags/archive/v2.2.2.tar.gz",
        ],

    )
    maybe(
        new_git_repository,
        #name = "com_github_microsoft_seal",  #version 4.0
        name = "com_github_primihub_seal_40",  #version 4.0
        build_file = "//bazel:seal.BUILD",
        remote = "https://github.com/primihub/SEAL.git",
        branch = "change_submodule_resource",
    )
    maybe(
        # needed by APSI
        new_git_repository,
        name = "com_microsoft_kuku",
        build_file = "//bazel:kuku.BUILD",
        branch = "2.1.0",
        remote = "https://github.com/microsoft/Kuku.git",
    )
    maybe(
        # needed by APSI
        http_archive,
        name = "jsoncpp",
        sha256 = "f409856e5920c18d0c2fb85276e24ee607d2a09b5e7d5f0a371368903c275da2",
        strip_prefix = "jsoncpp-1.9.5",
        urls = [
            "https://github.com/open-source-parsers/jsoncpp/archive/refs/tags/1.9.5.tar.gz",
        ]
    )
    maybe(
        http_archive,
        name = "com_github_microsoft_gsl",
        build_file = "//bazel:gsl.BUILD",
        sha256 = "f0e32cb10654fea91ad56bde89170d78cfbf4363ee0b01d8f097de2ba49f6ce9",
        strip_prefix = "GSL-4.0.0",
        urls = [
            "https://github.com/microsoft/GSL/archive/refs/tags/v4.0.0.tar.gz",
        ],
    )

