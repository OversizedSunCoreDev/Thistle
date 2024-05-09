// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ThistleDispatch.generated.h"

/**
 * Component for running the dispatch of tasks to units, allowing us to mix Mass and Behaviortree and Statetree
 * transparently, as well as shim RPAI if we like that. Might not be useful at all, see other headers for more!
 */
UCLASS()
class THISTLERUNTIME_API UThistleDispatch : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
};
