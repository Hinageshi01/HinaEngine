#pragma once

#ifdef HN_PLATFORM_WIN

extern Hina::Application *Hina::CreateApplication();

int main(int argc, char **argv) {
    Hina::Log::Init();
    HN_CORE_INFO("Initialized Log");

    HN_PROFILE_BEGIN_SESSION("Startup", "Log/HinaProfile_Startup.json");
    Hina::Application *app = Hina::CreateApplication();
    HN_PROFILE_END_SESSION();

    HN_PROFILE_BEGIN_SESSION("Running", "Log/HinaProfile_Running.json");
    app->Run();
    HN_PROFILE_END_SESSION();

    HN_PROFILE_BEGIN_SESSION("Shutdown", "Log/HinaProfile_Shutdown.json");
    delete app;
    HN_PROFILE_END_SESSION();

    return 0;
}

#else
    #error Hina only supports windows!
#endif
