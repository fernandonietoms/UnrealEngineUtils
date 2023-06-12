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
	UPROPERTY(BlueprintReadWrite)
	FString folderGamePath;

	UPROPERTY(BlueprintReadWrite)
	FString folderName;

	UPROPERTY(BlueprintReadWrite)
	TArray<UClass*> folderList;

	UPROPERTY(BlueprintReadOnly)
	TArray<AFolderFileList*> folderInsideFolderList;

};
