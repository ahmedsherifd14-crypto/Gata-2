#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SCVehiclePawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class ASCPlayerCharacter;

UCLASS()
class SANCLEMENTE_API ASCVehiclePawn : public APawn
{
    GENERATED_BODY()
public:
    ASCVehiclePawn();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    void SetDriver(ASCPlayerCharacter* InDriver);
protected:
    void Throttle(float Value);
    void Steer(float Value);
    void ExitVehicle();
    UPROPERTY(VisibleAnywhere) TObjectPtr<UBoxComponent> CollisionBox;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> VehicleMesh;
    UPROPERTY(VisibleAnywhere) TObjectPtr<USpringArmComponent> CameraBoom;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UCameraComponent> VehicleCamera;
    UPROPERTY() TObjectPtr<ASCPlayerCharacter> Driver;
    float ThrottleInput = 0.f;
    float SteeringInput = 0.f;
    float Speed = 0.f;
    UPROPERTY(EditAnywhere, Category="Vehicle") float MaxSpeed = 2600.f;
    UPROPERTY(EditAnywhere, Category="Vehicle") float Acceleration = 1500.f;
};
