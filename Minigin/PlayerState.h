#pragma once
class PlayerState
{
	 
public:

	virtual void HandleInput() = 0;
	virtual void Update() = 0;
};
class JumpingState final : PlayerState
{
	// Inherited via PlayerState
	virtual void HandleInput() override;
	virtual void Update() override;
};
class ClimbState final : PlayerState
{
	// Inherited via PlayerState
	virtual void HandleInput() override;

	virtual void Update() override;


};