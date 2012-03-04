#ifndef FREYA_IMAGEWALL_HH
#define FREYA_IMAGEWALL_HH

#include <gtkmm.h>

namespace Browser 
{
    class ImageWall : public Gtk::Grid 
    {
        public:
            ImageWall(int xmax, int ymax);

            void add(Widget& w);
            void add(std::string& path);
            void clear();

        private:

            int col,row;
            int xmax, ymax;
    };
}

#endif /* end of include guard: FREYA_IMAGEWALL_HH */
