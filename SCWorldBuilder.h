#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCWorldBuilder.generated.h"

UCLASS()
class SANCLEMENTE_API ASCWorldBuilder : public AActor
{
    GENERATED_BODY()
public:
    ASCWorldBuilder();
    virtual void BeginPlay() override;
private:
    void SpawnCube(const FVector& Location, const FVector& Scale, const FRotator& Rotation = FRotator::ZeroRotator);
};
