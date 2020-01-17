#ifndef MAPSTREEVIEW_H
#define MAPSTREEVIEW_H

#include <exception>
#include <memory>

#include <QMenu>
#include <QTreeView>

#include "editor/project.hpp"

//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Dummy {
class Project;
}

//////////////////////////////////////////////////////////////////////////////
//  Error classes
//////////////////////////////////////////////////////////////////////////////

class MapsTreeViewError : public std::exception
{};

class ProjectNotSet : public MapsTreeViewError
{
public:
    const char* what() const noexcept override
    {
        return "the project is not set";
    }
};

//////////////////////////////////////////////////////////////////////////////
//  MapsTreeView class
// a MapsTreeView represents a visual list of maps.
// It contains only the graphical representation and interactions. Data are
// kept in MapsTreeModel.
//////////////////////////////////////////////////////////////////////////////

class MapsTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit MapsTreeView(QWidget* parent = nullptr);

    void setProject(std::shared_ptr<Editor::Project> project);

public slots:
    void onNewMapAction();
    void onPropertiesAction();
    void showContextMenu(const QPoint&);

signals:
    void chipsetMapChanged(QString);

private:
    std::shared_ptr<Editor::Project> m_project;
    QMenu* m_mapMenu            = nullptr;
    QAction* m_newMapAction     = nullptr;
    QAction* m_propertiesAction = nullptr;
    QModelIndex m_selectedModelIndex;
};

#endif // MAPSTREEVIEW_H
