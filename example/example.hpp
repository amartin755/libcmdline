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


#ifndef APPLICATION_HPP
#define APPLICATION_HPP


#include "cmdlineapp.hpp"

struct appOptions
{
    int argA;
    int argB_isSet;
    int argB;
    const char* argC;
    int argD_isSet;
    const char* argD;
    int argE;

    appOptions () :
        argA (0),
        argB_isSet (0),
        argB (0),
        argC (nullptr),
        argD_isSet (0),
        argD (nullptr),
        argE (0)
    {
    }
};

class Example : public cCmdlineApp
{
public:
    Example (const char* name, const char* brief, const char* usage, const char* description, const char* version);
    virtual ~Example();

    int execute (const std::vector<std::string>& args);

private:
    appOptions m_options;
};

#endif /* APPLICATION_HPP */
