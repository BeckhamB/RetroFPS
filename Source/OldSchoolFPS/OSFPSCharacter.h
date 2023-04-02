// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"
#include "OSFPSCharacter.generated.h"

UCLASS()
class OLDSCHOOLFPS_API AOSFPSCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
		class UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
		class UOSFPSAttributeSet* Attributes;
public:
	// Sets default values for this character's properties
	AOSFPSCharacter();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int MaxArmour = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int MaxBullets = 250;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int MaxRockets = 20;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "RetroFPS")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "RetroFPS")
		TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;
};
