
#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	//attaching the camera to the final point of the spring arm component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName );

	CarSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CarSprite"));
	CarSprite->SetupAttachment(RootComponent);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController * PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		//I need the Subsystem to use the AddMappingContext method, and add it tho the player. That's what i'm doing here
		UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if(Subsystem)
		{ 
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// i need to cast the UInputComponent to a EnhancedInput Component. So i can use the bind Method and get support to the Input Actions and modifeirs.
	UEnhancedInputComponent * EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		//binding the MoveAction to the Move Method
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	}

}
void APlayerCharacter::Move(const FInputActionValue& Value)
{

		FVector2D MoveActionValue = Value.Get<FVector2D>();

		//GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::White, MoveActionValue.ToString());

		if (CanMove)
		{
			//this will return true if W or S is pressed
			if (abs(MoveActionValue.Y) > 0.0f)
			{
				float DeltaTime = GetWorld()->DeltaTimeSeconds;

				FVector CurrentLocation = GetActorLocation();
				FVector DistanceToMove = GetActorUpVector() * MovementSpeed * MoveActionValue.Y * DeltaTime;

				FVector NewLocation = CurrentLocation + DistanceToMove;
				SetActorLocation(NewLocation);
			}
		}
}
