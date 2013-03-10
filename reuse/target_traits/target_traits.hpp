#ifndef _LIBSHY_TARGET_TRAITS_HPP_
#define _LIBSHY_TARGET_TRAITS_HPP_

#include <type_traits>

namespace shy
{
    enum target_system_name
    {
        target_system_windows,
        target_system_linux,
        target_system_mac,
        target_system_iphone,
        target_system_unknown
    };

    const target_system_name target_system =
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN32__)
    target_system_windows
    #define SHY_TARGET_SYSTEM_WINDOWS 1
#elif defined(__linux__)
    target_system_linux
    #define SHY_TARGET_SYSTEM_LINUX 1
#elif defined(TARGET_OS_MAC)
    target_system_mac
    #define SHY_TARGET_SYSTEM_MAC 1
#elif defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
    target_system_iphone
    #define SHY_TARGET_SYSTEM_IPHONE 1
#else
    target_system_unknown
    #define SHY_TARGET_SYSTEM_UNKNOWN 1
#endif
    ;

    template <target_system_name N = target_system>
    struct target_system_is_unknown : std::true_type
    {
    };

    template <>
    struct target_system_is_unknown<target_system_windows> : std::false_type
    {
    };

    template <target_system_name N = target_system>
    struct target_system_is_windows : std::conditional<target_system_windows == N, std::true_type, std::false_type>::type
    {
    };

    template <>
    struct target_system_is_unknown<target_system_linux> : std::false_type
    {
    };

    template <target_system_name N = target_system>
    struct target_system_is_linux : std::conditional<target_system_linux == N, std::true_type, std::false_type>::type
    {
    };

    template <>
    struct target_system_is_unknown<target_system_mac> : std::false_type
    {
    };

    template <target_system_name N = target_system>
    struct target_system_is_mac : std::conditional<target_system_mac == N, std::true_type, std::false_type>::type
    {
    };

    template <>
    struct target_system_is_unknown<target_system_iphone> : std::false_type
    {
    };

    template <target_system_name N = target_system>
    struct target_system_is_iphone : std::conditional<target_system_iphone == N, std::true_type, std::false_type>::type
    {
    };

    enum target_compiler_name
    {
        target_compiler_gcc,
        target_compiler_msc,
        target_compiler_unknown
    };

    const target_compiler_name target_compiler =
#if defined(__GNUC__)
    target_compiler_gcc
    #define SHY_TARGET_COMPILER_GCC 1
#elif defined(_MSC_VER)
    target_compiler_msc
    #define SHY_TARGET_COMPILER_MSC 1
#else
    target_compiler_unknown
    #define SHY_TARGET_COMPILER_UNKNOWN 1
#endif
    ;

    template <target_compiler_name N = target_compiler>
    struct target_compiler_is_unknown : std::true_type
    {
    };

    template <>
    struct target_compiler_is_unknown<target_compiler_gcc> : std::false_type
    {
    };

    template <target_compiler_name N = target_compiler>
    struct target_compiler_is_gcc : std::conditional<target_compiler_gcc == N, std::true_type, std::false_type>::type
    {
    };

    template <>
    struct target_compiler_is_unknown<target_compiler_msc> : std::false_type
    {
    };

    template <target_compiler_name N = target_compiler>
    struct target_compiler_is_msc : std::conditional<target_compiler_msc == N, std::true_type, std::false_type>::type
    {
    };

    enum target_cpu_name
    {
        target_cpu_ia32,
        target_cpu_amd64,
        target_cpu_unknown
    };

    const target_cpu_name target_cpu =
#if defined(_M_X64) || defined(__amd64__)
    target_cpu_amd64
    #define SHY_TARGET_CPU_AMD64 1
#elif defined(_M_IX86) || defined(__i386__)
    target_cpu_ia32
    #define SHY_TARGET_CPU_IA32 1
#else
    target_cpu_unknown
    #define SHY_TARGET_CPU_UNKNOWN 1
#endif
    ;

    template <target_cpu_name N = target_cpu>
    struct target_cpu_is_unknown : std::true_type
    {
    };

    template <>
    struct target_cpu_is_unknown<target_cpu_ia32> : std::false_type
    {
    };

    template <target_cpu_name N = target_cpu>
    struct target_cpu_is_ia32 : std::conditional<target_cpu_ia32 == N, std::true_type, std::false_type>::type
    {
    };

    template <>
    struct target_cpu_is_unknown<target_cpu_amd64> : std::false_type
    {
    };

    template <target_cpu_name N = target_cpu>
    struct target_cpu_is_amd64 : std::conditional<target_cpu_amd64 == N, std::true_type, std::false_type>::type
    {
    };
}

#endif
