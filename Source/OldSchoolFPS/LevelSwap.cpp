// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSwap.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALevelSwap::ALevelSwap()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	CollisionBox->SetBoxExtent(FVector(35.f, 35.f, 35.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelSwap::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ALevelSwap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelSwap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSwap::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (OtherActor == (AActor*)PlayerCharacter && LevelToLoad != "")
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::OpenLevel(this, LevelToLoad);
;	}
}

// Called to bind functionality to input
void ALevelSwap::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

