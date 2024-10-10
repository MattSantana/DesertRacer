#include "Obstacle.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	ObstacleSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ObstacleSprite"));
	ObstacleSprite->SetupAttachment(RootComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	//The Ampersand is a way to also get a adress of a function.
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OverlapBegin);
	
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	MyGameMode =  Cast<AMyGameMode>(GameMode);
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		//Debug Example
		//GEngine->AddOnScreenDebugMessage(-1, 10.0F, FColor::White, TEXT("Overlapped with Player"));
		
		if (Player->CanMove) {
			Player->CanMove = false;

			UGameplayStatics::PlaySound2D(GetWorld(), HitSound);

			MyGameMode->ResetLevel(IsFinishLine);
		}
		
	}
}