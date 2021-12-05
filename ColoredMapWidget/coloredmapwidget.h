#ifndef COLOREDMAPWIDGET_H
#define COLOREDMAPWIDGET_H

#include "ColoredMapWidget_global.h"

#include <QQuickWidget>

class ColoredMap;

class COLOREDMAPWIDGET_EXPORT ColoredMapWidget : public QQuickWidget {

    Q_OBJECT

public:
    ColoredMapWidget(const QUrl& source, QWidget* parent = nullptr);

    static void init();
    static void setApiKey(const QString& apiKey);

    void setFieldNames(const QStringList &fieldNames);
    void setBusStopFieldNames(const QStringList &fieldNames);
    void setRegionsData(const QStringList &regionsData);
signals:
    void takeSnapshot();

public slots:
    void setPathToTpkMapFile(const QString& pathToTpkMapFile);
    void setPathToShapeFile(const QString& name, const QString& pathToShapeFile);

private:
    ColoredMap* m_map = nullptr;
};

#endif // COLOREDMAPWIDGET_H
