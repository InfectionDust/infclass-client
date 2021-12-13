/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#ifndef MACRO_CONFIG_INT

#error "Config macros must be defined"
#define MACRO_CONFIG_INT(Name, ScriptName, Def, Min, Max, Save, Desc);
#define MACRO_CONFIG_COL(Name, ScriptName, Def, Save, Desc);
#define MACRO_CONFIG_STR(Name, ScriptName, Len, Def, Save, Desc);

#endif

MACRO_CONFIG_STR(ClAssetInfclass, cl_asset_infclass, 50, "default", CFGFLAG_SAVE | CFGFLAG_CLIENT, "The asset for infclass")
