// SPDX-License-Identifier: GPL-3.0-only
/*
 * LIBCMDLINE <https://github.com/amartin755/libcmdline>
 * Copyright (C) 2012-2021 Andreas Martin (netnag@mailbox.org)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#include <cstdarg>
#ifdef MT_CONSOLE
#include <mutex>
#endif

class Console
{
public:
    static int PrintError (const char* format, ...);
    static int Print (const char* format, ...);
    static int PrintVerbose (const char* format, ...);
    static int PrintMoreVerbose (const char* format, ...);
    static int PrintMostVerbose (const char* format, ...);
    static int PrintDebug (const char* format, ...);
    static void Clear ();
    static void PrintWrapedText(const char* text, size_t lineWidth, size_t firstIndent = 0, size_t otherIndent = 0);

    enum out_level {Silent = 1, Error = 2, Normal = 3, Verbose = 4, MoreVerbose = 5, MostVerbose = 6, Debug = 7};
    static void SetPrintLevel (out_level lvl);

private:
    static int print (out_level lvl, const char* format, va_list ap);

private:
    static out_level level;
#ifdef MT_CONSOLE
    static std::mutex mtx;
#endif
};

#endif /* CONSOLE_HPP_ */
