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

#include "example.hpp"

Example::Example (const char* name, const char* brief, const char* usage, const char* description, const char* version)
: cCmdlineApp (name, brief, usage, description, version)
{
    addCmdLineOption (false, 'a', "john", "INT", "Mandadory option with integer argument", &m_options.argA);
    addCmdLineOption (true, "jack", "INT", "Optional long-only option with integer argument", &m_options.argB_isSet, &m_options.argB);
    addCmdLineOption (true, 'c', "liz", "TEXT", "Optional option with string argument", &m_options.argC);
    addCmdLineOption (true, "susi", "INT", "Optional long-only option with optional string argument", &m_options.argD_isSet, &m_options.argD);
    addCmdLineOption (true, 'e', "peter", "Optional boolean option", &m_options.argE);
}

Example::~Example()
{
}

int Example::execute (const std::list<std::string>& args)
{
    Console::Print ("--- options --- \n");
    Console::Print ("-a = %d\n", m_options.argA);
    if (m_options.argB_isSet)
        Console::Print ("--optional-long-only-int = %d\n", m_options.argB);
    if (m_options.argC)
        Console::Print ("-c = %s\n", m_options.argC);
    if (m_options.argD_isSet)
        Console::Print ("--optional-long-only-string = %s\n", m_options.argD ? m_options.argD : "no argument set");
    Console::Print ("-e = %d\n", m_options.argE);

    Console::Print ("--- parameters --- \n");
    if (args.size ())
    {
        for (const auto& arg : args)
        {
            Console::Print ("  %s\n", arg.c_str ());
        }
    }
    else
    {
        Console::Print ("  none\n");
    }

    return 0;
}

int main(int argc, char* argv[])
{
    Example app (
            "example",
            "A demo application for libcmdline",
            "example -a INT [OPTIONS] parameters",
            "Homepage: <https://github.com/amartin755/libcmdline>",
            "V1.0");
    return app.main (argc, argv);
}
