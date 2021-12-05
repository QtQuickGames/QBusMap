#include "featurelayerfromshapefile.h"

#include "FeatureLayer.h"
#include "LabelingTypes.h"
#include "Map.h"
#include "ShapefileFeatureTable.h"

using namespace Esri::ArcGISRuntime;

FeatureLayerFromShapefile::FeatureLayerFromShapefile(Esri::ArcGISRuntime::Map* map, const QString &name, const QString& pathToShapeFile, QQuickItem* parent)
    : QQuickItem(parent)
    , m_featureTable(new ShapefileFeatureTable(pathToShapeFile, this))
    , m_layer(new FeatureLayer(m_featureTable, this))
{
    if (name == "przystaneczki"){
        QString labelDefJSON = QStringLiteral("{");
        labelDefJSON += QLatin1String("\"labelExpressionInfo\" :{");
        labelDefJSON += QLatin1String("\"expression\" : \"$feature.Nazwa_skr\" },");
        labelDefJSON += QLatin1String("\"symbol\" : {");
        labelDefJSON += QLatin1String("\"type\": \"esriTS\",");
        labelDefJSON += QLatin1String("\"font\" : { \"family\": \"Arial\", \"size\" : 11,\"weight\" : \"bold\"}");
        labelDefJSON += QLatin1String("}");
        labelDefJSON += QLatin1String("}");

        LabelDefinition* labelDefinition = LabelDefinition::fromJson(labelDefJSON, this);
        labelDefinition->setPlacement(LabelingPlacement::Automatic);
        labelDefinition->setRemoveDuplicatesStrategy(LabelRemoveDuplicatesStrategy::All);

        m_layer->setLabelsEnabled(true);
        m_layer->labelDefinitions()->append(labelDefinition);
    }

    map->operationalLayers()->append(m_layer);
}

FeatureLayer* FeatureLayerFromShapefile::featureLayer()
{
    return m_layer;
}
