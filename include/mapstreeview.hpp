#pragma once

#include <QMenu>
#include <QObject>
#include <QTreeView>

#include <exception>
#include <memory>

#include "editor/project.hpp"

namespace Dummy {
    class Project;
}

class QAction;


class MapsTreeViewError : public std::exception {
};

class ProjectNotSet : public MapsTreeViewError {
public:
    const char* what() const noexcept override {
        return "the project is not set";
    }
};


class MapsTreeView : public QTreeView
{
    Q_OBJECT

public:
    MapsTreeView(QWidget* parent=nullptr);

    void setProject(std::shared_ptr<Editor::Project> project) {
        m_project = project;

        if (nullptr != project) {
            _enableActions();
        } else {
            _disableActions();
        }
    }

    const Editor::Project& project() const {
        return *m_project;
    }

signals:
    void chipsetMapChanged(QString);

private:

    void _enableActions();
    void _disableActions();


    std::shared_ptr<Editor::Project> m_project;
    QMenu* m_mapMenu;
    QAction* m_newMapAction, *m_propertiesAction;
    QModelIndex m_selectedModelIndex;

private slots:
    void _onNewMapAction();
    void _onPropertiesAction();
    void _showContextMenu(const QPoint&);
};
