#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SCGameMode.generated.h"

UCLASS()
class SANCLEMENTE_API ASCGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    ASCGameMode();
    virtual void BeginPlay() override;
    UFUNCTION(BlueprintCallable) void AddMoney(int32 Amount);
    UFUNCTION(BlueprintCallable) void AddWanted(int32 Stars);
    UFUNCTION(BlueprintCallable) void CompleteCheckpoint();
    UFUNCTION(BlueprintCallable) FString GetObjective() const { return Objective; }
    UFUNCTION(BlueprintCallable) int32 GetMoney() const { return Money; }
    UFUNCTION(BlueprintCallable) int32 GetWantedStars() const { return WantedStars; }
private:
    int32 Money = 250;
    int32 WantedStars = 0;
    int32 CheckpointsDone = 0;
    FString Objective = TEXT("Reach the glowing checkpoint");
};
