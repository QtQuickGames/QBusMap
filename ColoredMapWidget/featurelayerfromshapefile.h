#ifndef FEATURELAYERFROMSHAPEFILE_H
#define FEATURELAYERFROMSHAPEFILE_H

#include <QQuickItem>

namespace Esri {
namespace ArcGISRuntime {
    class Map;
    class FeatureLayer;
    class ShapefileFeatureTable;
}
}

class FeatureLayerFromShapefile : public QQuickItem {
    Q_OBJECT
public:
    explicit FeatureLayerFromShapefile(Esri::ArcGISRuntime::Map* map, const QString& name, const QString& pathToShapeFile, QQuickItem* parent = nullptr);

    Esri::ArcGISRuntime::FeatureLayer* featureLayer();

private:
    Esri::ArcGISRuntime::ShapefileFeatureTable* m_featureTable = nullptr;
    Esri::ArcGISRuntime::FeatureLayer* m_layer = nullptr;
};

#endif // FEATURELAYERFROMSHAPEFILE_H
