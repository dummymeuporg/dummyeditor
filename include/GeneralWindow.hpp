#ifndef GENERALWINDOW_H
#define GENERALWINDOW_H

#include <QMainWindow>
#include <memory>

#include "utils/Logger.hpp"

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
class VisibleGraphicLayer;
class BlockingGraphicLayer;
} // namespace GraphicMap

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
    void on_mapsList_doubleClicked(const QModelIndex& selectedIndex);
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();

    void graphicLayerSelected(GraphicMap::VisibleGraphicLayer* layer);
    void blockingLayerSelected(GraphicMap::BlockingGraphicLayer* layer);

private:
    void closeEvent(QCloseEvent* event) override;
    void updateProjectView();
    void updateMapsAndFloorsList();

    void setupLoggers();
    void cleanLoggers();

    std::unique_ptr<Ui::GeneralWindow> m_ui;
    std::unique_ptr<ChipsetGraphicsScene> m_chipsetScene;
    std::unique_ptr<GraphicMap::MapGraphicsScene> m_mapScene;

    std::shared_ptr<Editor::Project> m_loadedProject;
    std::vector<std::shared_ptr<Log::Logger>> m_loggers;
};

// This is a wrapper around status bar to use log system
class LoggerStatusBar : public Log::Logger
{
public:
    LoggerStatusBar(QStatusBar* stsBar);
    void print(const std::string& message, Log::eLogType type) override;

private:
    QStatusBar* m_statusBar = nullptr;
};

#endif // GENERALWINDOW_H
