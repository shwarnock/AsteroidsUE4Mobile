// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FVector;
struct FHitResult;
#ifdef ASTEROIDS_AsteroidsProjectile_generated_h
#error "AsteroidsProjectile.generated.h already included, missing '#pragma once' in AsteroidsProjectile.h"
#endif
#define ASTEROIDS_AsteroidsProjectile_generated_h

#define Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_HitComp); \
		P_GET_OBJECT(AActor,Z_Param_OtherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp); \
		P_GET_STRUCT(FVector,Z_Param_NormalImpulse); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_Hit); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		P_THIS->OnHit(Z_Param_HitComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_NormalImpulse,Z_Param_Out_Hit); \
		P_NATIVE_END; \
	}


#define Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAsteroidsProjectile(); \
	friend struct Z_Construct_UClass_AAsteroidsProjectile_Statics; \
public: \
	DECLARE_CLASS(AAsteroidsProjectile, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Asteroids"), NO_API) \
	DECLARE_SERIALIZER(AAsteroidsProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAAsteroidsProjectile(); \
	friend struct Z_Construct_UClass_AAsteroidsProjectile_Statics; \
public: \
	DECLARE_CLASS(AAsteroidsProjectile, AActor, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Asteroids"), NO_API) \
	DECLARE_SERIALIZER(AAsteroidsProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAsteroidsProjectile(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAsteroidsProjectile) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAsteroidsProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAsteroidsProjectile); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAsteroidsProjectile(AAsteroidsProjectile&&); \
	NO_API AAsteroidsProjectile(const AAsteroidsProjectile&); \
public:


#define Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAsteroidsProjectile(AAsteroidsProjectile&&); \
	NO_API AAsteroidsProjectile(const AAsteroidsProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAsteroidsProjectile); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAsteroidsProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAsteroidsProjectile)


#define Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ProjectileMesh() { return STRUCT_OFFSET(AAsteroidsProjectile, ProjectileMesh); } \
	FORCEINLINE static uint32 __PPO__ProjectileMovement() { return STRUCT_OFFSET(AAsteroidsProjectile, ProjectileMovement); }


#define Asteroids_Source_Asteroids_AsteroidsProjectile_h_12_PROLOG
#define Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_PRIVATE_PROPERTY_OFFSET \
	Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_RPC_WRAPPERS \
	Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_INCLASS \
	Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_PRIVATE_PROPERTY_OFFSET \
	Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_INCLASS_NO_PURE_DECLS \
	Asteroids_Source_Asteroids_AsteroidsProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ASTEROIDS_API UClass* StaticClass<class AAsteroidsProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Asteroids_Source_Asteroids_AsteroidsProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
