#ifndef GAME_CLIENT_COMPONENTS_INFC_COMMANDS_H
#define GAME_CLIENT_COMPONENTS_INFC_COMMANDS_H

#include <game/client/component.h>

class CInfCCommands : public CComponent
{
public:
	CInfCCommands();

	int Sizeof() const override { return sizeof(*this); }

	void OnConsoleInit() override;

	enum class ELocation
	{
		Middle,
		Top,
		TopRight,
		Right,
		BottomRight,
		Bottom,
		BottomLeft,
		Left,
		TopLeft,
		Bunker,
		BonusZone,
		InfSpawn,
		Count,
		Invalid = Count,
	};

	enum class EInfoMessage
	{
		Run,
		Ghost,
		Help,
		BoomFlyHammerFly,
		Where,
		Clear,
		AdvertiseWitch,
		Taxi,
		AskTaxi,
		SuggestTaxi,
		AskFlag,
		SuggestFlag,
		AskHealing,
		SuggestHealing,
		Count,
		Invalid = Count,
	};

	static void ConSayTeamLocation(IConsole::IResult *pResult, void *pUserData);
	void ConSayTeamLocation(ELocation Location, const char *pExtraArg);
	static void ConSayInfoMessage(IConsole::IResult *pResult, void *pUserData);
	void ConSayInfoMessage(EInfoMessage Message);

	static void ConCallWitch(IConsole::IResult *pResult, void *pUserData);
	void ConCallWitch();
};
#endif
