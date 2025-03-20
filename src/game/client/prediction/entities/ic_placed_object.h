#pragma once

#include <game/client/prediction/entities/ic_entity.h>

enum class EIcObjectType
{
	CUSTOM,
	LASER_WALL,
	LOOPER_WALL,
	SOLDIER_BOMB,
	SCIENTIST_MINE,
	BIOLOGIST_MINE,
	MERCENARY_BOMB,
	TURRET,
};

EIcObjectType GetIcObjectTypeFromInt(int value);

class CIcPlacedObject : public CIcEntity
{
public:
	CIcPlacedObject(CGameWorld *pGameWorld, int Id, EIcObjectType ObjectType, vec2 Pos, int Owner, int ProximityRadius);

	bool Match(const CIcPlacedObject *pEntity) const;
	void Read(const CIcPlacedObject &Source);

	void MoveTo(const vec2 &Position) override;

	bool HasSecondPosition() const { return m_Pos2.has_value(); }
	vec2 SecondPosition() const { return m_Pos2.value_or(m_Pos); }
	void SetSecondPosition(vec2 Position);

	EIcObjectType IcObjectType() const { return m_IcObjectType; }
	void Tick() override;

protected:
	std::optional<vec2> m_Pos2;
	EIcObjectType m_IcObjectType{};
	int m_InfClassObjectFlags = 0;
};
