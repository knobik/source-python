//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "dt_send.h"
#include "server_class.h"
#include "te_particlesystem.h"
#include "coordsize.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_SERVERCLASS_ST(CTEParticleSystem, DT_TEParticleSystem)
#if defined( TF_DLL )
	SendPropFloat( SENDINFO_VECTORELEM2(m_vecOrigin, 0, x), -1, SPROP_COORD_MP_INTEGRAL ),
	SendPropFloat( SENDINFO_VECTORELEM2(m_vecOrigin, 1, y), -1, SPROP_COORD_MP_INTEGRAL ),
	SendPropFloat( SENDINFO_VECTORELEM2(m_vecOrigin, 2, z), -1, SPROP_COORD_MP_INTEGRAL ),
#else
	SendPropFloat( SENDINFO_VECTORELEM2(m_vecOrigin, 0, x), -1, SPROP_COORD),
	SendPropFloat( SENDINFO_VECTORELEM2(m_vecOrigin, 1, y), -1, SPROP_COORD),
	SendPropFloat( SENDINFO_VECTORELEM2(m_vecOrigin, 2, z), -1, SPROP_COORD),
#endif
END_SEND_TABLE()




