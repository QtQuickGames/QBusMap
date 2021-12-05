#ifdef Q_OS_WIN
#include <Windows.h>
#endif

#include "mainwindow.h"

#include "coloredmapwidget.h"
#include <QList>
#include <QPair>
#include <QTimer>
#include <QtWidgets>

typedef QPair<QString, double> RegionData;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QMdiArea* centralWidget = new QMdiArea;

    const QString dataPath = QApplication::applicationDirPath();
    const QString pathToTpkMapFile = dataPath + "/resources/tpk/z.tpk";
    const QString pathToDzielniceShapeFile = dataPath + "/resources/shp/obreby.shp";
    const QString pathToDrogiShapeFile = dataPath + "/resources/shp/droga.shp";
    const QString pathToPrzystankiShapeFile = dataPath + "/resources/shp/przystaneczki.shp";

    m_regionsData.append("LYSKI");
    m_regionsData.append("MSZANA");
    m_regionsData.append("JEJKOWICE");

    ColoredMapWidget::init();
    ColoredMapWidget::setApiKey(QStringLiteral("AAPK7d814b4e3e434463b27dee9f608b56cfaeOOoiwjfT4V4BZLtPGIwWF6nEEMu5Ur_a5NIuxAj-tXUwNX0PE5cmU2B38OaQBK"));

    QUrl source(QStringLiteral("qrc:/quickwidget/ColoredMapWidget.qml"));
    m_coloredMapWidget = new ColoredMapWidget(source, this);

    m_coloredMapWidget->setPathToTpkMapFile(pathToTpkMapFile);
    m_coloredMapWidget->setPathToShapeFile(QStringLiteral("dzielnice"), pathToDzielniceShapeFile);
    m_coloredMapWidget->setPathToShapeFile(QStringLiteral("ulice"), pathToDrogiShapeFile);
    m_coloredMapWidget->setPathToShapeFile(QStringLiteral("przystanki"), pathToPrzystankiShapeFile);

    m_coloredMapWidget->setFieldNames(QStringList() << "JPT_NAZWA_");
    m_coloredMapWidget->setBusStopFieldNames(QStringList() << "Gmina" << "Osiedle" << "Miejscowos");
    m_coloredMapWidget->setRegionsData(m_regionsData);

    m_coloredMapWidget->resize(this->width() * 2, this->height() * 2);
    m_coloredMapWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    connect(m_coloredMapWidget, &ColoredMapWidget::takeSnapshot, this, &MainWindow::renderToPixmap);

    centralWidget->addSubWindow(m_coloredMapWidget);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::renderToPixmap()
{
    QPixmap pixmap(m_coloredMapWidget->size());
    m_coloredMapWidget->render(&pixmap);
    saveToFile(this, &pixmap);
}

template <class T>
void MainWindow::saveToFile(QWidget* parent, T* saveable)
{
    QFileDialog fd(parent);
    fd.setAcceptMode(QFileDialog::AcceptSave);
    fd.setDefaultSuffix(QStringLiteral("png"));
    fd.selectFile(QStringLiteral("test.png"));
    if (fd.exec() == QDialog::Accepted) {
        QStringList selectedFiles = fd.selectedFiles();
        if (selectedFiles.size() > 0) {
            saveable->save(selectedFiles.first());
        }
    }
}
