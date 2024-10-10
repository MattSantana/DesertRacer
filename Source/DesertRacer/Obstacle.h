#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "MyGameMode.h"
#include "Sound/SoundBase.h"

#include "Obstacle.generated.h"


UCLASS()
class DESERTRACER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* ObstacleSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool IsFinishLine = false;

	AObstacle();

	AMyGameMode* MyGameMode;


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult );
};
