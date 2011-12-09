#ifndef FREYA_ABSTRACTCLIENTEXTENSION_HH
#define FREYA_ABSTRACTCLIENTEXTENSION_HH

namespace MPD
{
    class Client;

    class AbstractClientExtension
    {
        public:
            AbstractClientExtension(MPD::Client& client);

        private:
            MPD::Client * client;
    };

}

#endif /* end of include guard: FREYA_ABSTRACTCLIENTEXTENSION_HH */
