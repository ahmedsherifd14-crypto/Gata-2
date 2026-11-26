#include "SCWorldBuilder.h"
#include "SCVehiclePawn.h"
#include "SCMissionCheckpoint.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

ASCWorldBuilder::ASCWorldBuilder()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASCWorldBuilder::BeginPlay()
{
    Super::BeginPlay();
    // Runtime-generated blockout district: streets, sidewalks and buildings.
    SpawnCube(FVector(0,0,-100), FVector(100,100,1));
    SpawnCube(FVector(0,0,-40), FVector(100,.12f,.12f));
    SpawnCube(FVector(0,1800,-40), FVector(100,.12f,.12f));
    SpawnCube(FVector(0,-1800,-40), FVector(100,.12f,.12f));
    SpawnCube(FVector(1800,0,-40), FVector(.12f,100,.12f));
    SpawnCube(FVector(-1800,0,-40), FVector(.12f,100,.12f));

    for (int32 X=-7; X<=7; ++X)
    {
        for (int32 Y=-7; Y<=7; ++Y)
        {
            if (FMath::Abs(X)<2 || FMath::Abs(Y)<2) continue;
            const float H = FMath::FRandRange(350.f, 1600.f);
            SpawnCube(FVector(X*900.f,Y*900.f,H*.5f-50.f), FVector(3.2f,3.2f,H/100.f));
        }
    }

    // Side streets and a few distinctive blocks.
    for (int32 I=-5; I<=5; ++I)
    {
        SpawnCube(FVector(I*900.f, 2200.f,-45.f), FVector(4.5f,.08f,.1f));
        SpawnCube(FVector(I*900.f,-2200.f,-45.f), FVector(4.5f,.08f,.1f));
    }

    GetWorld()->SpawnActor<ASCVehiclePawn>(ASCVehiclePawn::StaticClass(), FVector(250,120,80), FRotator(0,0,0));

    for (int32 I=0; I<3; ++I)
    {
        const FVector P(1000.f + I*700.f, 500.f, 60.f);
        GetWorld()->SpawnActor<ASCMissionCheckpoint>(ASCMissionCheckpoint::StaticClass(), P, FRotator::ZeroRotator);
    }
}

void ASCWorldBuilder::SpawnCube(const FVector& Location, const FVector& Scale, const FRotator& Rotation)
{
    UStaticMesh* Cube = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (!Cube) return;
    AStaticMeshActor* Actor = GetWorld()->SpawnActor<AStaticMeshActor>(Location, Rotation);
    if (!Actor) return;
    Actor->GetStaticMeshComponent()->SetStaticMesh(Cube);
    Actor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Static);
    Actor->SetActorScale3D(Scale);
}
