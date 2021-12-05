#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickWidget>

class ColoredMapWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void renderToPixmap();

private:
    template <class T>
    void saveToFile(QWidget* parent, T* saveable);

private:
    ColoredMapWidget* m_coloredMapWidget;
    QStringList m_regionsData;
};
#endif // MAINWINDOW_H
