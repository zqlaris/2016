#pragma once

namespace Arkiv
{
    private ref class NoInternetDialog sealed
    {
    public:
        static void Show();
    private:
        static void ShowCore();
        static bool _visible;
    };
}
