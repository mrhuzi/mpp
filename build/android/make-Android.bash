#!/bin/bash
# Run this from within a bash shell
ANDROID_NDK=~/work/android/ndk/android-ndk-r10d/
PLATFORM=$ANDROID_NDK/platforms/android-17/arch-arm

cmake -DCMAKE_TOOLCHAIN_FILE=./android.toolchain.cmake                      \
      -DANDROID_NDK=${ANDROID_NDK}                                          \
      -DANDROID_SYSROOT=${PLATFORM}                                         \
      -DANDROID_ABI="armeabi-v7a with NEON"                                 \
      -DANDROID_TOOLCHAIN_NAME="arm-linux-androideabi-4.8"                  \
      -DANDROID_NATIVE_API_LEVEL=android-21                                 \
      -DANDROID_STL=none                                                    \
      ../../

# ----------------------------------------------------------------------------
# usefull cmake debug flag
# ----------------------------------------------------------------------------
      #-DCMAKE_BUILD_TYPE=Debug                                              \
      #-DCMAKE_VERBOSE_MAKEFILE=true                                         \
      #--trace                                                               \
      #--debug-output                                                        \

#cmake --build . --clean-first -- V=1
cmake --build .

# ----------------------------------------------------------------------------
# test script
# ----------------------------------------------------------------------------
#adb push osal/test/rk_log_test /system/bin/
#adb push osal/test/rk_thread_test /system/bin/
#adb shell sync
#adb shell logcat -c
#adb shell rk_log_test
#adb shell rk_thread_test
#adb logcat -d|tail -30





