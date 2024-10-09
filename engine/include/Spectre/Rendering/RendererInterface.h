#ifndef RENDERERINTERFACE_H
#define RENDERERINTERFACE_H

#include "sppch.h"

namespace Spectre {
class RendererInterface {
    public:
        virtual ~RendererInterface() = default;

        virtual bool initialise() = 0;
        virtual bool createWindow(const std::string& title, int width,
                                  int height) = 0;
        virtual void update() = 0;
        virtual void stop() = 0;
};
}  // namespace Spectre

#endif  // RENDERERINTERFACE_H