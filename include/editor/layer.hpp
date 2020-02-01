#ifndef EDITORLAYER_H
#define EDITORLAYER_H

#include <QObject>

namespace Editor {

//////////////////////////////////////////////////////////////////////////////
//  Layer class
//////////////////////////////////////////////////////////////////////////////

class Layer : public QObject
{
    Q_OBJECT
public:
    explicit Layer();
    bool visible() const { return m_visible; }
    void setVisible(bool visible);

signals:
    void visibilityChanged(bool);
    void setSelected();

private:
    bool m_visible = true;
};
} // namespace Editor

#endif // EDITORLAYER_H
