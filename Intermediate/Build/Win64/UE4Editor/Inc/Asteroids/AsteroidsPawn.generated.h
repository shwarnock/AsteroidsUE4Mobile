// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ASTEROIDS_AsteroidsPawn_generated_h
#error "AsteroidsPawn.generated.h already included, missing '#pragma once' in AsteroidsPawn.h"
#endif
#define ASTEROIDS_AsteroidsPawn_generated_h

#define Asteroids_Source_Asteroids_AsteroidsPawn_h_13_RPC_WRAPPERS
#define Asteroids_Source_Asteroids_AsteroidsPawn_h_13_RPC_WRAPPERS_NO_PURE_DECLS
#define Asteroids_Source_Asteroids_AsteroidsPawn_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAsteroidsPawn(); \
	friend struct Z_Construct_UClass_AAsteroidsPawn_Statics; \
public: \
	DECLARE_CLASS(AAsteroidsPawn, APawn, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Asteroids"), NO_API) \
	DECLARE_SERIALIZER(AAsteroidsPawn)


#define Asteroids_Source_Asteroids_AsteroidsPawn_h_13_INCLASS \
private: \
	static void StaticRegisterNativesAAsteroidsPawn(); \
	friend struct Z_Construct_UClass_AAsteroidsPawn_Statics; \
public: \
	DECLARE_CLASS(AAsteroidsPawn, APawn, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Asteroids"), NO_API) \
	DECLARE_SERIALIZER(AAsteroidsPawn)


#define Asteroids_Source_Asteroids_AsteroidsPawn_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAsteroidsPawn(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAsteroidsPawn) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAsteroidsPawn); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAsteroidsPawn); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAsteroidsPawn(AAsteroidsPawn&&); \
	NO_API AAsteroidsPawn(const AAsteroidsPawn&); \
public:


#define Asteroids_Source_Asteroids_AsteroidsPawn_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAsteroidsPawn(AAsteroidsPawn&&); \
	NO_API AAsteroidsPawn(const AAsteroidsPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAsteroidsPawn); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAsteroidsPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAsteroidsPawn)


#define Asteroids_Source_Asteroids_AsteroidsPawn_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ShipMeshComponent() { return STRUCT_OFFSET(AAsteroidsPawn, ShipMeshComponent); } \
	FORCEINLINE static uint32 __PPO__CameraComponent() { return STRUCT_OFFSET(AAsteroidsPawn, CameraComponent); } \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(AAsteroidsPawn, CameraBoom); }


#define Asteroids_Source_Asteroids_AsteroidsPawn_h_10_PROLOG
#define Asteroids_Source_Asteroids_AsteroidsPawn_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Asteroids_Source_Asteroids_AsteroidsPawn_h_13_PRIVATE_PROPERTY_OFFSET \
	Asteroids_Source_Asteroids_AsteroidsPawn_h_13_RPC_WRAPPERS \
	Asteroids_Source_Asteroids_AsteroidsPawn_h_13_INCLASS \
	Asteroids_Source_Asteroids_AsteroidsPawn_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Asteroids_Source_Asteroids_AsteroidsPawn_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Asteroids_Source_Asteroids_AsteroidsPawn_h_13_PRIVATE_PROPERTY_OFFSET \
	Asteroids_Source_Asteroids_AsteroidsPawn_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	Asteroids_Source_Asteroids_AsteroidsPawn_h_13_INCLASS_NO_PURE_DECLS \
	Asteroids_Source_Asteroids_AsteroidsPawn_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ASTEROIDS_API UClass* StaticClass<class AAsteroidsPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Asteroids_Source_Asteroids_AsteroidsPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
