// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ThistleInject.generated.h"

/*
* One of the two hearts of thistle
* This is intended to be a either a slight expansion of pawn or an alternative to physicalized pawns.
* Our goal is to allow behavior trees to control squads and similar in elegant ways and that means we want
* something that lets large numbers of actors subscribe to and fulfill tasks from Mass and BehaviorTrees.
* 
* It's TOTALLY possible this'll prove a hassle or that we can use the InjectionComponent here in thistle instead. 
* That latter option? it'd be ideologically preferable, as a pawn is a pretty heavyweight inheritance\asset chunk 
* that basically ends up at least partially owning the rigid body, though often NOT the mesh. I've seen projects 
* that ended up with quite a few pawns in an asset's hierarchy, and that was..... grim.
* 
* Traditionally, this sort of stuff works by building infrastructure around AIControllers. See:
* https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/AIModule/AAIController
* 
* For us, we'd like to stick with that core paradigm absolutely as much as possible, but we have a problem:
* AIControllers normally only run on the server in networked games.
* 
* There are VERY good reasons for this. It's borderline impossible to make a truly deterministic game otherwise,
* without the aggressive use of rollback and network prediction. This can lead to situations where an AI actor shoots
* one character on their player's machine, and another on some other player's machine. Reconciling this in a network-predicted
* game is really quite unpleasant. A lot of thought and work has gone into it, and Iris has powerful support for it.
* 
* The problem is that we don't really want to have our AI run at such a delay, and we'd really like to clock our server quite slow.
* 
* There are four good solves: 
*	Have the AI produce slightly longer tasks than usual.
*	Manage only tasks that must be coherent across all players on the server-side.
*	Grin and bear it, and hope that the fully server defaults are fast enough.
*	Mad shit. Destiny 2 style.
* 
* It's not clear to me which way to go yet. If we go with 3, this component is just an attachment point for the standard AI controller
* or a way of consuming commands from it in the case of a squad. This isn't the worst! Actually, it's pretty good!
* 
* Of probable interest are:
* https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/AIModule/BehaviorTree/Tasks/UBTTask_RunBehavior
* https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/AIModule/BehaviorTree/Tasks/UBTTask_MoveTo
* 
* 
* Mass Entity and Mass Avoidance:
* https://dev.epicgames.com/documentation/en-us/unreal-engine/overview-of-mass-entity-in-unreal-engine
* https://dev.epicgames.com/documentation/en-us/unreal-engine/mass-avoidance-overview-in-unreal-engine
* https://dev.epicgames.com/community/learning/tutorials/JXMl/unreal-engine-your-first-60-minutes-with-mass
* 
*/


UCLASS()
class THISTLERUNTIME_API AThistleInject : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AThistleInject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
