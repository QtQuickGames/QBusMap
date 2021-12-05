#include "coloredmap.h"

#include "ArcGISTiledLayer.h"
#include "FeatureLayer.h"
#include "Map.h"
#include "MapQuickView.h"
#include "SimpleFillSymbol.h"
#include "SimpleLineSymbol.h"
#include "TileCache.h"
#include "UniqueValueRenderer.h"
#include "featurelayerfromshapefile.h"

using namespace Esri::ArcGISRuntime;

ColoredMap::ColoredMap(QQuickItem* parent)
    : QQuickItem(parent)
    , m_dzielniceUniqueValueRenderer(new UniqueValueRenderer(this))
    , m_uliceUniqueValueRenderer(new UniqueValueRenderer(this))
    , m_przystankiUniqueValueRenderer(new UniqueValueRenderer(this))
{
    SimpleLineSymbol dzielniceSimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor("lightgray"), 1, this);
    SimpleFillSymbol dzielniceDefaultSymbol(SimpleFillSymbolStyle::Solid, QColor("white"), &dzielniceSimpleLineSymbol, this);
    m_dzielniceUniqueValueRenderer->setDefaultSymbol(&dzielniceDefaultSymbol);

    SimpleLineSymbol uliceSimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor("lightgray"), 1, this);
    SimpleFillSymbol uliceDefaultSymbol(SimpleFillSymbolStyle::Solid, QColor("ghostwhite"), &uliceSimpleLineSymbol, this);
    m_uliceUniqueValueRenderer->setDefaultSymbol(&uliceDefaultSymbol);

    SimpleFillSymbol *simpleFillSymbol = new SimpleFillSymbol(SimpleFillSymbolStyle::Null, QColor("black"), new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor("gray"), 2, this), this);
    m_przystankiUniqueValueRenderer->setDefaultSymbol(simpleFillSymbol);
}

void ColoredMap::init()
{
    qmlRegisterType<MapQuickView>("QtQuickSoft.Samples", 1, 0, "MapView");
    qmlRegisterType<ColoredMap>("QtQuickSoft.Samples", 1, 0, "ColoredMap");
}

void ColoredMap::setPathToTpkMapFile(const QString& pathToTpkMapFile)
{
    TileCache* tileCache = new TileCache(pathToTpkMapFile, this);
    ArcGISTiledLayer* tiledLayer = new ArcGISTiledLayer(tileCache, this);

    Basemap* basemap = new Basemap(tiledLayer, this);

    m_map = new Map(basemap, this);
    m_map->setBackgroundColor("#fafafa");
    m_mapView->setMap(m_map);
}

void ColoredMap::setPathToShapeFile(const QString& name, const QString& pathToShapeFile)
{
    FeatureLayerFromShapefile * featureLayer = new FeatureLayerFromShapefile(m_map, name, pathToShapeFile, this);
    m_map->operationalLayers()->append(featureLayer->featureLayer());

    if(name == "dzielnice"){
        featureLayer->featureLayer()->setRenderer(m_dzielniceUniqueValueRenderer);
    } else if (name == "ulice"){
        featureLayer->featureLayer()->setRenderer(m_uliceUniqueValueRenderer);
    } else if (name == "przystanki"){
        //featureLayer->featureLayer()->setRenderer(m_przystankiUniqueValueRenderer);
    }
}

void ColoredMap::setFieldNames(const QStringList& fieldNames)
{
    m_dzielniceUniqueValueRenderer->setFieldNames(fieldNames);
}

void ColoredMap::setBusStopFieldNames(const QStringList &fieldNames)
{
    m_przystankiUniqueValueRenderer->setFieldNames(fieldNames);
}

void ColoredMap::setRegionsData(const QStringList &regionsData)
{
    if (m_regionsData == regionsData) {
        return;
    }

    m_dzielniceUniqueValueRenderer->uniqueValues()->clear();
    m_przystankiUniqueValueRenderer->uniqueValues()->clear();
    foreach (auto value, regionsData) {
        m_dzielniceUniqueValueRenderer->uniqueValues()->append(createDistrictUniqueValue(value));
        m_przystankiUniqueValueRenderer->uniqueValues()->append(createBusStopUniqueValue(value));
    }
}

UniqueValue* ColoredMap::createDistrictUniqueValue(const QString& regionData)
{
    SimpleLineSymbol simpleLineSymbol(SimpleLineSymbolStyle::Solid, "darkgrey", 1);
    SimpleFillSymbol fillSymbol(SimpleFillSymbolStyle::Solid, "#F8D5BC", &simpleLineSymbol);

    return new UniqueValue(regionData, "The State of " + regionData, QVariantList() << regionData, &fillSymbol);
}

UniqueValue *ColoredMap::createBusStopUniqueValue(const QString &regionData)
{
    SimpleFillSymbol *simpleFillSymbol = new SimpleFillSymbol(SimpleFillSymbolStyle::Solid, QColor("red"), new SimpleLineSymbol(SimpleLineSymbolStyle::Solid, QColor("red"), 2, this), this);

    return new UniqueValue(regionData, "The State of " + regionData, QVariantList() << regionData, simpleFillSymbol, this);
}

MapQuickView* ColoredMap::mapView() const
{
    return m_mapView;
}

void ColoredMap::setMapView(MapQuickView* mapView)
{
    if (!mapView || m_mapView == mapView)
        return;

    m_mapView = mapView;
    m_mapView->setMap(m_map);

    emit mapViewChanged();
}
