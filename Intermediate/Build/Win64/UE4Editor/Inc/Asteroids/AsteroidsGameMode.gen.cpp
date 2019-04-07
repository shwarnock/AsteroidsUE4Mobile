// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Asteroids/AsteroidsGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAsteroidsGameMode() {}
// Cross Module References
	ASTEROIDS_API UClass* Z_Construct_UClass_AAsteroidsGameMode_NoRegister();
	ASTEROIDS_API UClass* Z_Construct_UClass_AAsteroidsGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Asteroids();
// End Cross Module References
	void AAsteroidsGameMode::StaticRegisterNativesAAsteroidsGameMode()
	{
	}
	UClass* Z_Construct_UClass_AAsteroidsGameMode_NoRegister()
	{
		return AAsteroidsGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AAsteroidsGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAsteroidsGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Asteroids,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAsteroidsGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "AsteroidsGameMode.h" },
		{ "ModuleRelativePath", "AsteroidsGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAsteroidsGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAsteroidsGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AAsteroidsGameMode_Statics::ClassParams = {
		&AAsteroidsGameMode::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802A8u,
		METADATA_PARAMS(Z_Construct_UClass_AAsteroidsGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AAsteroidsGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AAsteroidsGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AAsteroidsGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AAsteroidsGameMode, 1653885411);
	template<> ASTEROIDS_API UClass* StaticClass<AAsteroidsGameMode>()
	{
		return AAsteroidsGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AAsteroidsGameMode(Z_Construct_UClass_AAsteroidsGameMode, &AAsteroidsGameMode::StaticClass, TEXT("/Script/Asteroids"), TEXT("AAsteroidsGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAsteroidsGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
