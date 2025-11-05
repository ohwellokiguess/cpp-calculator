#pragma once

#include "ui_mainwindow.h"
#include "enums.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();


    void SetInputText(const std::string& text);

    void SetErrorText(const std::string& text);

    void SetFormulaText(const std::string& text);

    void SetMemText(const std::string& text);

    void SetExtraKey(const std::optional<std::string> &key);


    void SetDigitKeyCallback(std::function<void(int key)> cb);

    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb);

    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb);

    void SetControllerCallback(std::function<void(ControllerType controller)> cb);


    void OnComboBoxChanged(int index);

    void OnDigitClicked();

    void OnOperationClicked();

    void OnControlClicked();

private:
    Ui::MainWindow* ui;
    std::function<void(int key)> cb_set_digit_;
    std::function<void(Operation key)> cb_set_operation_;
    std::function<void(ControlKey key)> cb_set_control_;
    std::function<void(ControllerType key)> cb_set_controller_;

};
