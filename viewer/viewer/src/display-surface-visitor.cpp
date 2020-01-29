#include    "display-surface-visitor.h"

#include    <osgQt/QWidgetImage>
#include    <osgViewer/ViewerEventHandlers>
#include    <osg/Material>
#include    <osg/Texture2D>

DisplaySurfaceVisitor::DisplaySurfaceVisitor(display_container_t *dc)
    : osg::NodeVisitor()
    , dc(dc)

{

}

void DisplaySurfaceVisitor::apply(osg::Geode &geode)
{
    dc->widgetImage = new osgQt::QWidgetImage(dc->display);
    dc->texture = new osg::Texture2D(dc->widgetImage.get());
    dc->texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
    dc->texture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);

    osg::StateSet *stateset = geode.getOrCreateStateSet();
    stateset->setTextureAttributeAndModes(0, dc->texture.get());

    dc->handler = new osgViewer::InteractiveImageHandler(dc->widgetImage.get());
    geode.getDrawable(0)->setEventCallback(dc->handler.get());
    geode.getDrawable(0)->setCullCallback(dc->handler.get());

    traverse(geode);
}
