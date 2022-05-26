#pragma once

enum class Event
{
	ActorDied,
	EnemyDies,
	BurgerDrops,
	MrHotDog,
	MrPickle,
	MrEgg,
	DropBurgerWithOneEnemy,
	DropBurgerWithTwoEnemy,
	DropBurgerWithThreeEnemy,
	DropBurgerWithFourEnemy,
	DropBurgerWithFiveEnemy,
	DropBurgerWithSixEnemy,

};
enum class State
{
	ActorDied,
	ActorClimbUp,
	ActorClimbDown
};