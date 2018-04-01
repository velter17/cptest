//!
//! termcolor
//! ~~~~~~~~~
//!
//! termcolor is a header-only c++ library for printing colored messages
//! to the terminal. Written just for fun with a help of the Force.
//!
//! :copyright: (c) 2013 by Ihor Kalnytskyi, rewritten by Dmytro Sadovyi 2018
//! :license: BSD, see LICENSE for details
//!

#pragma once

// the following snippet of code detects the current OS and
// defines the appropriate macro that is used to wrap some
// platform specific things
#if defined(_WIN32) || defined(_WIN64)
#   define TERMCOLOR_OS_WINDOWS
#elif defined(__APPLE__)
#   define TERMCOLOR_OS_MACOS
#elif defined(__unix__) || defined(__unix)
#   define TERMCOLOR_OS_LINUX
#else
#   error unsupported platform
#endif


// This headers provides the `isatty()`/`fileno()` functions,
// which are used for testing whether a standart stream refers
// to the terminal. As for Windows, we also need WinApi funcs
// for changing colors attributes of the terminal.
#if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
#   include <unistd.h>
#elif defined(TERMCOLOR_OS_WINDOWS)
#   include <io.h>
#   include <windows.h>
#endif

#include <cstdio>
#include <functional>
#include <iostream>

namespace termcolor
{
    using color_t = std::ostream& (*)(std::ostream&);

    struct Bold {};
    struct Dark {};
    struct Underline {};
    struct Blink {};
    struct Reverse {};
    struct Concealed {};
    struct Grey {};
    struct Red {};
    struct Green {};
    struct Yellow {};
    struct Blue {};
    struct LightBlue {};
    struct Magenta {};
    struct LightMagenta {};
    struct Cyan {};
    struct LightCyan {};
    struct White {};
    struct Empty {};
    struct LightYellow {};

    template <typename type>
    struct color
    {
        using color_type = type;
    };

    template <typename type>
    struct bold_color
    {
        using color_type = type;
    };

    template <typename type>
    struct on_color
    {
        using color_type = type;
    };

    template <>
    struct color<Bold>
    {
        static constexpr char const* str = "\033[1m";
    };
    template <>
    struct color<Dark>
    {
        static constexpr char const* str = "\033[2m";
    };
    template <>
    struct color<Underline>
    {
        static constexpr char const* str = "\033[4m";
    };
    template <>
    struct color<Blink>
    {
        static constexpr char const* str = "\033[5m";
    };
    template <>
    struct color<Reverse>
    {
        static constexpr char const* str = "\033[7m";
    };
    template <>
    struct color<Concealed>
    {
        static constexpr char const* str = "\033[8m";
    };
    template <>
    struct color<Grey>
    {
        static constexpr char const* str = "\033[30m";
        static constexpr char const* on = "\033[40m";
    };
    template <>
    struct color<Red>
    {
        static constexpr char const* str = "\033[31m";
        static constexpr char const* on = "\033[41m";
    };
    template <>
    struct color<Green>
    {
        static constexpr char const* str = "\033[32m";
        static constexpr char const* on = "\033[42m";
    };
    template <>
    struct color<Yellow>
    {
        static constexpr char const* str = "\033[33m";
        static constexpr char const* on = "\033[43m";
    };
    template <>
    struct color<LightYellow>
    {
        static constexpr char const* str = "\033[93m";
        static constexpr char const* on = "\033[43m";
    };
    template <>
    struct color<Blue>
    {
        static constexpr char const* str = "\033[34m";
        static constexpr char const* on = "\033[44m";
    };
    template <>
    struct color<LightBlue>
    {
        static constexpr char const* str = "\033[94m";
        static constexpr char const* on = "\033[44m";
    };
    template <>
    struct color<Magenta>
    {
        static constexpr char const* str = "\033[35m";
        static constexpr char const* on = "\033[45m";
    };
    template <>
    struct color<LightMagenta>
    {
        static constexpr char const* str = "\033[95m";
        static constexpr char const* on = "\033[45m";
    };
    template <>
    struct color<Cyan>
    {
        static constexpr char const* str = "\033[36m";
        static constexpr char const* on = "\033[46m";
    };
    template <>
    struct color<LightCyan>
    {
        static constexpr char const* str = "\033[96m";
        static constexpr char const* on = "\033[46m";
    };

    template <>
    struct color<White>
    {
        static constexpr char const* str = "\033[37m";
        static constexpr char const* on = "\033[47m";
    };

    // Forward declaration of the `_internal` namespace.
    // All comments are below.
    namespace _internal
    {
        // An index to be used to access a private storage of I/O streams. See
        // colorize / nocolorize I/O manipulators for details.
        static int colorize_index = std::ios_base::xalloc();

        inline FILE* get_standard_stream(const std::ostream& stream);
        inline bool is_colorized(std::ostream& stream);
        inline bool is_atty(const std::ostream& stream);

    #if defined(TERMCOLOR_OS_WINDOWS)
        inline void win_change_attributes(std::ostream& stream, int foreground, int background=-1);
    #endif
    }

    inline
    std::ostream& colorize(std::ostream& stream)
    {
        stream.iword(_internal::colorize_index) = 1L;
        return stream;
    }

    inline
    std::ostream& nocolorize(std::ostream& stream)
    {
        stream.iword(_internal::colorize_index) = 0L;
        return stream;
    }

    inline
    std::ostream& reset(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[00m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1, -1);
        #endif
        }
        return stream;
    }

    template <typename T>
    struct apply_type {};

    template <typename T>
    inline std::ostream& operator<<(std::ostream& stream, apply_type<T>)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << color<T>::str;
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }

    template <>
    inline std::ostream& operator<<(std::ostream& stream, apply_type<Empty>)
    {
    }

    template <typename T>
    inline std::ostream& operator<<(std::ostream& stream, apply_type<color<T>>)
    {
        return stream << apply_type<T>{};
    }

    template <typename T>
    inline std::ostream& operator<<(std::ostream& stream, apply_type<bold_color<T>>)
    {
        return stream << apply_type<Bold>{} << apply_type<T>{};
    }

    template <typename T>
    inline std::ostream& operator<<(std::ostream& stream, apply_type<on_color<T>>)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << T::on;
        #endif
        }
        return stream;
    }

    template <typename T>
    inline std::ostream& apply(std::ostream& stream)
    {
        return stream << termcolor::colorize << apply_type<T>{};
    }

    //! Since C++ hasn't a way to hide something in the header from
    //! the outer access, I have to introduce this namespace which
    //! is used for internal purpose and should't be access from
    //! the user code.
    namespace _internal
    {
        //! Since C++ hasn't a true way to extract stream handler
        //! from the a given `std::ostream` object, I have to write
        //! this kind of hack.
        inline
        FILE* get_standard_stream(const std::ostream& stream)
        {
            if (&stream == &std::cout)
                return stdout;
            else if ((&stream == &std::cerr) || (&stream == &std::clog))
                return stderr;

            return 0;
        }

        // Say whether a given stream should be colorized or not. It's always
        // true for ATTY streams and may be true for streams marked with
        // colorize flag.
        inline
        bool is_colorized(std::ostream& stream)
        {
            return is_atty(stream) || static_cast<bool>(stream.iword(colorize_index));
        }

        //! Test whether a given `std::ostream` object refers to
        //! a terminal.
        inline
        bool is_atty(const std::ostream& stream)
        {
            FILE* std_stream = get_standard_stream(stream);

            // Unfortunately, fileno() ends with segmentation fault
            // if invalid file descriptor is passed. So we need to
            // handle this case gracefully and assume it's not a tty
            // if standard stream is not detected, and 0 is returned.
            if (!std_stream)
                return false;

        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            return ::isatty(fileno(std_stream));
        #elif defined(TERMCOLOR_OS_WINDOWS)
            return ::_isatty(_fileno(std_stream));
        #endif
        }

    #if defined(TERMCOLOR_OS_WINDOWS)
        //! Change Windows Terminal colors attribute. If some
        //! parameter is `-1` then attribute won't changed.
        inline void win_change_attributes(std::ostream& stream, int foreground, int background)
        {
            // yeah, i know.. it's ugly, it's windows.
            static WORD defaultAttributes = 0;

            // Windows doesn't have ANSI escape sequences and so we use special
            // API to change Terminal output color. That means we can't
            // manipulate colors by means of "std::stringstream" and hence
            // should do nothing in this case.
            if (!_internal::is_atty(stream))
                return;

            // get terminal handle
            HANDLE hTerminal = INVALID_HANDLE_VALUE;
            if (&stream == &std::cout)
                hTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
            else if (&stream == &std::cerr)
                hTerminal = GetStdHandle(STD_ERROR_HANDLE);

            // save default terminal attributes if it unsaved
            if (!defaultAttributes)
            {
                CONSOLE_SCREEN_BUFFER_INFO info;
                if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                    return;
                defaultAttributes = info.wAttributes;
            }

            // restore all default settings
            if (foreground == -1 && background == -1)
            {
                SetConsoleTextAttribute(hTerminal, defaultAttributes);
                return;
            }

            // get current settings
            CONSOLE_SCREEN_BUFFER_INFO info;
            if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                return;

            if (foreground != -1)
            {
                info.wAttributes &= ~(info.wAttributes & 0x0F);
                info.wAttributes |= static_cast<WORD>(foreground);
            }

            if (background != -1)
            {
                info.wAttributes &= ~(info.wAttributes & 0xF0);
                info.wAttributes |= static_cast<WORD>(background);
            }

            SetConsoleTextAttribute(hTerminal, info.wAttributes);
        }
    #endif // TERMCOLOR_OS_WINDOWS

    } // namespace _internal

} // namespace termcolor


#undef TERMCOLOR_OS_WINDOWS
#undef TERMCOLOR_OS_MACOS
#undef TERMCOLOR_OS_LINUX
