LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS    := -llog
LOCAL_MODULE    := timeperf
LOCAL_C_INCLUDES:= ../test/
LOCAL_SRC_FILES := \
	../timeperf/main.cpp \
	../test/test.cpp

include $(BUILD_EXECUTABLE)
