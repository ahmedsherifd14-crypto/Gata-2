#include "SCGameMode.h"
#include "SCPlayerCharacter.h"
#include "SCWorldBuilder.h"
#include "SCGameHUD.h"
#include "Engine/World.h"

ASCGameMode::ASCGameMode()
{
    DefaultPawnClass = ASCPlayerCharacter::StaticClass();
    HUDClass = ASCGameHUD::StaticClass();
}

void ASCGameMode::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->SpawnActor<ASCWorldBuilder>(ASCWorldBuilder::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
}

void ASCGameMode::AddMoney(int32 Amount)
{
    Money = FMath::Max(0, Money + Amount);
}

void ASCGameMode::AddWanted(int32 Stars)
{
    WantedStars = FMath::Clamp(WantedStars + Stars, 0, 6);
}

void ASCGameMode::CompleteCheckpoint()
{
    ++CheckpointsDone;
    AddMoney(500);
    if (CheckpointsDone >= 3)
    {
        CheckpointsDone = 0;
        Objective = TEXT("Neighborhood route complete! Find the next checkpoint");
    }
    else
    {
        Objective = FString::Printf(TEXT("Checkpoint %d/3 complete - continue the route"), CheckpointsDone);
    }
}
