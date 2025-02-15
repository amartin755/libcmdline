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


#include <cstdarg>
#include <cstdio>
#include <sstream>

#include "console.hpp"
#include "bug.hpp"

Console::out_level Console::level = Normal;
#ifdef MT_CONSOLE
    std::mutex Console::mtx;
#endif


void Console::SetPrintLevel (out_level lvl)
{
    BUG_ON ((lvl < Silent) || (lvl > Debug));
    level = lvl;
}

int Console::PrintError (const char* format, ...)
{
    int ret;
    va_list args;
    va_start (args, format);

    ret = Console::print (Console::Error, format, args);

    va_end (args);
    return ret;
}
int Console::Print (const char* format, ...)
{
    int ret;
    va_list args;
    va_start (args, format);
#ifdef MT_CONSOLE
    mtx.lock();
#endif
    ret = Console::print (Console::Normal, format, args);
#ifdef MT_CONSOLE
    mtx.unlock();
#endif

    va_end (args);
    return ret;
}
int Console::PrintVerbose (const char* format, ...)
{
    int ret;
    va_list args;
    va_start (args, format);

    ret = Console::print (Console::Verbose, format, args);

    va_end (args);
    return ret;
}
int Console::PrintMoreVerbose (const char* format, ...)
{
    int ret;
    va_list args;
    va_start (args, format);

    ret = Console::print (Console::MoreVerbose, format, args);

    va_end (args);
    return ret;
}
int Console::PrintMostVerbose (const char* format, ...)
{
    int ret;
    va_list args;
    va_start (args, format);

    ret = Console::print (Console::MostVerbose, format, args);

    va_end (args);
    return ret;
}
int Console::PrintDebug (const char* format, ...)
{
    int ret;
    va_list args;
    va_start (args, format);

    ret = Console::print (Console::Debug, format, args);

    va_end (args);
    return ret;
}

void Console::PrintWrapedText(const char* text, size_t lineWidth, size_t firstIndent, size_t otherIndent)
{
    std::istringstream words(text);
    std::string word;
    bool isFirstLine = true;
    std::string line(firstIndent, ' ');

    while (words >> word)
    {
        bool linebreak = false;
        if (word == "</br>")
        {
            linebreak = true;
            word = "";
        }
        if (linebreak || line.length() + word.length() + 1 > lineWidth)
        {
            Console::Print ("%s\n", line.c_str());
            line = std::string(otherIndent, ' ') + word;
            isFirstLine = false;
        }
        else
        {
            if (line.length() > (isFirstLine ? firstIndent : otherIndent))
            {
                line += " ";
            }
            line += word;
        }
    }
    if (!line.empty())
    {
        Console::Print ("%s\n", line.c_str());
    }
}

void Console::Clear ()
{
    Console::Print ("%c[2J", (char)27);
    Console::Print ("%c[H", (char)27);
}

int Console::print (out_level lvl, const char* format, va_list ap)
{
    if (lvl > level)
        return false;

     // we always print to stderr to be able to separate piped in/output from console prints
    int ret = vfprintf (stderr, format, ap) >= 0;
    fflush (stderr);
    return ret;
}
