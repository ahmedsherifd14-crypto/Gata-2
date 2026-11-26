#include "SCMissionCheckpoint.h"
#include "SCGameMode.h"
#include "SCPlayerCharacter.h"
#include "SCVehiclePawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

ASCMissionCheckpoint::ASCMissionCheckpoint()
{
    PrimaryActorTick.bCanEverTick = false;
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    SetRootComponent(Trigger);
    Trigger->SetBoxExtent(FVector(180,180,160));
    Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASCMissionCheckpoint::OnCheckpointOverlap);
    Marker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Marker"));
    Marker->SetupAttachment(RootComponent);
    Marker->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded())
    {
        Marker->SetStaticMesh(Cube.Object);
        Marker->SetRelativeScale3D(FVector(.8f,.8f,2.2f));
    }
}

void ASCMissionCheckpoint::OnCheckpointOverlap(UPrimitiveComponent*, AActor* OtherActor,
    UPrimitiveComponent*, int32, bool, const FHitResult&)
{
    if (bCompleted || (!Cast<ASCPlayerCharacter>(OtherActor) && !Cast<ASCVehiclePawn>(OtherActor))) return;
    bCompleted = true;
    if (ASCGameMode* GM = GetWorld()->GetAuthGameMode<ASCGameMode>())
    {
        GM->CompleteCheckpoint();
    }
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
}
