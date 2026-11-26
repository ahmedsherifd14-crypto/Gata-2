#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class SANCLEMENTE_API ASCPlayerCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ASCPlayerCharacter();
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    void SetHiddenForVehicle(bool bHidden);
protected:
    virtual void BeginPlay() override;
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void StartSprint();
    void StopSprint();
    void ToggleCrouch();
    void Interact();
    void TriggerWantedTest();

    UPROPERTY(VisibleAnywhere) TObjectPtr<USpringArmComponent> CameraBoom;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UCameraComponent> FollowCamera;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> BodyVisual;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> HeadVisual;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> LegVisualA;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> LegVisualB;
    UPROPERTY(EditDefaultsOnly, Category="Movement") float WalkSpeed = 450.0f;
    UPROPERTY(EditDefaultsOnly, Category="Movement") float SprintSpeed = 720.0f;
};
