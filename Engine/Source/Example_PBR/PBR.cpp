#include "hnpch.h"

#include "Hina.h"

class ExampleLayer : public Hina::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        // HN_APP_TRACE("ExampleLayer::Update()");
    }

    void OnEvent(Hina::Event &event) override {
        // HN_APP_TRACE("{}", event);
    }
};

class PBR : public Hina::Application
{
public:
    PBR() {
        PushLater(new ExampleLayer());
        PushOverlay(new Hina::ImGuiLayer());
    }

    ~PBR() {

    }
};

Hina::Application *Hina::CreateApplication() {
    return new PBR;
}
