#include "ui_slider.h"
#include "ui_layout.h"
#include <SDL3/SDL.h>

template<typename T>
UISlider<T>::UISlider(UILayout* layout)
    :UIWidget(layout)
{
    
}

template<typename T>
void UISlider<T>::Draw(){

}

template<typename T>
void UISlider<T>::Update(float deltatime){

}

template<typename T>
void UISlider<T>::HandleEvent(const SDL_Event& event){

}

template<typename T>
void UISlider<T>::SetFloatRange(float start, float stop, float step){
    for(auto i = start; i <= stop; i += step){
        m_range.push_back(i);
    }
}

