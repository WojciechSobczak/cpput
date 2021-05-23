#pragma once

#define CPPUT_NO_COPYABLE(class_name) \
    class_name(const class_name& other) = delete; \
    class_name(class_name& other) = delete; \

#define CPPUT_NO_MOVABLE(class_name) \
    class_name(const class_name&& other) = delete; \
    class_name(class_name&& other) = delete; \

#define CPPUT_NO_REPLICABLE(class_name) \
    CPPUT_NO_COPYABLE(class_name); \
    CPPUT_NO_MOVABLE(class_name); \

#define CPPUT_DEFAULT_COPYABLE(class_name) \
    class_name(const class_name& other) = default; \
    class_name(class_name& other) = default; \

#define CPPUT_DEFAULT_MOVABLE(class_name) \
    class_name(const class_name&& other) = default; \
    class_name(class_name&& other) = default; \

#define CPPUT_DEFAULT_REPLICABLE(class_name) \
    CPPUT_DEFAULT_COPYABLE(class_name); \
    CPPUT_DEFAULT_MOVABLE(class_name); \


