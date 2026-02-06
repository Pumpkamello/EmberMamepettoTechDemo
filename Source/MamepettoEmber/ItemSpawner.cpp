// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < 4; i++)
	{
		SpawnItems();
	}
}

void AItemSpawner::SpawnItems()
{
	SpawnPoint = FVector(FMath::RandRange(-400, 400), FMath::RandRange(-400, 400), 70);

	SpawnParams.OverrideLevel = GetLevel();

	AItem* SpawnedItem = (AItem*)GetWorld()->SpawnActor(AItem::StaticClass(), &SpawnPoint, &SpawnRot, SpawnParams);
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (FMath::RandRange(0, 999) == 1)
	{
		SpawnItems();
	}
}

