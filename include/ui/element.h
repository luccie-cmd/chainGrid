#if !defined(_CHAINGRID_UI_ELEMENT_H_)
#define _CHAINGRID_UI_ELEMENT_H_
#include <rendering/renderer.h>

namespace chainGrid::ui{
    enum struct ElementType{
        Text,
        Button,
        None,
    };
    class Element{
        public:
            Element(ElementType type, rendering::Renderer* renderer);
            virtual ~Element() = default;
            virtual void render() = 0;
            virtual void update(GLFWwindow* window){
                (void)window;
            }
        protected:
            ElementType __type;
            rendering::Renderer* __renderer;
    };
};

#endif // _CHAINGRID_UI_ELEMENT_H_
