#ifndef COLORGAME_H
#define COLORGAME_H

#include <QDialog>

class QWidget;
class QPushButton;
class QLabel;
class QTimer;

class ColorGame: public QDialog
{
    Q_OBJECT //macro for connect

public:
    ColorGame(QWidget* parent = nullptr);


private:
    void createWidgets();
    void setupLayout();
    void makeConnetions();
    void nextLevel();
    void newGame();


private slots:
    void colorButtonClicked(int);
    void timeFinished();

private:

    QPushButton* m_colorButtons[6];
    QLabel* m_titleLabel;
    QLabel* m_scoreLabel;
    QLabel* m_describeLabel;
    QTimer* m_timer;
    int m_score;
    int m_correctAnswer;
    int m_timeValue;
};

#endif // COLORGAME_H
