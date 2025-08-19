// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"

// Add default functionality here for any ICollectible functions that are not pure virtual.

bool ICollectible::OnDirectCollect_Implementation()
{
	return false;
}

bool ICollectible::OnLoop_Implementation()
{
	return false;
}