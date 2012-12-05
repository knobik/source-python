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
#ifndef _CLIENTCMD_MANAGER_H
#define _CLIENTCMD_MANAGER_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "boost/unordered_map.hpp"
#include <vector>

#include "utility/sp_util.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "convar.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// ClientCommandReturn enum
//---------------------------------------------------------------------------------
enum ClientCommandReturn
{
	CONTINUE = 0,
	BLOCK
};

class ConCommand;

//---------------------------------------------------------------------------------
// ClientCommandManager class
//---------------------------------------------------------------------------------
class ClientCommandManager
{
public:
	ClientCommandManager();
	~ClientCommandManager();

	void AddToStart(PyObject* pCallable);
	void AddToEnd(PyObject* pCallable);
	void Remove(PyObject* pCallable);

	ClientCommandReturn Dispatch(edict_t *pEntity, const CCommand &command);
private:
	CUtlVector<PyObject*> m_vecCallables;
};

#endif // _CLIENTCMD_MANAGER_H
