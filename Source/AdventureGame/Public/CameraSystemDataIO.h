// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ADVENTUREGAME_API CameraSystemDataIO
{
public:

	FString ProjectDirectory;
	
	CameraSystemDataIO();
	
	~CameraSystemDataIO();

	FString GetProjectDirectory();

private:
	
};
