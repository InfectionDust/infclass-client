/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef ENGINE_CLIENT_SERVERBROWSER_H
#define ENGINE_CLIENT_SERVERBROWSER_H

#include <base/system.h>

#include <engine/console.h>
#include <engine/serverbrowser.h>
#include <engine/shared/memheap.h>

#include <unordered_map>

typedef struct _json_value json_value;
class CNetClient;
class IConfigManager;
class IConsole;
class IEngine;
class IFavorites;
class IFriends;
class IServerBrowserHttp;
class IServerBrowserPingCache;
class IStorage;

class CServerBrowser : public IServerBrowser
{
public:
	class CServerEntry
	{
	public:
		int64_t m_RequestTime;
		bool m_RequestIgnoreInfo;
		int m_GotInfo;
		CServerInfo m_Info;

		CServerEntry *m_pPrevReq; // request list
		CServerEntry *m_pNextReq;
	};

	CServerBrowser();
	virtual ~CServerBrowser();

	// interface functions
	void Refresh(int Type) override;
	bool IsRefreshing() const override;
	bool IsGettingServerlist() const override;
	int LoadingProgression() const override;
	void RequestResort() { m_NeedResort = true; }

	int NumServers() const override { return m_NumServers; }
	int Players(const CServerInfo &Item) const override;
	int Max(const CServerInfo &Item) const override;
	int NumSortedServers() const override { return m_NumSortedServers; }
	int NumSortedPlayers() const override { return m_NumSortedPlayers; }
	const CServerInfo *SortedGet(int Index) const override;

	const char *GetTutorialServer() override;
	void LoadDDNetRanks();
	void RecheckOfficial();
	void LoadDDNetServers();
	void LoadDDNetInfoJson();
	void LoadInfclassInfoJson();
	const json_value *LoadDDNetInfo();
	const json_value *LoadInfclassInfo();
	void UpdateServerFilteredPlayers(CServerInfo *pInfo) const;
	void UpdateServerFriends(CServerInfo *pInfo) const;
	CServerInfo::ERankState HasRank(const char *pMap);

	const std::vector<CCommunity> &Communities() const override;
	const CCommunity *Community(const char *pCommunityId) const override;

	void DDNetFilterAdd(char *pFilter, int FilterSize, const char *pName) const override;
	void DDNetFilterRem(char *pFilter, int FilterSize, const char *pName) const override;
	bool DDNetFiltered(const char *pFilter, const char *pName) const override;
	void CountryFilterClean(int CommunityIndex) override;
	void TypeFilterClean(int CommunityIndex) override;

	//
	void Update();
	void OnServerInfoUpdate(const NETADDR &Addr, int Token, const CServerInfo *pInfo);
	void SetHttpInfo(const CServerInfo *pInfo);
	void RequestCurrentServer(const NETADDR &Addr) const;
	void RequestCurrentServerWithRandomToken(const NETADDR &Addr, int *pBasicToken, int *pToken) const;
	void SetCurrentServerPing(const NETADDR &Addr, int Ping);

	void SetBaseInfo(class CNetClient *pClient, const char *pNetVersion);
	void OnInit();

	void QueueRequest(CServerEntry *pEntry);
	CServerEntry *Find(const NETADDR &Addr);
	int GetCurrentType() override { return m_ServerlistType; }
	bool IsRegistered(const NETADDR &Addr);

private:
	CNetClient *m_pNetClient = nullptr;
	IConfigManager *m_pConfigManager = nullptr;
	IConsole *m_pConsole = nullptr;
	IEngine *m_pEngine = nullptr;
	IFriends *m_pFriends = nullptr;
	IFavorites *m_pFavorites = nullptr;
	IStorage *m_pStorage = nullptr;
	char m_aNetVersion[128];

	bool m_RefreshingHttp = false;
	IServerBrowserHttp *m_pHttp = nullptr;
	IServerBrowserPingCache *m_pPingCache = nullptr;
	const char *m_pHttpPrevBestUrl = nullptr;

	CHeap m_ServerlistHeap;
	CServerEntry **m_ppServerlist;
	int *m_pSortedServerlist;
	std::unordered_map<NETADDR, int> m_ByAddr;

	std::vector<CCommunity> m_vCommunities;
	int m_OwnLocation = CServerInfo::LOC_UNKNOWN;

	json_value *m_pDDNetInfo;
	json_value *m_pInfclassInfo;

	CServerEntry *m_pFirstReqServer; // request list
	CServerEntry *m_pLastReqServer;
	int m_NumRequests;

	bool m_NeedResort;
	int m_Sorthash;

	// used instead of g_Config.br_max_requests to get more servers
	int m_CurrentMaxRequests;

	int m_NumSortedServers;
	int m_NumSortedServersCapacity;
	int m_NumSortedPlayers;
	int m_NumServers;
	int m_NumServerCapacity;

	int m_ServerlistType;
	int64_t m_BroadcastTime;
	unsigned char m_aTokenSeed[16];

	int GenerateToken(const NETADDR &Addr) const;
	static int GetBasicToken(int Token);
	static int GetExtraToken(int Token);

	// sorting criteria
	bool SortCompareName(int Index1, int Index2) const;
	bool SortCompareMap(int Index1, int Index2) const;
	bool SortComparePing(int Index1, int Index2) const;
	bool SortCompareGametype(int Index1, int Index2) const;
	bool SortCompareNumPlayers(int Index1, int Index2) const;
	bool SortCompareNumClients(int Index1, int Index2) const;
	bool SortCompareNumPlayersAndPing(int Index1, int Index2) const;

	//
	void Filter();
	void Sort();
	int SortHash() const;

	void CleanUp();

	void UpdateFromHttp();
	CServerEntry *Add(const NETADDR *pAddrs, int NumAddrs);

	void RemoveRequest(CServerEntry *pEntry);

	void RequestImpl(const NETADDR &Addr, CServerEntry *pEntry, int *pBasicToken, int *pToken, bool RandomToken) const;

	void RegisterCommands();
	static void Con_LeakIpAddress(IConsole::IResult *pResult, void *pUserData);

	void SetInfo(CServerEntry *pEntry, const CServerInfo &Info);
	void SetLatency(NETADDR Addr, int Latency);
};

#endif
