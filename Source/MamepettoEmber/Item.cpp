// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FoodValue = FMath::RandRange(10, 20);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item mesh"));
	ItemMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Item material"));

	// /Game/ItemContent

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ItemAsset(TEXT("/Game/ItemContent/Item_Mesh"));
	static ConstructorHelpers::FObjectFinder<UMaterial>ItemAssetMaterial(TEXT("/Game/ItemContent/Item_Material"));

	if (ItemAsset.Succeeded())
	{
		ItemMesh->SetStaticMesh(ItemAsset.Object);
	}
	if (ItemAssetMaterial.Succeeded())
	{
		ItemMaterial = ItemAssetMaterial.Object;

		ItemMesh->SetMaterial(0, ItemMaterial);
	}
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AItem::GetFoodValue()
{
	return 0;
}

