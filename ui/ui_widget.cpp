#include "ui_widget.h"
#include "ui_layout.h"

UIWidget::UIWidget(class UILayout* layout)
    :m_layout(layout)
    ,m_rect()
    ,m_rect_padding()
    ,m_hovered(false)
{
    if(m_layout)
        m_layout->AddWidget(this);
}

UIWidget::UIWidget():
    UIWidget(nullptr)
{

}

UIWidget::~UIWidget()
{
    if(m_layout)
        m_layout->RemoveWidget(this);
}
