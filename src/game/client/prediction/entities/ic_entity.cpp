#include "ic_entity.h"

CIcEntity::CIcEntity(CGameWorld *pGameWorld, int Id, int ObjectType, vec2 Pos, std::optional<int> Owner,
	int ProximityRadius) :
	CEntity(pGameWorld, ObjectType, Pos, ProximityRadius)
{
	SetOwner(Owner.value_or(-1));
	m_Id = Id;
}

bool CIcEntity::Match(const CIcEntity *pEntity) const
{
	return m_Owner == pEntity->m_Owner && m_Pos == pEntity->m_Pos;
}

void CIcEntity::Read(const CIcEntity &Source)
{
	m_EndTick = Source.m_EndTick;
}

void CIcEntity::SetStartTick(int Tick)
{
}

void CIcEntity::SetEndTick(int Tick)
{
}

void CIcEntity::SetOwner(int ClientId)
{
	if(ClientId < 0)
	{
		m_Owner.reset();
	}
	else
	{
		m_Owner = ClientId;
	}
}

CCharacter *CIcEntity::GetOwnerCharacter()
{
	return m_Owner.has_value() ? GameWorld()->GetCharacterById(m_Owner.value()) : nullptr;
}

void CIcEntity::Tick()
{
	if(m_EndTick.has_value() && (GameWorld()->GameTick() >= m_EndTick))
	{
		GameWorld()->DestroyEntity(this);
		return;
	}

	m_Pos += m_Velocity;
}

void CIcEntity::MoveTo(const vec2 &Position)
{
	SetPos(Position);
}

void CIcEntity::SetPos(const vec2 &Position)
{
	m_Pos = Position;
}

float CIcEntity::GetLifespan() const
{
	if(!m_EndTick.has_value())
		return -1;

	int RemainingTicks = m_EndTick.value_or(0) - GameWorld()->GameTick();
	return RemainingTicks <= 0 ? 0 : RemainingTicks / static_cast<float>(GameWorld()->GameTickSpeed());
}

void CIcEntity::SetLifespan(float Lifespan)
{
	m_EndTick = GameWorld()->GameTick() + GameWorld()->GameTickSpeed() * Lifespan;
}

void CIcEntity::ResetLifespan()
{
	m_EndTick.reset();
}
