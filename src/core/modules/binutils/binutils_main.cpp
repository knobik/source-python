/**
* =============================================================================
* Source Python
* Copyright (C) 2012 Source Python Development Team.  All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
* 
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*
* As a special exception, the Source Python Team gives you permission 
* to link the code of this program (as well as its derivative works) to 
* "Half-Life 2," the "Source Engine," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, the Source.Python
* Development Team grants this exception to all derivative works.  
*/

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "../export_main.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "binutils_scanner.h"

//---------------------------------------------------------------------------------
// Other wrapping functions.
//---------------------------------------------------------------------------------
extern void Export_DynCall( void );

//---------------------------------------------------------------------------------
// Exports the binutils module.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(Binutils)
{
	// Expose the module data class as an opaque pointer.
	BOOST_CLASS(moduledata_t)
	BOOST_END_CLASS()

	// Expose the functions for binutils.
	BOOST_FUNCTION(FindModuleData,
		"Returns a moduledata struct for the given module.",
		args("szModulePath"),
		manage_new_object_policy()
	);

	BOOST_FUNCTION(FindSignature,
		"Returns the address of a signature found in memory",
		args("moduleData", "signature", "length")
	);

	BOOST_FUNCTION(FindSymbol,
        "Returns the address of a symbol found in memory",
	    args("moduleData", "symbol")
    );

    BOOST_FUNCTION(FindVirtualFunction,
        "Returns the address of a vtable function",
        args("pThisPointer", "iOffset")
    );

    BOOST_FUNCTION(GetLocBool,
        "Returns the bool value from the given address",
        args("addr")
    );

    BOOST_FUNCTION(GetLocInt,
        "Returns the integer value from the given address",
        args("addr")
    );

    BOOST_FUNCTION(GetLocFloat,
        "Returns the float value from the given address",
        args("addr")
    );

    BOOST_FUNCTION(SetLocBool,
        "Sets the given address to the given bool value",
        args("addr", "bValue")
    );

    BOOST_FUNCTION(SetLocInt,
        "Sets the given address to the given integer value",
        args("addr", "iValue")
    );

    BOOST_FUNCTION(SetLocFloat,
        "Sets the given address to the given float value",
        args("addr", "fValue")
    );

	// Export dyncall library.
	Export_DynCall();
}
