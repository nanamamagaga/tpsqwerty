// Fill out your copyright notice in the Description page of Project Settings.


#include "TempMan.h"

// Sets default values
ATempMan::ATempMan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATempMan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATempMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

