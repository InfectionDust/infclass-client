#include "infc_binds.h"

#include <engine/shared/infclass.h>
#include <game/client/gameclient.h>

void CInfCBinds::OnConsoleInit()
{
	// bindings
	IConfigManager *pConfigManager = Kernel()->RequestInterface<IConfigManager>();
	if(pConfigManager)
		pConfigManager->RegisterCallback(ConfigSaveCallback, this);

	Console()->Register("infc_bind", "s[key] r[command]", CFGFLAG_CLIENT, ConBind, this, "Bind key to execute the command");
	Console()->Register("infc_binds", "?s[key]", CFGFLAG_CLIENT, ConBinds, this, "Print command executed by this keybindind or all binds");
	Console()->Register("infc_unbind", "s[key]", CFGFLAG_CLIENT, ConUnbind, this, "Unbind key");
	Console()->Register("infc_unbindall", "", CFGFLAG_CLIENT, ConUnbindAll, this, "Unbind all keys");

	// default bindings
	SetDefaults();
}

bool CInfCBinds::OnInput(const IInput::CEvent &Event)
{
	if(!GameClient()->m_GameInfo.m_InfClass)
		return false;

	return CBinds::OnInput(Event);
}

void CInfCBinds::ConfigSaveCallback(IConfigManager *pConfigManager, void *pUserData)
{
	CInfCBinds *pSelf = (CInfCBinds *)pUserData;

	pConfigManager->WriteLine("infc_unbindall", InfclassConfigDomainId());
	for(int Modifier = MODIFIER_NONE; Modifier < MODIFIER_COMBINATION_COUNT; Modifier++)
	{
		char aModifiers[128];
		GetKeyBindModifiersName(Modifier, aModifiers, sizeof(aModifiers));
		for(int Key = KEY_FIRST; Key < KEY_LAST; Key++)
		{
			if(!pSelf->m_aapKeyBindings[Modifier][Key])
				continue;

			// worst case the str_escape can double the string length
			int Size = str_length(pSelf->m_aapKeyBindings[Modifier][Key]) * 2 + 30;
			char *pBuffer = (char *)malloc(Size);
			char *pEnd = pBuffer + Size;

			str_format(pBuffer, Size, "infc_bind %s%s \"", aModifiers, pSelf->Input()->KeyName(Key));
			// process the string. we need to escape some characters
			char *pDst = pBuffer + str_length(pBuffer);
			str_escape(&pDst, pSelf->m_aapKeyBindings[Modifier][Key], pEnd);
			str_append(pBuffer, "\"", Size);
			
			pConfigManager->WriteLine(pBuffer, InfclassConfigDomainId());
			free(pBuffer);
		}
	}
}

void CInfCBinds::SetDefaults()
{
	UnbindAll();
}
