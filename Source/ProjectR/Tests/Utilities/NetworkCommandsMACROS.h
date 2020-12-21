// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

/**
 * Macro to be able to create network automation tests with a test as parameter.
 */
 //declare the class
#define START_NETWORK_AUTOMATION_COMMAND_WITH_TEST_ASSOCIATED(ClassDeclaration)	\
class F##ClassDeclaration : public IAutomationNetworkCommand \
{ \
private:\
	int32 RoleIndex; \
        FAutomationTestBase* test; \
public: \
	F##ClassDeclaration(int32 InRoleIndex, FAutomationTestBase* aTest) : RoleIndex(InRoleIndex), test(aTest) {} \
	virtual ~F##ClassDeclaration() {} \
	virtual uint32 GetRoleIndex() const override { return RoleIndex; } \
        FAutomationTestBase* associatedtest() { return test; } \
        virtual void Run() override 
        

//close the class and add to the framework
#define END_NETWORK_AUTOMATION_COMMAND_WITH_TEST_ASSOCIATED(ClassDeclaration,InRoleIndex, aTest) }; \
	FAutomationTestFramework::Get().EnqueueNetworkCommand(MakeShareable(new F##ClassDeclaration(InRoleIndex, aTest))); \
