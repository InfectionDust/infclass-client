/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_CLIENT_COMPONENTS_INFC_BINDS_H
#define GAME_CLIENT_COMPONENTS_INFC_BINDS_H

#include "binds.h"

class IConfigManager;

class CInfCBinds : public CBinds
{
	static void ConfigSaveCallback(IConfigManager *pConfigManager, void *pUserData);

public:
	CInfCBinds() = default;
	~CInfCBinds() = default;

	void OnConsoleInit() override;
	bool OnInput(const IInput::CEvent &Event) override;

	void SetDefaults();
};
#endif
