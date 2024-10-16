#include "colorGame.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QApplication>
#include <random>
#include <QColor>
#include <algorithm>
#include <QTimer>


ColorGame::ColorGame(QWidget * parent): QDialog(parent)
{

    createWidgets();
    setupLayout();
    makeConnetions();

    setFixedSize(600, 500);
    setWindowTitle("Color Game");

    nextLevel();
}

void ColorGame::createWidgets()
{
    for(int i=0;i<6;++i){
        m_colorButtons[i] = new QPushButton();
        m_colorButtons[i]->setFixedSize(100,100);
        m_colorButtons[i]->setStyleSheet(
                        "border-radius: 10px;"
                        "background-color: #D3D3D3;"
                        "border: 2px solid #8f8f91;"
                        );
        m_colorButtons[i]->setFocusPolicy(Qt::NoFocus);//skzbic vor chntrvi
    }
    m_titleLabel = new QLabel("Color Game");
    m_describeLabel = new QLabel("Find the block with a different shade or brightness.");
    m_scoreLabel = new QLabel("Pick a block to play.");
    m_score = 0;

    m_titleLabel->setStyleSheet("font-size: 50px; font-weight: bold;");
    m_describeLabel->setStyleSheet("font-size: 20px;");
    m_scoreLabel->setStyleSheet("font-size: 20px;");

    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_scoreLabel->setAlignment(Qt::AlignCenter);
    m_describeLabel->setAlignment(Qt::AlignCenter);

    m_timer = new QTimer(this);
    m_timeValue = 10000; //ms
}

void ColorGame::setupLayout()
{
    QGridLayout *colorButtonsLayout = new QGridLayout;

    for (int i = 0; i < 6; ++i) {
        int row = i / 3;
        int col = i % 3;
        colorButtonsLayout->addWidget(m_colorButtons[i], row, col);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_titleLabel);
    mainLayout->addWidget(m_describeLabel);
    mainLayout->addLayout(colorButtonsLayout);
    mainLayout->addWidget(m_scoreLabel);


    setLayout(mainLayout);
}

void ColorGame::makeConnetions()
{
    for (int i = 0; i < 6; ++i) {
        connect(m_colorButtons[i], &QPushButton::clicked, this, [this, i]() {
            colorButtonClicked(i); // Call the slot with the button index
        });
    }
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeFinished()));
}


void ColorGame::nextLevel()
{
    m_correctAnswer = rand() % 6; //other button

    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;

    int shift = 50 ;

    QColor color(r, g, b);

    QColor shiftColor(std::min(r+shift, 255), std::min(g+shift, 255), std::min(b+shift, 255));

    QString style =  QString(
                        "border-radius: 10px;"
                        "border: 2px solid #8f8f91;"
                        "background-color: %1;"
                        ).arg(color.name());


    for(int i=0; i<6; ++i){
        if(i==m_correctAnswer)
            continue;

        m_colorButtons[i]->setStyleSheet(style);
    }

    QString shiftStyle =  QString(
                        "border-radius: 10px;"
                        "border: 2px solid #8f8f91;"
                        "background-color: %1;"
                        ).arg(shiftColor.name());
    m_colorButtons[m_correctAnswer]->setStyleSheet(shiftStyle);
}

void ColorGame::newGame()
{
    int r = QMessageBox::question(
                                this,
                                "Color Game",
                                "Do you want to start a new game?",
                                QMessageBox::Yes |
                                QMessageBox::No,
                                QMessageBox::No);

    if(r == QMessageBox::Yes){
        m_scoreLabel->setText("Pick a block to play.");
        m_score = 0;
        nextLevel();
    }
    else{
        QApplication::quit();
    }
}

void ColorGame::colorButtonClicked(int k)
{
    m_timer->stop();
    if(k == m_correctAnswer){
        ++m_score;
        m_scoreLabel->setText("Your Score: " + QString::number(m_score));

        m_timer->start(m_timeValue);
        nextLevel();
    }
    else{
        m_scoreLabel->setText("Oh no! Game over :(");

        QString message = QString("Game Over!\nYour final score is: %1\nThanks for playing!").arg(m_score);

        QMessageBox::information(this, "Game Ended", message);

        newGame();
    }
}

void ColorGame::timeFinished()
{
    m_scoreLabel->setText("Oh no! Time's up! Game over :(");

    QString message = QString("Game Over!\nYour final score is: %1\nThanks for playing!").arg(m_score);

    QMessageBox::information(this, "Game Ended", message);

    m_timer->stop();
    newGame();
}
