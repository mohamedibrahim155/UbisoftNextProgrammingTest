#pragma once
#include "../src/ECS/Components/Scripts/ScriptComponent.h"
#include "../src/ECS/Components/UI/TextRenderer.h"

enum class eUIType
{
    NONE,
    SCORE,
    STROKE
};
class UIDisplayer : public BaseScriptComponent
{
public:
    UIDisplayer(eUIType type);

    ~UIDisplayer() override = default;
	 void start() override;
     void updateComponent() override;
     void render(bool isDebugVisible) override {};
     void cleanUp() override {}

private:
    eUIType m_type;
    TextRenderer* m_displayText = nullptr;

    std::string prefixText;


    void updateUI();

    void setUIText(const std::string& value);
};

