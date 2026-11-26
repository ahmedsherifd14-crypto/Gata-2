#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCMissionCheckpoint.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class SANCLEMENTE_API ASCMissionCheckpoint : public AActor
{
    GENERATED_BODY()
public:
    ASCMissionCheckpoint();
protected:
    UFUNCTION() void OnCheckpointOverlap(UPrimitiveComponent* Overlapped, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep);
    UPROPERTY(VisibleAnywhere) TObjectPtr<UBoxComponent> Trigger;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> Marker;
    bool bCompleted = false;
};
