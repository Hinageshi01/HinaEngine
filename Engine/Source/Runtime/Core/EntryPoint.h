#pragma once

#ifdef HN_PLATFORM_WIN

extern Hina::Application *Hina::CreateApplication();

int main(int argc, char **argv) {
    Hina::Application *app = Hina::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#else
    #error Hina only supports windows!
#endif
