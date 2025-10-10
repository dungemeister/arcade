#include "ui_widget.h"
#include "ui_layout.h"

UIWidget::UIWidget(class UILayout* layout)
    :m_layout(layout)
    ,m_size()
    ,m_size_padding()
{
    m_layout->AddWidget(this);
}

UIWidget::UIWidget()
    :UIWidget(nullptr)
{
    m_layout->RemoveWidget(this);
}
