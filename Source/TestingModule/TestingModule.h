#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FTestingModule : public IModuleInterface
{
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};