#ifndef COLOREDMAP_H
#define COLOREDMAP_H

namespace Esri {
namespace ArcGISRuntime {
    class Map;
    class MapQuickView;
    class UniqueValue;
    class UniqueValueRenderer;
}
}

#include <QColor>
#include <QHash>
#include <QObject>
#include <QQuickItem>
#include <QMap>

class FeatureLayerFromShapefile;
class UniqueColorValue;

class ColoredMap : public QQuickItem {

    Q_OBJECT
    Q_PROPERTY(Esri::ArcGISRuntime::MapQuickView* mapView READ mapView WRITE setMapView NOTIFY mapViewChanged)

public:
    ColoredMap(QQuickItem* parent = nullptr);

    static void init();

    void setPathToTpkMapFile(const QString& pathToTpkMapFile);
    void setPathToShapeFile(const QString& name, const QString& pathToShapeFile);
    void setFieldNames(const QStringList& fieldNames);
    void setBusStopFieldNames(const QStringList& fieldNames);
    void setRegionsData(const QStringList& regionsData);

signals:
    void takeSnapshot();
    void mapViewChanged();

private:
    Esri::ArcGISRuntime::MapQuickView* mapView() const;
    void setMapView(Esri::ArcGISRuntime::MapQuickView* mapView);
    QColor calculateColor(const double& value, const double& min, const double& max, const QColor& lowColor, const QColor& highColor);
    int calculateColorLevel(const double& percent, const int& from, const int& to) const;
    Esri::ArcGISRuntime::UniqueValue *createDistrictUniqueValue(const QString &regionData);
    Esri::ArcGISRuntime::UniqueValue *createBusStopUniqueValue(const QString &regionData);

private:
    Esri::ArcGISRuntime::Map* m_map = nullptr;
    Esri::ArcGISRuntime::MapQuickView* m_mapView = nullptr;
    Esri::ArcGISRuntime::UniqueValueRenderer* m_dzielniceUniqueValueRenderer = nullptr;
    Esri::ArcGISRuntime::UniqueValueRenderer* m_uliceUniqueValueRenderer = nullptr;
    Esri::ArcGISRuntime::UniqueValueRenderer* m_przystankiUniqueValueRenderer = nullptr;

    QString m_pathToMobileMapPackage;
    QString m_pathToTpkMapFile;
    QString m_pathToShapeFile;
    QStringList m_regionsData;
};

#endif // COLOREDMAP_H
