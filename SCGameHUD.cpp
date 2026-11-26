#include "SCGameHUD.h"
#include "SCGameMode.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

void ASCGameHUD::DrawHUD()
{
    Super::DrawHUD();
    if (!Canvas) return;
    const ASCGameMode* GM = GetWorld()->GetAuthGameMode<ASCGameMode>();
    if (!GM) return;
    const float X=36.f, Y=36.f;
    DrawText(TEXT("SAN CLEMENTE  |  OPEN WORLD"), FLinearColor::White, X, Y, nullptr, 1.2f, false);
    DrawText(FString::Printf(TEXT("$%d"), GM->GetMoney()), FLinearColor(0.2f,1.f,.35f,1.f), X, Y+30.f, nullptr, 1.3f, false);
    DrawText(FString::Printf(TEXT("WANTED: %d / 6"), GM->GetWantedStars()), FLinearColor(1.f,.8f,.1f,1.f), X, Y+62.f, nullptr, 1.1f, false);
    DrawText(GM->GetObjective(), FLinearColor::White, X, Y+100.f, nullptr, 1.0f, false);
    DrawText(TEXT("WASD Move | Mouse Look | Shift Sprint | Space Jump | Ctrl Crouch | E Enter/Exit | F6 Wanted Test"),
        FLinearColor(.8f,.85f,1.f,1.f), X, Canvas->SizeY-42.f, nullptr, .85f, false);
}
