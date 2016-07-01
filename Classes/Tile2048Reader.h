//
//  Tile2048Reader.hpp
//  2048Clone
//
//  Created by huunc on 6/26/16.
//
//

#ifndef Tile2048Reader_h
#define Tile2048Reader_h

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class Tile2048Reader : public cocostudio::NodeReader
{
public:
    static Tile2048Reader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* Tile2048Reader_h */
