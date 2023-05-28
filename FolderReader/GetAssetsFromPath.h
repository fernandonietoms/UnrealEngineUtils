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

	UFUNCTION(BlueprintCallable, Category ="Utils")
	void GetAllAssetsOfClassFromPath(UClass* classType, FString path, TArray<AFolderFileList*> &FoundObjects);
};
