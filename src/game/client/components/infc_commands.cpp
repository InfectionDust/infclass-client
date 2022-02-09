/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include <game/client/gameclient.h>

#include <engine/shared/config.h>

#include "infc_commands.h"

static const int LocationsCount = static_cast<int>(CInfCCommands::ELocation::Count);
static const char *gs_pLocationNames[LocationsCount] = {
	"middle",
	"top",
	"topright",
	"right",
	"bottomright",
	"bottom",
	"bottomleft",
	"left",
	"topleft",
	"bunker",
	"bonuszone",
	"infspawn",
};

const char *GetEnumValueName(CInfCCommands::ELocation Location)
{
	int Index = static_cast<int>(Location);
	return gs_pLocationNames[Index];
}

static const int InfoMessagesCount = static_cast<int>(CInfCCommands::EInfoMessage::Count);
static const char *gs_pInfoMessageNames[InfoMessagesCount] = {
	"run",
	"ghost",
	"help",
	"bfhf",
	"where",
	"clear",
	"witch",
	"taxi",
	"asktaxi",
	"suggesttaxi",
	"askflag",
	"suggestflag",
	"askhealing",
	"suggesthealing",
};

const char *GetEnumValueName(CInfCCommands::EInfoMessage Location)
{
	int Index = static_cast<int>(Location);
	return gs_pInfoMessageNames[Index];
}

static const char *gs_apLocationTextStyle1[LocationsCount] = {
	"↔ Middle",
	"↑ Top",
	"↗ Top right",
	"→ Right",
	"↘ Bottom right",
	"↓ Bottom",
	"↙ Bottom left",
	"← Left",
	"↖ Top left",
	"Bunker",
	"Bonus zone",
	"Spawn",
};

static const char *gs_apInfoMessageTextStyle1[InfoMessagesCount] = {
	"Run! Run! Run!",
	"Ghost!",
	"Help!",
	"Boom fly / Hammer fly!",
	"Where?",
	"Clear!",
	"Call witch!",
	"F3!",
	"Taxi is needed!",
	"Anyone needs a Taxi?",
	"Please find a flag!",
	"Anyone needs a flag?",
	"Heal!",
	"Who needs healing?",
};

template <typename TEnum>
TEnum GetKeyByName(const char *pName)
{
	for(int i = 0; i < static_cast<int>(TEnum::Count); ++i)
	{
		TEnum Key = static_cast<TEnum>(i);
		if(str_comp(pName, GetEnumValueName(Key)) == 0)
		{
			return Key;
		}
	}

	return TEnum::Invalid;
}

CInfCCommands::CInfCCommands()
{
}

void CInfCCommands::OnConsoleInit()
{
	Console()->Register("witch", "", CFGFLAG_CLIENT, ConCallWitch, this, "Echo the text in chat window");
	Console()->Register("say_team_location", "s[location] ?s[clear]", CFGFLAG_CLIENT, ConSayTeamLocation, this, "Echo the text in chat window");
	Console()->Register("say_message", "s[message_type]", CFGFLAG_CLIENT, ConSayInfoMessage, this, "Say a specific message in the chat or team chat");
}

void CInfCCommands::ConSayTeamLocation(IConsole::IResult *pResult, void *pUserData)
{
	CInfCCommands *pThis = static_cast<CInfCCommands*>(pUserData);
	if(pResult->NumArguments() < 1)
	{
		dbg_msg("infc/commands", "ConSayTeamLocation: No args given");
		return;
	}
	const char *pLocation = pResult->GetString(0);
	ELocation Location = GetKeyByName<ELocation>(pLocation);
	if(Location == ELocation::Invalid)
	{
		dbg_msg("infc/commands", "ConSayTeamLocation: Invalid location %s", pLocation);
		return;
	}

	const char *pExtraArg = pResult->GetString(1);
	pThis->ConSayTeamLocation(Location, pExtraArg);
}

void CInfCCommands::ConSayTeamLocation(ELocation Location, const char *pExtraArg)
{
	const char *pText = gs_apLocationTextStyle1[static_cast<int>(Location)];
	if(pExtraArg && pExtraArg[0])
	{
		if(str_comp(pExtraArg, "clear") == 0)
		{
			char aBuffer[128];
			str_format(aBuffer, sizeof(aBuffer), "%s is clear", pText);
			m_pClient->m_Chat.SendChat(1, aBuffer);
		}
		else
		{
			dbg_msg("infc/commands", "ConSayTeamLocation: Invalid extra arg %s", pExtraArg);
		}
		return;
	}
	m_pClient->m_Chat.SendChat(1, pText);
}

void CInfCCommands::ConSayInfoMessage(IConsole::IResult *pResult, void *pUserData)
{
	CInfCCommands *pThis = static_cast<CInfCCommands*>(pUserData);
	if(pResult->NumArguments() < 1)
	{
		dbg_msg("infc/commands", "ConSayTeamInfoMessage: No args given");
		return;
	}
	const char *pMessageType = pResult->GetString(0);
	EInfoMessage InfoMessage = GetKeyByName<EInfoMessage>(pMessageType);
	if(InfoMessage == EInfoMessage::Invalid)
	{
		dbg_msg("infc/commands", "ConSayTeamInfoMessage: Invalid message type %s", pMessageType);
		return;
	}

	pThis->ConSayInfoMessage(InfoMessage);
}

void CInfCCommands::ConSayInfoMessage(EInfoMessage Message)
{
	const char *pText = gs_apInfoMessageTextStyle1[static_cast<int>(Message)];

	bool TeamChat = true;
	switch(Message)
	{
	case EInfoMessage::AdvertiseWitch:
		TeamChat = false;
		break;
	default:
		break;
	}

	m_pClient->m_Chat.SendChat(TeamChat ? 1 : 0, pText);
}

void CInfCCommands::ConCallWitch(IConsole::IResult *pResult, void *pUserData)
{
	CInfCCommands *pThis = static_cast<CInfCCommands*>(pUserData);
	pThis->ConCallWitch();
}

void CInfCCommands::ConCallWitch()
{
	m_pClient->m_Chat.SendChat(0, "/witch");
}
