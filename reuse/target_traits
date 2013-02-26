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
#elif defined(__linux__)
    target_system_linux
#elif defined(TARGET_OS_MAC)
    target_system_mac
#elif defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
    target_system_iphone
#else
    target_system_unknown
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
#elif defined(_MSC_VER)
    target_compiler_msc
#else
    target_compiler_unknown
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
#elif defined(_M_IX86) || defined(__i386__)
    target_cpu_ia32
#else
    target_cpu_unknown
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
