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

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "ticklisteners_wrap.h"

//-----------------------------------------------------------------------------
// Static singletons.
//-----------------------------------------------------------------------------
static CTickListenerManager s_TickListenerManager;

//-----------------------------------------------------------------------------
// TickListenerManager accessor.
//-----------------------------------------------------------------------------
CTickListenerManager* get_tick_listener_manager()
{
	return &s_TickListenerManager;
}

//-----------------------------------------------------------------------------
// Adds a callable to the end of the CTickListenerManager vector.
//-----------------------------------------------------------------------------
void CTickListenerManager::register_listener(PyObject* pCallable)
{
	if( !m_vecCallables.HasElement(pCallable))
	{
		m_vecCallables.AddToTail(pCallable);
	}
}

//-----------------------------------------------------------------------------
// Removes all instances of a callable from the CTickListenerManager vector.
//-----------------------------------------------------------------------------
void CTickListenerManager::unregister_listener(PyObject* pCallable)
{
	m_vecCallables.FindAndRemove(pCallable);
}

//-----------------------------------------------------------------------------
// Calls all registered tick listeners.
//-----------------------------------------------------------------------------
void CTickListenerManager::call_tick_listeners()
{
	for(int i = 0; i < m_vecCallables.Count(); i++)
	{
		BEGIN_BOOST_PY()
			call<void>(m_vecCallables[i]);
		END_BOOST_PY_NORET()
	}
}
