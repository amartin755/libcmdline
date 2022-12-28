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


#include <cstdio>

#include "bug.hpp"
#include "console.hpp"
#include "cmdline.hpp"


int main (void)
{
    Console::SetPrintLevel(Console::Debug);
    try
    {
        cCmdline::unitTest ();
    }
    catch (...)
    {
        BUG ("unhandled exception");
    }
    // every failure will lead to assert, thus if we see this output, all tests have passed
    fprintf (stderr, "\n --- unit tests finished successfully !!! --- \n");
    return 0;
}
