// Fill out your copyright notice in the Description page of Project Settings.


#include "GetAssetsFromPath.h"
#include "FolderFileList.h"
#include <AssetRegistry/AssetRegistryModule.h>
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>

//Get all the classes of the files (Classified by folder) inside a folder
void UGetAssetsFromPath::GetAllAssetClassesByFolderFromPath(FString path, AFolderFileList*& foundObjects)
{
	UE_LOG(LogTemp, Warning, TEXT("Getting all assets on path: %s"), *path);
	
	AFolderFileList* folderListPtr = NewObject<AFolderFileList>();
	foundObjects = GetFolderData(path, folderListPtr, 0);
}

AFolderFileList* UGetAssetsFromPath::GetFolderData(FString relativePath, AFolderFileList* parentFolder, int recursiveLevel) {
	//Returned value
	AFolderFileList* folderListPtr = NewObject<AFolderFileList>();

	//Add the new folderFileList to the parent
	parentFolder->folderInsideFolderList.Add(folderListPtr);
	
	//Path usable by the finder
	FString folderPath = FPaths::ProjectContentDir() + relativePath;
	FPaths::NormalizeDirectoryName(folderPath);
	folderPath = folderPath / TEXT("*");

#pragma region Inside Folder List (Folders)
	//Get all the folders inside the folder
	IFileManager& fileManager = IFileManager::Get();
	TArray<FString> foldersInside;
	fileManager.FindFiles(foldersInside, *folderPath, false, true);

	//Iterate each folder
	for (int folderIndex = 0; folderIndex < foldersInside.Num(); folderIndex++)
	{
		PrintStringWithTab(*foldersInside[folderIndex], recursiveLevel);

		//Get folders inside the folder
		FString insideFolderPath = relativePath + "/" + *foldersInside[folderIndex];
		GetFolderData(insideFolderPath, folderListPtr, recursiveLevel + 1);
	}
#pragma endregion

#pragma region Inside Folder List (Files)
	/*
	//Get all the folders inside the folder
	TArray<FString> filesInside;
	fileManager.FindFiles(filesInside, *folderPath, true, false);

	//Iterate each folder
	for (int fileIndex = 0; fileIndex < filesInside.Num(); fileIndex++)
	{
		PrintStringWithTab(*filesInside[fileIndex], recursiveLevel);
	}
	*/
#pragma endregion

#pragma region Create FolderFileList
	//Asset Registry
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	//Get each asset data inside the folder
	FString gameRelativePath = "/Game/" + relativePath;
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssetsByPath(*gameRelativePath, AssetData, false, false);

	//Get all the classes of each asset data
	for (int assetDataIndex = 0; assetDataIndex < AssetData.Num(); assetDataIndex++)
	{
		FString assetDataClass = AssetData[assetDataIndex].ObjectPath.ToString() + "_C";
		FSoftClassPath assetClassPath = FSoftClassPath::FSoftClassPath(assetDataClass);
		UClass* assetClass = UKismetSystemLibrary::LoadClassAsset_Blocking(UKismetSystemLibrary::Conv_SoftClassPathToSoftClassRef(assetClassPath));
		if (assetClass != nullptr) {
			PrintStringWithTab(*assetDataClass, recursiveLevel);

			folderListPtr->folderList.Add(assetClass);
		}
	}

	return folderListPtr;
#pragma endregion
}

void UGetAssetsFromPath::PrintStringWithTab(FString text, int tabs) {
	//Final FString
	FString printedString = "";

	//Add the tabs
	while (tabs > 0)
	{
		printedString += "    ";
		tabs--;
	}

	//Add the printed text
	printedString += text;

	//Print the string
	UE_LOG(LogTemp, Warning, TEXT("%s"), *printedString);
}