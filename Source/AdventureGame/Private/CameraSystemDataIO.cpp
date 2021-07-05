// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSystemDataIO.h"

CameraSystemDataIO::CameraSystemDataIO()
{
	
}

CameraSystemDataIO::~CameraSystemDataIO()
{
}

FString CameraSystemDataIO::GetProjectDirectory()
{
	ProjectDirectory = FPaths::ProjectDir();
	
	return ProjectDirectory;
}

