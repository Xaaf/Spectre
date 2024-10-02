#ifndef ENGINE_H
#define ENGINE_H

#include "sppch.h"

namespace Spectre {
class Engine {
    private:
        // Window* m_Window;    
        bool m_IsRunning;

        static Engine* instance;

    private:
        Engine();
        ~Engine();

    public:
        static Engine* getInstance();

        void initialise(const std::string& title, const std::string& renderer);
        void step();
        void stop();

        bool isRunning() const;
};
}  // namespace Spectre

#endif  // ENGINE_H