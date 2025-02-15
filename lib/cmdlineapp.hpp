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


#ifndef CMDLINEAPP_HPP_
#define CMDLINEAPP_HPP_

#include "cmdline.hpp"
#include "console.hpp"
#include <string>
#include <vector>

class cCmdlineApp
{
public:
    cCmdlineApp (const char* name, const char* brief, const char* usage, const char* description, const char* version,
        const char* build = nullptr, const char* buildDetails = nullptr)
    {
            this->name = name;
            this->brief = brief;
            this->usage = usage;
            this->description = description;
            this->version = version;
            this->build = build;
            this->buildDetails = buildDetails;

            helpRequested = 0;
            versionRequested = 0;
            verbosity = 0;

            cmdline.addOption  (true, 'h', "help", "Display this text", &helpRequested, nullptr, ARG_NO, nullptr, false, true);
            cmdline.addOption  (true, 0, "version", "Show detailed version information", &versionRequested, nullptr, ARG_NO, nullptr, false, true);
            addCmdLineOption (true, 'v', "verbose",
                "Produce verbose output when parsing and printing. This option can be supplied multiple times (up to 4 times, e.g., -vvvv) for even more debug output."
                , &verbosity);
    }
    virtual ~cCmdlineApp ()
    {
    }
    int main (int argc, char* argv[])
    {
        int index = 0;
        bool parseOk = cmdline.parse (argc, argv, &index);

        switch (verbosity)
        {
        case 1:
            Console::SetPrintLevel(Console::Verbose);
            break;
        case 2:
            Console::SetPrintLevel(Console::MoreVerbose);
            break;
        case 3:
            Console::SetPrintLevel(Console::MostVerbose);
            break;
        case 4:
            Console::SetPrintLevel(Console::Debug);
            break;
        }

        if (helpRequested)
        {
            printUsage ();
            return 0;
        }
        if (versionRequested)
        {
            printVersion ();
            return 0;
        }

        if (!parseOk)
        {
            Console::PrintError ("try %s -h\n", argv[0]);
            return -1;
        }

        std::vector <std::string> args;

        for (int n = index; n < argc; n++)
        {
            args.emplace_back(argv[n]);
        }

        return this->execute (args);
    }

protected:
    virtual int execute (const std::vector<std::string>& args) = 0;
    void printUsage ()
    {
        Console::Print ("%s %s - %s\n\nUsage: ", name, version, brief);
        Console::PrintWrapedText (usage, 100, 0, 7);
        Console::Print ("\n");
        cmdline.printOptions ();
        Console::Print ("\n");
        Console::PrintWrapedText (description, 100);
        Console::Print ("\n");
    }
    void printVersion ()
    {
        if (build)
            Console::Print ("%s %s (%s)\n", name, version, build);
        else
            Console::Print ("%s %s\n", name, version);
        if (buildDetails)
            Console::Print ("build: %s\n", buildDetails);
    }

    // adds (optional) integer option with argument
    bool addCmdLineOption (bool optional, char shortname, const char* longname, const char* argname, const char* description,
            int* arg)
    {
        return cmdline.addOption (optional, shortname, longname, description, nullptr, argname, ARG_INT, (void*)arg, false);
    }
    // adds (optional) integer long-only-option with optional argument
    bool addCmdLineOption (bool optional, const char* longname, const char* argname, const char* description,
            int* optSet, int* arg)
    {
        return cmdline.addOption (optional, 0, longname, description, optSet, argname, ARG_INT, (void*)arg, true);
    }
    // adds (optional) string option with argument
    bool addCmdLineOption (bool optional, char shortname, const char* longname, const char* argname, const char* description,
            const char** arg)
    {
        return cmdline.addOption (optional, shortname, longname, description, nullptr, argname, ARG_STRING, (void*)arg, false);
    }
    // adds (optional) string long-only-option with optional argument
    bool addCmdLineOption (bool optional, const char* longname, const char* argname, const char* description,
            int* optSet, const char** arg)
    {
        return cmdline.addOption (optional, 0, longname, description, optSet, argname, ARG_STRING, (void*)arg, true);
    }
    // adds boolean (optional) option without argument
    bool addCmdLineOption (bool optional, char shortname, const char* longname, const char* description, int* optSet)
    {
        return cmdline.addOption (optional, shortname, longname, description, optSet);
    }

private:
    const char* name;
    const char* brief;
    const char* usage;
    const char* description;
    const char* version;
    const char* build;
    const char* buildDetails;
    int helpRequested;
    int versionRequested;
    int verbosity;
    cCmdline cmdline;
};

#endif /* CMDLINE_HPP_ */
