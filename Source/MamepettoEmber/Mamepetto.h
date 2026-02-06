// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Mamepetto.generated.h"

UCLASS()
class MAMEPETTOEMBER_API AMamepetto : public AActor
{
	GENERATED_BODY()

	enum class DirectionState : int8
	{
		IDLE,
		NORTH,
		NORTHEAST,
		EAST,
		SOUTHEAST,
		SOUTH,
		SOUTHWEST,
		WEST,
		NORTHWEST

	};
	
public:	
	// Sets default values for this actor's properties
	AMamepetto();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* MamepettoMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tick")
	float MoveSpeed;

	class AItem* ItemTarget;


	void PrintStats();
	void MameUpdateStats();

private:
	int Hunger;
	int Tiredness;
	int Toilet;

	int SubTick;

	bool bCanSeeFood;

	FVector FoodTarget;

	DirectionState Direction;

	void CheckForFood();
	void Movement(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
