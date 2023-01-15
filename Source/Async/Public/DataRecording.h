// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataRecording.generated.h"

/**
 * 
 */
UCLASS()
class ASYNC_API UDataRecording : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BLueprintCallable, Category = "File I/O")
		static FString LoadFileToString(FString FileDir, FString Filename);

		UFUNCTION(BLueprintCallable, Category = "File I/O")
		static TArray<FString> LoadFileToStringArray(FString FileDir, FString Filename);

		UFUNCTION(BlueprintPure, Category = "File I/O")
		static TArray<FVector> LoadFileToVector(FString FileDir, FString Filename);

		UFUNCTION(BlueprintCallable, Category = "File I/O")
		static bool SaveArrayText(FString SaveDirectory, FString Filename, TArray<FString> savetext, bool AllowOverwriting);


		UFUNCTION(BlueprintCallable, Category = "File I/O")
		static bool SaveVectorArrayText(FString SaveDirectory, FString Filename, TArray<FVector> vectors, bool AllowOverwriting);

		UFUNCTION(BlueprintPure, Category = "File I/O")
		static FString VectorToNiceString(FVector input);
};
