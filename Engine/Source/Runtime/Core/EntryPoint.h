#pragma once

#ifdef HN_PLATFORM_WIN

extern Hina::Application *Hina::CreateApplication();

int main(int argc, char **argv) {
    // Just some test code here.
    Hina::Log::Init();
    HN_CORE_WARN("Initialized Log!");
    int tmp = 42;
    HN_INFO("The truth is {}.", tmp);

    Hina::WindowResizeEvent wre(123, 456);
    HN_INFO(wre);

    Hina::Application *app = Hina::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#else
    #error Hina only supports windows!
#endif
