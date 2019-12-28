#ifndef MAPSTREEVIEW_H
#define MAPSTREEVIEW_H

#include <exception>
#include <memory>

#include <QMenu>
#include <QTreeView>

#include "editor/project.hpp"

//////////////////////////////////////////////////////////////////////////////
//  pre-declaration
//////////////////////////////////////////////////////////////////////////////

namespace Dummy {
    class Project;
}

//////////////////////////////////////////////////////////////////////////////
//  Error classes
//////////////////////////////////////////////////////////////////////////////

class MapsTreeViewError : public std::exception {
};

class ProjectNotSet : public MapsTreeViewError {
public:
    const char* what() const noexcept override {
        return "the project is not set";
    }
};

//////////////////////////////////////////////////////////////////////////////
//  MapsTreeView class
//////////////////////////////////////////////////////////////////////////////

class MapsTreeView : public QTreeView
{
    Q_OBJECT

public:
    MapsTreeView(QWidget* parent=nullptr);

    const Editor::Project& project() const { return *m_project; }

    void setProject(std::shared_ptr<Editor::Project> project);

private:
    void enableActions();
    void disableActions();

signals:
    void chipsetMapChanged(QString);

private slots:
    void onNewMapAction();
    void onPropertiesAction();
    void showContextMenu(const QPoint&);

private:
    std::shared_ptr<Editor::Project> m_project;
    QMenu* m_mapMenu;
    QAction* m_newMapAction;
    QAction* m_propertiesAction;
    QModelIndex m_selectedModelIndex;
};

#endif // MAPSTREEVIEW_H
