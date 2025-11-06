#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):

    QMainWindow(parent),
    ui(new Ui::MainWindow) {
        ui->setupUi(this);

        connect(ui->cmb_controller, &QComboBox::currentIndexChanged, this, &MainWindow::OnComboBoxChanged);

        //set Digit
        connect(ui->pb_zero, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
        connect(ui->pb_one, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
        connect(ui->pb_two, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
        connect(ui->pb_three, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
        connect(ui->pb_four, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
        connect(ui->pb_five, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
        connect(ui->pb_six, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
        connect(ui->pb_seven, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
        connect(ui->pb_eight, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);
        connect(ui->pb_nine, &QPushButton::clicked, this, &MainWindow::OnDigitClicked);

        //set Operation
        connect(ui->pb_addition, &QPushButton::clicked, this, &MainWindow::OnOperationClicked);
        connect(ui->pb_substraction, &QPushButton::clicked, this, &MainWindow::OnOperationClicked);
        connect(ui->pb_multiplication, &QPushButton::clicked, this, &MainWindow::OnOperationClicked);
        connect(ui->pb_division, &QPushButton::clicked, this, &MainWindow::OnOperationClicked);
        connect(ui->pb_power, &QPushButton::clicked, this, &MainWindow::OnOperationClicked);

        //set Control
        connect(ui->pb_equal, &QPushButton::clicked, this, &MainWindow::OnControlClicked);
        connect(ui->pb_reset, &QPushButton::clicked, this, &MainWindow::OnControlClicked);
        connect(ui->pb_ms, &QPushButton::clicked, this, &MainWindow::OnControlClicked);
        connect(ui->pb_mr, &QPushButton::clicked, this, &MainWindow::OnControlClicked);
        connect(ui->pb_mc, &QPushButton::clicked, this, &MainWindow::OnControlClicked);
        connect(ui->pb_negative, &QPushButton::clicked, this, &MainWindow::OnControlClicked);
        connect(ui->pb_backspace, &QPushButton::clicked, this, &MainWindow::OnControlClicked);
        connect(ui->tb_extra, &QPushButton::clicked, this, &MainWindow::OnControlClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key.has_value()) {
        ui->tb_extra->show();
        ui->tb_extra->setText(QString::fromStdString(key.value()));
    } else {
        ui->tb_extra->hide();
    }
}

//set Callbacks
void MainWindow::SetDigitKeyCallback(std::function<void (int)> cb) {
    cb_set_digit_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void (Operation)> cb) {
    cb_set_operation_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void (ControlKey)> cb) {
    cb_set_control_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void (ControllerType)> cb) {
    cb_set_controller_ = cb;
}


//Buttons processing
void MainWindow::OnComboBoxChanged(int index) {

    if (cb_set_controller_) {
        ControllerType controller_type = static_cast<ControllerType>(index);

        cb_set_controller_(controller_type);
    }
}

void MainWindow::OnDigitClicked() {

    if (cb_set_digit_) {
        QPushButton* sender_button = qobject_cast<QPushButton*>(sender());
        int digit = sender_button->text().toInt();

        cb_set_digit_(digit);
    }
}

void MainWindow::OnOperationClicked() {

    if (cb_set_operation_) {

        QPushButton* sender_button = qobject_cast<QPushButton*>(sender());
        QString operation = sender_button->text();

        if (operation  == "+") {
            cb_set_operation_(Operation::ADDITION);

        } else if (operation == "−") {
            cb_set_operation_(Operation::SUBTRACTION);

        } else if (operation == "×") {
            cb_set_operation_(Operation::MULTIPLICATION);

        } else if (operation == "÷") {
            cb_set_operation_(Operation::DIVISION);

        } else {
            cb_set_operation_(Operation::POWER);
        }
    }
}

void MainWindow::OnControlClicked() {

    if (cb_set_control_) {

        QPushButton* sender_button = qobject_cast<QPushButton*>(sender());
        QString control = sender_button->text();

        if (control  == "=") {
            cb_set_control_(ControlKey::EQUALS);

        } else if (control == "C") {
            cb_set_control_(ControlKey::CLEAR);

        } else if (control == "MS") {
            cb_set_control_(ControlKey::MEM_SAVE);

        } else if (control == "MR") {
            cb_set_control_(ControlKey::MEM_LOAD);

        } else if (control == "MC"){
            cb_set_control_(ControlKey::MEM_CLEAR);

        } else if (control == "±"){
            cb_set_control_(ControlKey::PLUS_MINUS);

        } else if (control == "⌫"){
            cb_set_control_(ControlKey::BACKSPACE);

        } else {
            cb_set_control_(ControlKey::EXTRA_KEY);
        }
    }
}

