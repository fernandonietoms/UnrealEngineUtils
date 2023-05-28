// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FolderFileList.generated.h"

UCLASS()
class BUILDER_API AFolderFileList : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString path;

	UPROPERTY()
	FString folderName;

	UPROPERTY()
	TArray<FString> list;
	
	// Sets default values for this actor's properties
	AFolderFileList();
	AFolderFileList(FString path,FString folderName, TArray<FString> list);
};
