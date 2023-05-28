// Fill out your copyright notice in the Description page of Project Settings.


#include "GetAssetsFromPath.h"
#include "FolderFileList.h"
#include <Kismet/GameplayStatics.h>

//Get all the files (Classified by folder) inside a folder
void UGetAssetsFromPath::GetAllAssetsOfClassFromPath(UClass* classType, FString path, TArray<AFolderFileList*> &foundObjects)
{
	//Get the absolute path
	path = FPaths::ProjectContentDir() + path;
	FPaths::NormalizeDirectoryName(path);
	IFileManager& fileManager = IFileManager::Get();
	FString finalPath = path / TEXT("*");

	//Array used to save all the folders inside the path
	TArray<FString> foundFolders;
	fileManager.FindFiles(foundFolders, *finalPath, false, true);

	//Iterate each found folder
	for (int i = 0; i < foundFolders.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Searching folder %s..."), *foundFolders[i]);

		//Folder path
		FString folderPath = path + "/" + foundFolders[i];
		FString finalFolderPath = folderPath / TEXT("*");
		UE_LOG(LogTemp, Warning, TEXT("Path %s..."), *finalFolderPath);

		//Array of the found objects inside
		TArray<FString> folderObjects;
		fileManager.FindFiles(folderObjects, *finalFolderPath, true, false);

		//Check the content of the folde
		for (int folderIndex = 0; folderIndex < folderObjects.Num(); folderIndex++)
		{
			UE_LOG(LogTemp, Warning, TEXT("    %s..."), *folderObjects[folderIndex]);
		}

		//Add array to the found objects (As a FFolferFile)
		AFolderFileList* folderListPtr = NewObject<AFolderFileList>(this);
		//AFolderFileList folderList = AFolderFileList(path, foundFolders[i], folderObjects);

		foundObjects.Add(folderListPtr);
	}
}