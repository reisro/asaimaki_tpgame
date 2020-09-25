// Fill out your copyright notice in the Description page of Project Settings.


#include "AsaiMakiGameDebugger.h"

// Sets default values
AAsaiMakiGameDebugger::AAsaiMakiGameDebugger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAsaiMakiGameDebugger::BeginPlay()
{
	Super::BeginPlay();

	FImGuiDelegates::OnMultiContextDebug().AddUFunction(this, TEXT("ActivateMainMenubar"));	
}

// Called every frame
void AAsaiMakiGameDebugger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAsaiMakiGameDebugger::ActivateMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Game"))
		{
			if (ImGui::MenuItem("Show Menu Title")) {}
			if (ImGui::MenuItem("Go to Fight Combat at Small Temple")) {}
			if (ImGui::MenuItem("Go to Fight Combat at Shrine")) {}
			if (ImGui::MenuItem("Go to Final Combat at Great Shrine")) {}
			if (ImGui::MenuItem("Game Over")) {}
			if (ImGui::MenuItem("Credits")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Character"))
		{
			if (ImGui::MenuItem("Core")) {}
			if (ImGui::MenuItem("Animation")) {}
			if (ImGui::MenuItem("Abilities")) {}
			if (ImGui::MenuItem("Items")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("NPC"))
		{
			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();
}