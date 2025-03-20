#include "ic_placed_object.h"

EIcObjectType GetIcObjectTypeFromInt(int Value)
{
	if(Value < 0 || Value > static_cast<int>(EIcObjectType::TURRET))
		return EIcObjectType::CUSTOM;

	return static_cast<EIcObjectType>(Value);
}

CIcPlacedObject::CIcPlacedObject(CGameWorld *pGameWorld, int Id, EIcObjectType ObjectType, vec2 Pos, int Owner, int ProximityRadius) :
	CIcEntity(pGameWorld, Id, CGameWorld::ENTTYPE_IC_PLACED_OBJECT, Pos, Owner, ProximityRadius),
	m_IcObjectType(ObjectType)
{
}

bool CIcPlacedObject::Match(const CIcPlacedObject *pEntity) const
{
	if(!CIcEntity::Match(pEntity))
		return false;

	if(m_IcObjectType != pEntity->m_IcObjectType)
		return false;

	return true;
}

void CIcPlacedObject::Read(const CIcPlacedObject &Source)
{
	CIcEntity::Read(Source);
	m_Pos2 = Source.m_Pos2;
	m_InfClassObjectFlags = Source.m_InfClassObjectFlags;
}

void CIcPlacedObject::MoveTo(const vec2 &Position)
{
	if(m_Pos2.has_value())
	{
		vec2 Difference = Position - m_Pos;
		CIcEntity::MoveTo(Position);
		m_Pos2 = m_Pos2.value() + Difference;
	}
}

void CIcPlacedObject::SetSecondPosition(vec2 Position)
{
	m_Pos2 = Position;
	m_InfClassObjectFlags = INFCLASS_OBJECT_FLAG_HAS_SECOND_POSITION;
}

void CIcPlacedObject::Tick()
{
	CIcEntity::Tick();

	if(m_Pos2.has_value())
	{
		m_Pos2.value() += m_Velocity;
	}
}
