// ----------------------------------------------------------------------------
// CERTI - HLA RunTime Infrastructure
// Copyright (C) 2002-2006  ONERA
//
// This file is part of CERTI
//
// CERTI is free software ; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation ; either version 2 of the License, or
// (at your option) any later version.
//
// CERTI is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY ; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program ; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
// ----------------------------------------------------------------------------

#include "config.h"
#include "RTIG.hh"
#include "RTIG_cmdline.h"
#include "certi.hh"

#ifdef _WIN32
#include <signal.h>
#endif

#include <new>
#include <csignal>
#include <iostream>

using namespace certi ;
using namespace certi::rtig ;
using std::cerr ;
using std::cout ;
using std::endl ;
using std::string ;

// ----------------------------------------------------------------------------
//! SignalHandler.
extern "C" void SignalHandler(int sig)
{
    RTIG::signalHandler(sig);
    // Catch signal again.
    std::signal(sig, SignalHandler);
}

// ----------------------------------------------------------------------------
//! NewHandler
void
NewHandler()
throw (MemoryExhausted)
{
    throw MemoryExhausted("main RTIG");
}

// ----------------------------------------------------------------------------
/**
 * @defgroup certi_executable_RTIG RTIG
 *
 * The CERTI RunTime Infrastructure Gateway (RTIG) is a process which
 * coordinate the HLA simulation with CERTI, there should be at least
 * one rtig process for each federation. However a single RTIG may
 * be used for several federations.
 * The command line usage of the RTIG is following:
 * \par rtig [-v 2] [-l \@IP|hostname]
 * \par
 * <ul>
 *   <li> \b -v  (optional) verbosity level </li>
 *   <ul>
 *          <li> 0 -> no output </li>
 *          <li> 1 -> small amount </li>
 *          <li> 2 -> show fed parse </li>
 *   </ul>
 *   <li> \b -l  (optional) listening @IP address</li>
 * </ul>
 *
 * Once the RTIG is launched an HLA Federate may interact with the RTI.
 * In fact a federate does not talk to the RTIG directly but it uses
 * its \ref certi_executable_RTIA.
 * RTIG is listening to \ref certi_executable_RTIA connection on TCP port:
 *    <ol>
 *      <li> 60400 or, </li>
 *      <li> the value of environment variable CERTI_TCP_PORT if it is defined</li>
 *    </ol>
 * The RTIG exchange messages with the \ref certi_executable_RTIA in order
 * to satify HLA request coming from the Federate.
 * In particular RTIG is responsible for giving to the Federate (through its RTIA)
 * the FOM file needed to create or join the federation.
 * \copydoc certi_FOM_FileSearch
 * @ingroup certi_executable
 */
int main(int argc, char *argv[])
{
    RTIG myRTIG;
    gengetopt_args_info args ;
    if (cmdline_parser(argc, argv, &args)) exit(EXIT_FAILURE);
    /* The default verbose level is 2 */
    int verboseLevel = 2;
    if (args.verbose_given)
        verboseLevel = args.verbose_arg;

#if _WIN32
    string dn = string(argv[0]);
    dn = dn.substr(0,dn.find_last_of("\\"));
    dn = dn.substr(0,dn.find_last_of("\\"));
    if (NULL==getenv("CERTI_HOME")) {
        dn = "CERTI_HOME="+dn+"\\";
        cout << "Updating : " << dn << endl;
        putenv(dn.c_str());
    }
#endif

    if (verboseLevel>0) {
        cout << "CERTI RTIG " VERSION " - Copyright 2002-2008  ONERA" << endl ;
        cout << "This is free software ; see the source for copying "
             << "conditions. There is NO\nwarranty ; not even for "
             << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
             << endl << endl ;
    }

    std::signal(SIGINT, SignalHandler);
#ifndef _WIN32
    std::signal(SIGPIPE, SignalHandler);
#endif

    std::set_new_handler(NewHandler);

    myRTIG.setVerboseLevel(verboseLevel);
    try {
        // if a listening IP has been specified then use it
        if (args.listen_given) {
            myRTIG.setListeningIPAddress(args.listen_arg);
        }
        myRTIG.execute();
    } catch (NetworkError& e) {
        std::cerr << "CERTI RTIG aborted with a Network Error: [" << e._reason << "]." <<std::endl;
    }

    if (verboseLevel>0) {
        cout << "CERTI RTIG exiting." << endl ;
    }
    exit(EXIT_SUCCESS);
} /* end of main */
