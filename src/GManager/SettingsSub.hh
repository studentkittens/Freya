#ifndef FREYA_SETTINGS_SUB_GUARD
#define FREYA_SETTINGS_SUB_GUARD

namespace GManager
{
    class SettingsSub
    {
        public:
            SettingsSub(){};
            ~SettingsSub(){};

            virtual void accept_new_settings(void) {};
            virtual void decline_new_settings(void) {};
    };

}

#endif
