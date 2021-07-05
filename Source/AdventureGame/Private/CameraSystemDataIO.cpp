// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSystemDataIO.h"

CameraSystemDataIO::CameraSystemDataIO()
{
	
}

CameraSystemDataIO::~CameraSystemDataIO()
{
}

void CameraSystemDataIO::CreateFile()
{
	FString myFilePath = FPaths::ProjectConfigDir();
	myFilePath.Append((TEXT("CameraSystemData/CameraData.txt")));
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (FileManager.FileExists(*myFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: File found!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: File not found!"));
		UE_LOG(LogTemp, Warning, TEXT("Let's create one..."));

		//FPaths::CreateStandardFilename(*myFilePath);
	}
}

FString CameraSystemDataIO::GetProjectDirectory()
{
	ProjectDirectory = FPaths::ProjectDir();
	
	return ProjectDirectory;
}

