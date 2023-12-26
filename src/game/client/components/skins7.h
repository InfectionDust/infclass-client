/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_CLIENT_COMPONENTS_SKINS7_H
#define GAME_CLIENT_COMPONENTS_SKINS7_H
#include <base/vmath.h>
#include <game/client/component.h>
#include <vector>

#include <game/generated/protocol.h>

// todo: fix duplicate skins (different paths)
class CSkins7 : public CComponent
{
public:
	enum
	{
		SKINFLAG_SPECIAL = 1 << 0,
		SKINFLAG_STANDARD = 1 << 1,

		DARKEST_COLOR_LGT = 61,

		NUM_COLOR_COMPONENTS = 4,

		HAT_NUM = 2,
		HAT_OFFSET_SIDE = 2,
	};

	struct CSkinPart
	{
		int m_Flags;
		char m_aName[24];
		IGraphics::CTextureHandle m_OrgTexture;
		IGraphics::CTextureHandle m_ColorTexture;
		vec3 m_BloodColor;

		bool operator<(const CSkinPart &Other) { return str_comp_nocase(m_aName, Other.m_aName) < 0; }
	};

	struct CSkin
	{
		int m_Flags;
		char m_aName[24];
		const CSkinPart *m_apParts[NUM_SKINPARTS];
		int m_aPartColors[NUM_SKINPARTS];
		int m_aUseCustomColors[NUM_SKINPARTS];

		bool operator<(const CSkin &Other) const { return str_comp_nocase(m_aName, Other.m_aName) < 0; }
		bool operator==(const CSkin &Other) const { return !str_comp(m_aName, Other.m_aName); }
	};

	static const char *const ms_apSkinPartNames[NUM_SKINPARTS];
	static const char *const ms_apColorComponents[NUM_COLOR_COMPONENTS];

	static char *ms_apSkinVariables[NUM_DUMMIES][NUM_SKINPARTS];
	static int *ms_apUCCVariables[NUM_DUMMIES][NUM_SKINPARTS]; // use custom color
	static int *ms_apColorVariables[NUM_DUMMIES][NUM_SKINPARTS];
	IGraphics::CTextureHandle m_XmasHatTexture;
	IGraphics::CTextureHandle m_BotTexture;

	int GetInitAmount() const;
	void OnInit() override;

	void AddSkin(const char *pSkinName, int Dummy);
	void RemoveSkin(const CSkin *pSkin);

	int Num();
	int NumSkinPart(int Part);
	const CSkin *Get(int Index);
	int Find(const char *pName, bool AllowSpecialSkin);
	const CSkinPart *GetSkinPart(int Part, int Index);
	int FindSkinPart(int Part, const char *pName, bool AllowSpecialPart);
	void RandomizeSkin(int Dummy);

	vec3 GetColorV3(int v) const;
	vec4 GetColorV4(int v, bool UseAlpha) const;
	int GetTeamColor(int UseCustomColors, int PartColor, int Team, int Part) const;

	// returns true if everything was valid and nothing changed
	bool ValidateSkinParts(char *apPartNames[NUM_SKINPARTS], int *pUseCustomColors, int *pPartColors, int GameFlags) const;

	bool SaveSkinfile(const char *pSaveSkinName, int Dummy);

	virtual int Sizeof() const override { return sizeof(*this); }

private:
	int m_ScanningPart;
	std::vector<CSkinPart> m_aaSkinParts[NUM_SKINPARTS];
	std::vector<CSkin> m_aSkins;
	CSkin m_DummySkin;

	static int SkinPartScan(const char *pName, int IsDir, int DirType, void *pUser);
	static int SkinScan(const char *pName, int IsDir, int DirType, void *pUser);
};

#endif
