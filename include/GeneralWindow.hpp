#ifndef GENERALWINDOW_H
#define GENERALWINDOW_H

#include <QMainWindow>
#include <memory>


//////////////////////////////////////////////////////////////////////////////
//  forward declaration
//////////////////////////////////////////////////////////////////////////////

namespace Editor {
class Project;
} // namespace Editor

namespace Ui {
class GeneralWindow;
}

namespace GraphicMap {
class MapGraphicsScene;
}

class ChipsetGraphicsScene;

//////////////////////////////////////////////////////////////////////////////
//  GeneralWindow class
//////////////////////////////////////////////////////////////////////////////

class GeneralWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GeneralWindow(QWidget* parent = nullptr);
    virtual ~GeneralWindow() override;

public:
    bool loadProject(const QString& path);
    bool closeProject();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionClose_triggered();

private:
    void closeEvent(QCloseEvent* event) override;
    void updateProjectView();
    void updateMapsList();

    std::unique_ptr<Ui::GeneralWindow> m_ui;
    std::unique_ptr<ChipsetGraphicsScene> m_chipsetScene;
    std::unique_ptr<GraphicMap::MapGraphicsScene> m_mapScene;

    std::shared_ptr<Editor::Project> m_loadedProject;
};

#endif // GENERALWINDOW_H
