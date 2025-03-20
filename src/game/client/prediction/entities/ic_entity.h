#ifndef GAME_CLIENT_ENTITIES_IC_ENTITY_H
#define GAME_CLIENT_ENTITIES_IC_ENTITY_H

#include <game/client/prediction/entity.h>

inline constexpr int TileSize = 32;
inline constexpr float TileSizeF = 32.0f;
inline constexpr vec2 Tile2DSize{TileSizeF, TileSizeF};
inline constexpr vec2 Tile2DHalfSize{TileSizeF / 2, TileSizeF / 2};

class CIcEntity : public CEntity
{
public:
	CIcEntity(CGameWorld *pGameWorld, int Id, int ObjectType, vec2 Pos = vec2(), std::optional<int> Owner = std::nullopt,
		int ProximityRadius = 0);

	using CEntity::GameWorld;
	const CGameWorld *GameWorld() const { return m_pGameWorld; }

	bool Match(const CIcEntity *pEntity) const;
	void Read(const CIcEntity &Source);

	int GetSnapData1() const { return m_SnapData1; }
	void SetSnapData1(int Value) { m_SnapData1 = Value; }

	void SetStartTick(int Tick);
	void SetEndTick(int Tick);

	bool HasOwner() const { return m_Owner.has_value(); }
	int GetOwner() const { return m_Owner.value_or(-1); }
	void SetOwner(int ClientId);

	CCharacter *GetOwnerCharacter();

	void Tick() override;

	virtual void MoveTo(const vec2 &Position);
	void SetPos(const vec2 &Position);

	vec2 GetVelocity() const { return m_Velocity; }
	void SetVelocity(vec2 Velocity) { m_Velocity = Velocity; }

	float GetLifespan() const;
	void SetLifespan(float Lifespan);
	void ResetLifespan();
	std::optional<int> GetEndTick() const { return m_EndTick; }

protected:
	std::optional<int> m_Owner;
	vec2 m_Velocity{};
	std::optional<int> m_EndTick;
	int m_SnapData1{};
};

#endif // GAME_CLIENT_ENTITIES_IC_ENTITY_H
