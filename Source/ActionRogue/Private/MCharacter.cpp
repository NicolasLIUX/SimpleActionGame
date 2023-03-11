// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"

#include <corecrt_io.h>
#include <functional>

#include "Components/SplineMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp=CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	CameraComp=CreateDefaultSubobject<UCameraComponent>("CameraComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation=true;
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon"));
	if(SkeletalMeshAsset.Succeeded())
	{
		GetMesh()->SkeletalMesh=SkeletalMeshAsset.Object;
		GetMesh()->SetRelativeLocation(FVector(0.0,0.0,-90.0));
		GetMesh()->SetRelativeRotation(FRotator(0.0,-90,0));
	}

	GetCharacterMovement()->bOrientRotationToMovement=true;
	bUseControllerRotationYaw=false;

	InteractionComp=CreateDefaultSubobject<UMInteractionComponent>("IneractionComp");
	
	AttributeComp=CreateDefaultSubobject<UMAttributeComponent>("AttributeComp");

	ActionComp=CreateDefaultSubobject<UMActionComponent>("ActionComp");

	HandleSocketName="Muzzle_01";

	TimeToHitParamName="TimeToHit";

}

// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

// Called to bind functionality to input
void AMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&AMCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&AMCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn",this,&AMCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp/Down",this,&AMCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&AMCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryIneract",IE_Pressed,this,&AMCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("BlackHole",IE_Pressed,this,&AMCharacter::BlackHoleAttack);
	PlayerInputComponent->BindAction("Dash",IE_Pressed,this,&AMCharacter::DashAttcak);


	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this,&AMCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint",IE_Released,this,&AMCharacter::SprintStop);
	
}

void AMCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this,&AMCharacter::OnHealthChanged);
}

FVector AMCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}


void AMCharacter::MoveForward(float value)
{
	FRotator ControlRot=GetControlRotation();
	ControlRot.Pitch=0.0;
	ControlRot.Roll=0.0f;
	AddMovementInput(ControlRot.Vector(),value);
	
}

void AMCharacter::MoveRight(float value)
{
	FRotator ControlRot=GetControlRotation();
	ControlRot.Pitch=0.0;
	ControlRot.Roll=0.0f;

	FVector RightVector;
	RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector,value);
}

void AMCharacter::PrimaryInteract()
{
	if(InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void AMCharacter::PrimaryAttack()
{
	ActionComp->StartActionByNname(this,"PrimaryAttack");
	// PlayAnimMontage(AttackAnim);
	//
	// GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAcctack,this,&AMCharacter::PrimaryAttack_TimeElapsed,0.2f);
	//
}



void AMCharacter::BlackHoleAttack()
{
	ActionComp->StartActionByNname(this,"BHAttack");
}


void AMCharacter::DashAttcak()
{
	ActionComp->StartActionByNname(this,"DashAttack");
}


void AMCharacter::OnHealthChanged(AActor* InstigatorActor, UMAttributeComponent* OwningComp, float Newhealth,float Delta)
{
	if(Delta<=0)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName,GetWorld()->TimeSeconds);
	}
	if(Newhealth<=0&&Delta<0)
	{
		APlayerController* PC=Cast<APlayerController>(GetController());
		DisableInput(PC);

		SetLifeSpan(5.0f);
	}
}

void AMCharacter::SprintStart()
{
	ActionComp->StartActionByNname(this,"Sprint");
}

void AMCharacter::SprintStop()
{
	ActionComp->StopActionByName(this,"Sprint");
}
