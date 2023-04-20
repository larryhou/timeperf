#!/usr/bin/env bash
set -x
cd $(dirname $0)
function ndk-build() {
    ~/Library/Android/sdk/ndk/25.2.9519653/ndk-build $@
}

BUILD_DIRECTORY=./build
NDK_PROJECT_PATH=. ndk-build NDK_APPLICATION_MK=./Application.mk NDK_LIBS_OUT=${BUILD_DIRECTORY}/bin NDK_OUT=${BUILD_DIRECTORY}/obj
