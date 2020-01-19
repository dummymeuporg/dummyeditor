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

//////////////////////////////////////////////////////////////////////////////
//  GeneralWindow class
//////////////////////////////////////////////////////////////////////////////

class GeneralWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GeneralWindow(QWidget* parent = nullptr);
    ~GeneralWindow();

private slots:
    void on_actionOpen_triggered();

private:
    bool loadProject(const QString& path);
    bool closeProject();
    void updateProjectView();

    Ui::GeneralWindow* m_ui;
    std::unique_ptr<Editor::Project> m_loadedProject;
};

#endif // GENERALWINDOW_H
