// Fill out your copyright notice in the Description page of Project Settings.


#include "DataRecording.h"
#include "Misc\Filehelper.h"
#include "HAL\PlatformFilemanager.h"
#include "Containers/UnrealString.h"
#include <Runtime\Core\Public\Misc\Paths.h>

bool UDataRecording::SaveArrayText(FString SaveDirectory, FString Filename, TArray<FString> savetext, bool AllowOverwriting = true)
{
	//complete file check
	SaveDirectory += "\\";
	SaveDirectory += Filename;
	//check if allowing overwrite
	if (!AllowOverwriting)
	{
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			return false;
		}
	}
	//saving this to file
	FString FinalString = "";
	for (FString& Each : savetext) {
		FinalString += Each;
		FinalString += LINE_TERMINATOR;
	}
	return FFileHelper::SaveStringToFile(FinalString, *SaveDirectory);
}

FString UDataRecording::VectorToNiceString(FVector input)
{
	FString comma = FString(TEXT(","));
	return FString::SanitizeFloat(input.X, 2) + comma + FString::SanitizeFloat(input.Y, 2) + comma + FString::SanitizeFloat(input.Z, 2);
}

bool UDataRecording::SaveVectorArrayText(FString SaveDirectory, FString Filename, TArray<FVector> vectors, bool AllowOverwriting)
{
	//complete file check
	SaveDirectory += "\\";
	SaveDirectory += Filename;
	//check if allowing overwrite
	if (!AllowOverwriting)
	{
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			return false;
		}
	}
	FString FinalString = "";
	for (FVector& Each : vectors)
	{
		FinalString += VectorToNiceString(Each);
		FinalString += LINE_TERMINATOR;
	}
	return FFileHelper::SaveStringToFile(FinalString, *SaveDirectory);
}


FString UDataRecording::LoadFileToString(FString FileDir, FString Filename)
{
	FString result;
	FString myFile = FileDir + Filename;
	UE_LOG(LogTemp, Warning, TEXT("FileDirectory is %s"), *myFile);
	bool success = FFileHelper::LoadFileToString(result, *myFile);
	FString worked = success ? TEXT("true") : TEXT("false");
	UE_LOG(LogTemp, Warning, TEXT("loaded correctly? %s	"), *worked);
	return result;
}

TArray<FString> UDataRecording::LoadFileToStringArray(FString FileDir, FString Filename)
{
	TArray<FString> result;
	FString myFile = FileDir + Filename;
	UE_LOG(LogTemp, Warning, TEXT("FileDirectory is %s"), *myFile);
	bool success = FFileHelper::LoadFileToStringArray(result, *myFile);
	FString worked = success ? TEXT("true") : TEXT("false");
	UE_LOG(LogTemp, Warning, TEXT("loaded correctly? %s	"), *worked);
	return result;
}


TArray<FVector> UDataRecording::LoadFileToVector(FString FileDir, FString Filename)
{
	TArray<FVector> result;
	TArray<FString> STRArr = UDataRecording::LoadFileToStringArray(FileDir, Filename);
	TArray<FString> temp;
	for (FString& Each : STRArr) {
		FString num1;
		FString num2;
		FString num3;
		Each.Split(FString(TEXT(",")), &num1, &num2);
		 num2 = num2.LeftChop(1);
		num2.Split(FString(TEXT(",")), &num2, &num3);
		 num3 = num3.LeftChop(1);
		//sounds good
		FVector data = FVector(FCString::Atof(*num1), FCString::Atof(*num2), FCString::Atof(*num3));
		result.Add(data);
	}

		//string back into float
	return result;
}