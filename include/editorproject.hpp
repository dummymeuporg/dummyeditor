#pragma once

#include <memory>

#include <QDomDocument>
#include <QMap>
#include <QString>

#include "core/project.hpp"

#include "misc/mapdocument.hpp"
#include "misc/maptreemodel.hpp"

class EditorStartingPoint;


class EditorProject
{
public:
    EditorProject(const std::string& projectFolder);
    virtual ~EditorProject();
    static void create(const QString&);
    Misc::MapTreeModel* mapsModel();

    static void cleanMapName(QString& mapName);

    /*
    inline const std::string& fullpath() const {
        return m_coreProject.projectPath().string();
    }
    */

    const Dummy::Core::Project& coreProject() const {
        return m_coreProject;
    }

    inline bool isModified() const {
        return m_isModified;
    }

    EditorProject& setModified(bool isModified) {
        m_isModified = isModified;
        return *this;
    }

    void saveProjectFile();

    std::shared_ptr<Misc::MapDocument>& document(const QString& mapName);

    inline QMap<QString, std::shared_ptr<Misc::MapDocument>>
    openedMaps() const
    {
        return m_openedMaps;
    }

    const EditorStartingPoint& startingPoint() const {
        return *m_startingPoint;
    }

    void setStartingPoint(const EditorStartingPoint&);

private:
    Dummy::Core::Project m_coreProject;
    QDomDocument m_domDocument;
    Misc::MapTreeModel* m_mapsModel;
    bool m_isModified;
    std::unique_ptr<EditorStartingPoint> m_startingPoint;

    QMap<QString, std::shared_ptr<Misc::MapDocument>> m_openedMaps;

    static QDomDocument _createXmlProjectTree();
    static void _createXmlProjectFile(const QString&);
    static void _createFolders(const QString&);
    void _dumpToXmlNode(QDomDocument& document,
                        QDomElement& xmlNode,
                        QStandardItem* modelItem);


};
