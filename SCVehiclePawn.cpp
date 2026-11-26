#include "SCVehiclePawn.h"
#include "SCPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"

ASCVehiclePawn::ASCVehiclePawn()
{
    PrimaryActorTick.bCanEverTick = true;
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    SetRootComponent(CollisionBox);
    CollisionBox->SetBoxExtent(FVector(150,75,55));
    CollisionBox->SetCollisionProfileName(TEXT("Pawn"));
    VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
    VehicleMesh->SetupAttachment(CollisionBox);
    VehicleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded())
    {
        VehicleMesh->SetStaticMesh(Cube.Object);
        VehicleMesh->SetRelativeScale3D(FVector(1.5f,.75f,.45f));
        VehicleMesh->SetRelativeLocation(FVector(0,0,0));
    }
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("VehicleCameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 600.f;
    CameraBoom->bUsePawnControlRotation = true;
    VehicleCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VehicleCamera"));
    VehicleCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    VehicleCamera->bUsePawnControlRotation = false;
    AutoPossessPlayer = EAutoReceiveInput::Disabled;
}

void ASCVehiclePawn::Tick(float Delta)
{
    Super::Tick(Delta);
    Speed += ThrottleInput * Acceleration * Delta;
    Speed = FMath::Clamp(Speed, -MaxSpeed * .35f, MaxSpeed);
    Speed = FMath::FInterpTo(Speed, 0.f, Delta, ThrottleInput == 0.f ? .35f : .05f);
    const float SteeringScale = FMath::Clamp(FMath::Abs(Speed) / 800.f, .15f, 1.f);
    AddActorLocalRotation(FRotator(0.f, SteeringInput * 75.f * SteeringScale * Delta * FMath::Sign(Speed == 0 ? 1 : Speed), 0.f));
    const FVector DeltaMove = GetActorForwardVector() * Speed * Delta;
    AddActorWorldOffset(DeltaMove, true);
}

void ASCVehiclePawn::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);
    Input->BindAxis("MoveForward", this, &ASCVehiclePawn::Throttle);
    Input->BindAxis("MoveRight", this, &ASCVehiclePawn::Steer);
    Input->BindAction("Interact", IE_Pressed, this, &ASCVehiclePawn::ExitVehicle);
}
void ASCVehiclePawn::Throttle(float V) { ThrottleInput = V; }
void ASCVehiclePawn::Steer(float V) { SteeringInput = V; }
void ASCVehiclePawn::SetDriver(ASCPlayerCharacter* InDriver) { Driver = InDriver; }

void ASCVehiclePawn::ExitVehicle()
{
    if (!Driver || !Controller) return;
    const FVector ExitLoc = GetActorLocation() + GetActorRightVector() * 220.f + FVector(0,0,100.f);
    ASCPlayerCharacter* NewCharacter = GetWorld()->SpawnActor<ASCPlayerCharacter>(ASCPlayerCharacter::StaticClass(), ExitLoc, GetActorRotation());
    if (NewCharacter)
    {
        Controller->Possess(NewCharacter);
        Driver = nullptr;
    }
}
