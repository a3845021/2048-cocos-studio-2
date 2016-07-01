//
//  Tile2048Reader.cpp
//  2048Clone
//
//  Created by huunc on 6/26/16.
//
//

#include "Tile2048Reader.h"
#include "Tile2048.h"

using namespace cocos2d;

static Tile2048Reader* _instanceTileReader = nullptr;

Tile2048Reader* Tile2048Reader::getInstance()
{
    if (!_instanceTileReader)
    {
        _instanceTileReader = new Tile2048Reader();
    }
    
    return _instanceTileReader;
}

void Tile2048Reader::purge()
{
    CC_SAFE_DELETE(_instanceTileReader);
}

Node* Tile2048Reader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
    Tile2048* node = Tile2048::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    
    return node;
}