TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += ./CfgReader
SUBDIRS += ./filesystem
SUBDIRS += ./log
SUBDIRS += ./tcp-connection
SUBDIRS += ./asound
SUBDIRS += ./simulator

SUBDIRS += ./addons/default-vehicle
SUBDIRS += ./addons/test-loco
SUBDIRS += ./addons/sapsan-motor
SUBDIRS += ./addons/sapsan-non-motor
SUBDIRS += ./addons/es1-motor
SUBDIRS += ./addons/es1-non-motor
SUBDIRS += ./addons/passcar
SUBDIRS += ./addons/vl60
SUBDIRS += ./addons/tep70
SUBDIRS += ./addons/chs4t

SUBDIRS += ./launcher

SUBDIRS += ./viewer

SUBDIRS += ./tools/profconv
SUBDIRS += ./tools/pathconv

