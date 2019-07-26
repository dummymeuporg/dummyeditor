#pragma once

#include <memory>

#include <QDomDocument>
#include <QMap>
#include <QString>

#include <dummy/local/project.hpp>

#include "misc/mapdocument.hpp"
#include "misc/map_tree_model.hpp"

namespace Editor {


class StartingPoint;


class ProjectError : public std::exception {

};

class NoStartingPoint : public ProjectError {
public:
    const char* what() const noexcept override {
        return "the project has no starting point";
    }
};

class Project
{
public:
    Project(const std::string&);
    virtual ~Project();
    static void create(const QString&);
    Misc::MapTreeModel* mapsModel();

    static void cleanMapName(QString& mapName);

    /*
    inline const std::string& fullpath() const {
        return m_coreProject.projectPath().string();
    }
    */

    const Dummy::Local::Project& coreProject() const {
        return m_coreProject;
    }

    inline bool isModified() const {
        return m_isModified;
    }

    Project& setModified(bool isModified) {
        m_isModified = isModified;
        return *this;
    }

    void saveProjectFile();

    std::shared_ptr<Misc::MapDocument> document(const QString& mapName);

    inline QMap<QString, std::shared_ptr<Misc::MapDocument>>
    openedMaps() const
    {
        return m_openedMaps;
    }

    const StartingPoint& startingPoint() const {
        if (m_startingPoint == nullptr) {
            throw NoStartingPoint();
        }
        return *m_startingPoint;
    }

    void setStartingPoint(const StartingPoint&);

private:
    Dummy::Local::Project m_coreProject;
    QDomDocument m_domDocument;
    Misc::MapTreeModel* m_mapsModel;
    bool m_isModified;
    std::unique_ptr<StartingPoint> m_startingPoint;

    QMap<QString, std::shared_ptr<Misc::MapDocument>> m_openedMaps;

    static QDomDocument _createXmlProjectTree();
    static void _createXmlProjectFile(const QString&);
    static void _createFolders(const QString&);
    void _dumpToXmlNode(QDomDocument& document,
                        QDomElement& xmlNode,
                        QStandardItem* modelItem);
};

} // namespace Editor
