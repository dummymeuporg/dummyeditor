#ifndef MAPSTREEVIEW_H
#define MAPSTREEVIEW_H

#include <QMenu>
#include <QObject>
#include <QTreeView>

#include <memory>

namespace Dummy {
    class Project;
}

class QAction;

class MapsTreeView : public QTreeView
{
    Q_OBJECT

public:
    MapsTreeView(QWidget* parent=nullptr);

    void setProject(std::shared_ptr<Dummy::Project> project) {
        m_project = project;

        if (nullptr != project) {
            _enableActions();
        } else {
            _disableActions();
        }
    }

    inline std::shared_ptr<Dummy::Project> project() const {
        return m_project;
    }

signals:
    void chipsetMapChanged(QString);

private:

    void _enableActions();
    void _disableActions();


    std::shared_ptr<Dummy::Project> m_project;
    QMenu* m_mapMenu;
    QAction* m_newMapAction, *m_propertiesAction;
    QModelIndex m_selectedModelIndex;

private slots:
    void _onNewMapAction();
    void _onPropertiesAction();
    void _showContextMenu(const QPoint&);
};

#endif // MAPSTREEVIEW_H
