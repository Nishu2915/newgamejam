#pragma once

UENUM(BlueprintType)
enum class ECharState : uint8
{
	ECS_unequipped,
	ECS_EquippedHammer,
	ECS_HammerAtBack
};

UENUM(BlueprintType)
enum class EAttackingState : uint8
{
	ECS_NotAttacking,
	ECS_Attacking
};

UENUM(BlueprintType)
enum class EquipingState : uint8
{
	ECS_NotEquiping,
	ECS_Equiping
};