#include "SCPlayerCharacter.h"
#include "SCVehiclePawn.h"
#include "SCGameMode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "EngineUtils.h"

ASCPlayerCharacter::ASCPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 320.f;
    CameraBoom->bUsePawnControlRotation = true;
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0,540,0);
    GetCharacterMovement()->JumpZVelocity = 620.f;
    GetCharacterMovement()->AirControl = .35f;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded())
    {
        BodyVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyVisual"));
        BodyVisual->SetupAttachment(RootComponent);
        BodyVisual->SetStaticMesh(Cube.Object);
        BodyVisual->SetRelativeLocation(FVector(0,0,5));
        BodyVisual->SetRelativeScale3D(FVector(.55f,.42f,.85f));
        BodyVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        HeadVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadVisual"));
        HeadVisual->SetupAttachment(RootComponent);
        HeadVisual->SetStaticMesh(Cube.Object);
        HeadVisual->SetRelativeLocation(FVector(0,0,83));
        HeadVisual->SetRelativeScale3D(FVector(.32f,.32f,.32f));
        HeadVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        LegVisualA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LegVisualA"));
        LegVisualA->SetupAttachment(RootComponent);
        LegVisualA->SetStaticMesh(Cube.Object);
        LegVisualA->SetRelativeLocation(FVector(0,-15,-55));
        LegVisualA->SetRelativeScale3D(FVector(.25f,.18f,.55f));
        LegVisualA->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        LegVisualB = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LegVisualB"));
        LegVisualB->SetupAttachment(RootComponent);
        LegVisualB->SetStaticMesh(Cube.Object);
        LegVisualB->SetRelativeLocation(FVector(0,15,-55));
        LegVisualB->SetRelativeScale3D(FVector(.25f,.18f,.55f));
        LegVisualB->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void ASCPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASCPlayerCharacter::SetupPlayerInputComponent(UInputComponent* Input)
{
    Super::SetupPlayerInputComponent(Input);
    Input->BindAxis("MoveForward", this, &ASCPlayerCharacter::MoveForward);
    Input->BindAxis("MoveRight", this, &ASCPlayerCharacter::MoveRight);
    Input->BindAxis("Turn", this, &ASCPlayerCharacter::Turn);
    Input->BindAxis("LookUp", this, &ASCPlayerCharacter::LookUp);
    Input->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    Input->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    Input->BindAction("Sprint", IE_Pressed, this, &ASCPlayerCharacter::StartSprint);
    Input->BindAction("Sprint", IE_Released, this, &ASCPlayerCharacter::StopSprint);
    Input->BindAction("Crouch", IE_Pressed, this, &ASCPlayerCharacter::ToggleCrouch);
    Input->BindAction("Interact", IE_Pressed, this, &ASCPlayerCharacter::Interact);
    Input->BindAction("WantedTest", IE_Pressed, this, &ASCPlayerCharacter::TriggerWantedTest);
}

void ASCPlayerCharacter::MoveForward(float V)
{
    if (!Controller || FMath::IsNearlyZero(V)) return;
    FRotator Yaw(0, Controller->GetControlRotation().Yaw, 0);
    AddMovementInput(FRotationMatrix(Yaw).GetUnitAxis(EAxis::X), V);
}
void ASCPlayerCharacter::MoveRight(float V)
{
    if (!Controller || FMath::IsNearlyZero(V)) return;
    FRotator Yaw(0, Controller->GetControlRotation().Yaw, 0);
    AddMovementInput(FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y), V);
}
void ASCPlayerCharacter::Turn(float V) { AddControllerYawInput(V); }
void ASCPlayerCharacter::LookUp(float V) { AddControllerPitchInput(V); }
void ASCPlayerCharacter::StartSprint() { GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }
void ASCPlayerCharacter::StopSprint() { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }
void ASCPlayerCharacter::ToggleCrouch() { bIsCrouched ? UnCrouch() : Crouch(); }

void ASCPlayerCharacter::Interact()
{
    ASCVehiclePawn* Closest = nullptr;
    float Best = 350.f;
    for (TActorIterator<ASCVehiclePawn> It(GetWorld()); It; ++It)
    {
        const float D = FVector::Dist(GetActorLocation(), It->GetActorLocation());
        if (D < Best) { Best = D; Closest = *It; }
    }
    if (Closest && Controller)
    {
        SetHiddenForVehicle(true);
        Controller->Possess(Closest);
        Closest->SetDriver(this);
    }
}

void ASCPlayerCharacter::SetHiddenForVehicle(bool bHidden)
{
    SetActorHiddenInGame(bHidden);
    SetActorEnableCollision(!bHidden);
}

void ASCPlayerCharacter::TriggerWantedTest()
{
    if (ASCGameMode* GM = GetWorld()->GetAuthGameMode<ASCGameMode>())
    {
        GM->AddWanted(1);
    }
}
