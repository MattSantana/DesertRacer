#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"


void AMyGameMode::ResetLevel(bool IsWin) 
{
	float ResetTime = LoseResetTime;
	if (IsWin)
	{
		ResetTime = WinResetTime;
	}

	GetWorldTimerManager().SetTimer(ResetGameTimer, this, &AMyGameMode::OnResetGameTimerTimeout, 1.0f, false,
		ResetTime);
}
void AMyGameMode::OnResetGameTimerTimeout()
{
	//starting the scene with this name
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
}