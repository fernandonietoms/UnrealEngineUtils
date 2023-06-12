// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GetAssetsFromPath.generated.h"

/**
 * 
 */
UCLASS()
class BUILDER_API UGetAssetsFromPath : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Utils")
	static void GetAllAssetClassesByFolderFromPath(FString path, AFolderFileList*& FoundObjects);
	
private:
	static AFolderFileList* GetFolderData(FString path, AFolderFileList* parentFolder, int recursiveLevel);
	static void PrintStringWithTab(FString text, int tabs);
};
