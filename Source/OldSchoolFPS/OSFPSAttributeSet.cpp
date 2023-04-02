// Fill out your copyright notice in the Description page of Project Settings.


#include "OSFPSAttributeSet.h"
#include "OSFPSCharacter.h"

UOSFPSAttributeSet::UOSFPSAttributeSet()
{

}

void UOSFPSAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	AOSFPSCharacter* RetroChar = Cast<AOSFPSCharacter>(GetOwningActor());

	if(Attribute  == GetHealthAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, RetroChar->MaxHealth);
	else if (Attribute == GetArmourAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, RetroChar->MaxArmour);
	else if(Attribute  == GetBulletsAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, RetroChar->MaxBullets);
	else if(Attribute  == GetRocketsAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, RetroChar->MaxRockets);
}

bool UOSFPSAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	float AbsoluteMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude);

	AOSFPSCharacter* RetroChar = Cast<AOSFPSCharacter>(GetOwningActor());

	if (Data.EvaluatedData.Magnitude > 0)
	{
		if (Data.EvaluatedData.Attribute == GetArmourAttribute() && GetArmour() + AbsoluteMagnitude >= RetroChar->MaxArmour)
		{
			SetArmour(RetroChar->MaxArmour);
			return false;
		}

		else if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() + AbsoluteMagnitude >= RetroChar->MaxHealth)
		{
			SetHealth(RetroChar->MaxHealth);
			return false;
		}
		else if (Data.EvaluatedData.Attribute == GetBulletsAttribute() && GetBullets() + AbsoluteMagnitude >= RetroChar->MaxBullets)
		{
			SetBullets(RetroChar->MaxBullets);
			return false;
		}
		else if (Data.EvaluatedData.Attribute == GetRocketsAttribute() && GetRockets() + AbsoluteMagnitude >= RetroChar->MaxRockets)
		{
			SetRockets(RetroChar->MaxRockets);
			return false;
		}
	}

	else if (Data.EvaluatedData.Magnitude < 0)
	{
		if (Data.EvaluatedData.Attribute == GetArmourAttribute() && AbsoluteMagnitude > GetArmour())
			Health.SetCurrentValue(Health.GetCurrentValue() - (AbsoluteMagnitude - GetArmour()));
	}
    return true;
}

void UOSFPSAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() < 0)
		SetHealth(0);
	else if (Data.EvaluatedData.Attribute == GetArmourAttribute() && GetArmour() < 0)
		SetArmour(0);
	else if (Data.EvaluatedData.Attribute == GetBulletsAttribute() && GetBullets() < 0)
		SetBullets(0);
	else if (Data.EvaluatedData.Attribute == GetRocketsAttribute() && GetRockets() < 0)
		SetRockets(0);
}
