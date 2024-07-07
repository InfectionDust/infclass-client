/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#ifndef MACRO_CONFIG_INT

#error "Config macros must be defined"
#define MACRO_CONFIG_INT(Name, ScriptName, Def, Min, Max, Save, Desc);
#define MACRO_CONFIG_COL(Name, ScriptName, Def, Save, Desc);
#define MACRO_CONFIG_STR(Name, ScriptName, Len, Def, Save, Desc);

#endif

MACRO_CONFIG_INT(ClEnableCommunities, cl_enable_communities, 1, 1, 1, CFGFLAG_SAVE | CFGFLAG_CLIENT, "Enable the Communities browser feature")
MACRO_CONFIG_STR(ClAssetInfclass, cl_asset_infclass, 50, "default", CFGFLAG_SAVE | CFGFLAG_CLIENT, "The asset for infclass")
MACRO_CONFIG_STR(ClInfcUpdatesUrl, cl_infc_updates_url, 256,  "https://infclass.github.io/files", CFGFLAG_SAVE | CFGFLAG_CLIENT, "The client updates URL")
MACRO_CONFIG_INT(ClInfStatusSize, infc_status_size, 16, 4, 64, CFGFLAG_SAVE | CFGFLAG_CLIENT, "The size of infclass status icons")
MACRO_CONFIG_INT(InfcShowBoomerWeapon, infc_show_boomer_weapon, 0, 0, 1, CFGFLAG_SAVE | CFGFLAG_CLIENT, "Toggle the Boomer hammer visibility")
MACRO_CONFIG_INT(InfUseDDRaceHUD, infc_use_ddrace_hud, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_CLIENT, "Use DDRace (Health/Ammo/State) HUD for Infclass")
MACRO_CONFIG_INT(InfcShowHookProtection, infc_show_hook_protection, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_CLIENT, "Show character hook protection status")
