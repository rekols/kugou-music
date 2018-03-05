#include "titlebar.h"
#include <QHBoxLayout>
#include <QSvgWidget>

Titlebar::Titlebar(QWidget *parent)
    : QWidget(parent),
      m_searchEdit(new DSearchEdit)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    QSvgWidget *iconWidget = new QSvgWidget(":/images/kugou-music.svg");
    iconWidget->setFixedSize(22, 22);

    m_searchEdit->setFixedWidth(350);
    m_searchEdit->setPlaceHolder(tr("Search"));

    mainLayout->addWidget(iconWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(m_searchEdit);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(5, 0, 0, 0);

    setFocusPolicy(Qt::ClickFocus);

    connect(m_searchEdit, &DSearchEdit::returnPressed, this, 
            [=] {
                emit editReturnPressed(m_searchEdit->text());
            });
}
