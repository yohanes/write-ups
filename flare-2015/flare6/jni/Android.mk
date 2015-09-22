

TARGET_CFLAGS += -fno-builtin -save-temps -g

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hello
LOCAL_SRC_FILES := main.c

include $(BUILD_EXECUTABLE)
# include $(CLEAR_VARS)
# TARGET_CFLAGS += -fno-builtin -save-temps

# LOCAL_MODULE    := testing 
# LOCAL_SRC_FILES := testing.c

# include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

TARGET_CFLAGS += -fno-builtin


LOCAL_MODULE := mylib
LOCAL_SRC_FILES := hello.c

include $(BUILD_SHARED_LIBRARY)

# include $(CLEAR_VARS)


# TARGET_CFLAGS += -fno-builtin


# LOCAL_MODULE := libstrlen
# LOCAL_SRC_FILES := strlen.c

# include $(BUILD_SHARED_LIBRARY)



# include $(CLEAR_VARS)

# TARGET_CFLAGS += -fno-builtin


# LOCAL_MODULE := myuserlib
# LOCAL_SRC_FILES := hello2.c

# include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)
TARGET_CFLAGS += -fno-builtin -save-temps -g -llog
TARGET_LDFLAGS += -llog

LOCAL_MODULE    := poc
LOCAL_SRC_FILES := poc.c

include $(BUILD_SHARED_LIBRARY)
