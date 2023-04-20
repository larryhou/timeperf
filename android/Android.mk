LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS    := -llog
LOCAL_MODULE    := timeperf
LOCAL_SRC_FILES := ../timeperf/main.cpp

include $(BUILD_EXECUTABLE)
