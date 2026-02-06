// Fill out your copyright notice in the Description page of Project Settings.


#include "Mamepetto.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMamepetto::AMamepetto()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MamepettoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mame mesh"));

	Hunger = 100;
	Tiredness = 90;
	Toilet = 5;

	MoveSpeed = 100.f;

	bCanSeeFood = false;

	SubTick = 0;

	Direction = DirectionState::IDLE;
}

// Called when the game starts or when spawned
void AMamepetto::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("Hello World"));

}

void AMamepetto::PrintStats()
{
	if (GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.5f, FColor::Cyan, FString::Printf(TEXT("Hunger = %d"), Hunger));
		GEngine->AddOnScreenDebugMessage(2, 1.5f, FColor::Red, FString::Printf(TEXT("Tiredness = %d"), Tiredness));
		GEngine->AddOnScreenDebugMessage(3, 1.5f, FColor::Green, FString::Printf(TEXT("Bladder = %d"), Toilet));
	}
}

void AMamepetto::MameUpdateStats()
{
	Hunger--;
	Tiredness--;
	Toilet--;
}


// Called every frame
void AMamepetto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Movement(DeltaTime);

	if (SubTick > 99)
	{
		MameUpdateStats();
		PrintStats();
		CheckForFood();
		Direction = DirectionState(FMath::RandRange(0, 8));

		SubTick = 0;
	}

	SubTick++;
}

void AMamepetto::CheckForFood()
{
	TSubclassOf<AActor> WorldClassObject = AItem::StaticClass();

	TArray<AActor*> FoodItems;

	UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, FoodItems);

	//if(GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(6, 1.5f, FColor::Magenta, FString::Printf(TEXT("Number of Items = %d"), FoodItems.Num()));
	//}

	if (FoodItems.Num() > 0)
	{
		ItemTarget = Cast<AItem>(FoodItems[0]);
		FoodTarget = FoodItems[0]->GetActorLocation();
		bCanSeeFood = true;
	}
	else
	{
		bCanSeeFood = false;
	}
}

void AMamepetto::Movement(float DeltaTime)
{
	FVector Location = GetActorLocation();

	int VectorDifference = 0;

	if (Location.X >= 400)
	{
		Direction = DirectionState::SOUTH;
	}
	else if (Location.X <= -400)
	{
		Direction = DirectionState::NORTH;
	}
	if (Location.Y >= 400)
	{
		Direction = DirectionState::WEST;
	}
	else if (Location.Y <= -400)
	{
		Direction = DirectionState::EAST;
	}

	if (bCanSeeFood == true)
	{
		if (Location.X > FoodTarget.X)
		{
			Location.X -= MoveSpeed * DeltaTime;
			VectorDifference += Location.X - FoodTarget.X;
		}
		else
		{
			Location.X += MoveSpeed * DeltaTime;
			VectorDifference += FoodTarget.X - Location.X;
		}
		
		if (Location.Y > FoodTarget.Y)
		{
			Location.Y -= MoveSpeed * DeltaTime;
			VectorDifference += Location.Y - FoodTarget.Y;
		}
		else
		{
			Location.Y += MoveSpeed * DeltaTime;
			VectorDifference += FoodTarget.Y - Location.Y;
		}

		if (VectorDifference < 20)
		{
			Hunger += ItemTarget->GetFoodValue();
			ItemTarget->Destroy();
		}



	}
	else
	{
		switch (Direction)
		{
		case DirectionState::IDLE:
			break;

		case DirectionState::NORTH:
			Location.X += MoveSpeed * DeltaTime;
			break;

		case DirectionState::NORTHEAST:
			Location.X += (MoveSpeed / 2) * DeltaTime;
			Location.Y += (MoveSpeed / 2) * DeltaTime;
			break;

		case DirectionState::EAST:
			Location.Y += MoveSpeed * DeltaTime;
			break;

		case DirectionState::SOUTHEAST:
			Location.X -= (MoveSpeed / 2) * DeltaTime;
			Location.Y += (MoveSpeed / 2) * DeltaTime;
			break;

		case DirectionState::SOUTH:
			Location.X -= MoveSpeed * DeltaTime;
			break;

		case DirectionState::SOUTHWEST:
			Location.X -= (MoveSpeed / 2) * DeltaTime;
			Location.Y -= (MoveSpeed / 2) * DeltaTime;
			break;

		case DirectionState::WEST:
			Location.Y -= MoveSpeed * DeltaTime;
			break;

		case DirectionState::NORTHWEST:
			Location.X += (MoveSpeed / 2) * DeltaTime;
			Location.Y -= (MoveSpeed / 2) * DeltaTime;
			break;
		}

	}

	SetActorLocation(Location);
}
