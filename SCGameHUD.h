#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SCGameHUD.generated.h"

UCLASS()
class SANCLEMENTE_API ASCGameHUD : public AHUD
{
    GENERATED_BODY()
public:
    virtual void DrawHUD() override;
};
