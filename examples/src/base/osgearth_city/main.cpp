#include <iostream>
#include <osg/Notify>
#include <osgGA/GUIEventHandler>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>

#include <osgEarth/MapNode>
#include <osgEarth/viewpoint>
#include <osgEarth/Imagelayer>
#include <osgEarth/ModelLayer>


#include <osgEarthUtil/ExampleResources>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/AutoClipPlanehandler>
#include <osgEarthUtil/LogarithmicdepthBuffer>
#include <osgEarthFeatures/FeatureModelLayer>


#include <osgEarthDrivers/tms/TMSOptions>
#include <osgEarthDrivers/xyz/XYZOptions>
#include <osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include <osgEarthDrivers/model_feature_geom/FeatureGeomModelOptions>
#include <osgEarthDrivers/engine_rex/RexTerrainEngineOptions>


using namespace osgEarth;
using namespace osgEarth::Drivers;
using namespace osgEarth::Features;
using namespace osgEarth::Symbology;
using namespace osgEarth::Util;




#define IMAGE_URL "http://readymap.org/readymap/tiles/1.0.0/22/"
#define ELEVATION_URL "http:/readymap.org/readymap/tiles/1.0.0/9/"
#define BUIDINGS_URL "boston_buidings_utm19.shp"
#define RESOURCE_LIB_URL "resources/textures_us/catalog.xml"
#define STREETS_URL      "boston-scl-utm19n-meters.shp"
#define PARKS_URL        "boston-parks.shp"
#define TREE_MODEL_URL   "loopix/tree4.osgb"

void addImagery(Map* map);
void addElevation(Map* map);
void addBuildings(Map* map);
void addStreets(Map* map);
void addParks(Map* map);

int main(int argc, char** argv)
{

    osg::ArgumentParser arguments(&argc, argv);

    Map* map = new Map();

    addImagery(map);
    addElevation(map);
    addBuildings(map);
    addStreets(map);
    addParks(map);

    osgViewer::Viewer viewer(arguments);
    
    EarthManipulator* manip = new EarthManipulator();
    viewer.setCameraManipulator(manip);

    osg::Group* root = new osg::Group;
    viewer.setSceneData(root);

    MapNode* mapNode = new MapNode(map);
    root->addChild(mapNode);

    // process cmdline args
    MapNodeHelper helper;
    helper.configureView(&viewer);
    helper.parse(mapNode,arguments,&viewer,root,new LabelControl("city demo"));

    //// zoom to a good startup position
    //manip->setViewpoint(Viewpoint(
    //    -71.0763,42.34425,0, // longitude latitude altitude
    //    24.261,-21.6,3450.0), // heading, pitch range
    //    5.0); // duration
    manip->setViewpoint(osgEarth::Viewpoint("Home",
        -71.0763,42.34425,0, // longitude latitude altitude
        24.261,-21.6,3450.0), // heading, pitch range
        0.1); // duration

    
    // This will mitigate near clip plane issue if you zoom in close to the ground
    LogarithmicDepthBuffer buf;
    buf.install(viewer.getCamera());

    return viewer.run();

}


void addImagery(Map* map)
{

    // add a TMS imagery layer
    TMSOptions imagery;
    imagery.url() = IMAGE_URL;
    map->addLayer(new  ImageLayer("ReadyMap imagery",imagery));
    map->addLayer( new ImageLayer("ReadyMap imagery", imagery) );
}

void addElevation(Map* map)
{


}

void addBuildings(Map* map)
{

}

void addStreets(Map* map)
{

}

void addParks(Map* map)
{

}