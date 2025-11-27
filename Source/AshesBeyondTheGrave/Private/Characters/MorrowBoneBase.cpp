// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MorrowBoneBase.h"

// Sets default values
AMorrowBoneBase::AMorrowBoneBase()
{
 	//in this version of the Game our character don't need decals and the tick.
	PrimaryActorTick.bCanEverTick = false;

	//set the decals false
	 GetMesh()->SetReceivesDecals(false);

}



