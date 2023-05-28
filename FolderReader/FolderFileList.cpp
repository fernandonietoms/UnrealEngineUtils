// Fill out your copyright notice in the Description page of Project Settings.


#include "FolderFileList.h"

// Sets default values
AFolderFileList::AFolderFileList()
{

}

AFolderFileList::AFolderFileList(FString path,FString folderName, TArray<FString> list)
{
	this->folderName = folderName;
	this->list = list;
}

