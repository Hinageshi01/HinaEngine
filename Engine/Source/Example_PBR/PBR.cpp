#include "hnpch.h"

#include "Hina.h"

class ExampleLayer : public Hina::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        HN_INFO("ExampleLayer::Update()");
    }

    void OnEvent(Hina::Event &event) override {
        HN_INFO("{}", event);
    }
};

class PBR : public Hina::Application
{
public:
    PBR() {
        PushLater(new ExampleLayer());
    }

    ~PBR() {

    }
};

Hina::Application *Hina::CreateApplication() {
    return new PBR;
}
