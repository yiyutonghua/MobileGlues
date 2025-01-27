LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE            := nobileglues
LOCAL_SRC_FILES         := mobileglues/src/main.cpp
LOCAL_C_INCLUDES        := $(LOCAL_PATH)/mobileglues/include
LOCAL_CFLAGS            += -DDEBUG
LOCAL_LDLIBS            := -ldl -llog
include $(BUILD_SHARED_LIBRARY)