//
//  Tile2048.cpp
//  2048Clone
//
//  Created by huunc on 6/26/16.
//
//

#include "Tile2048.h"
#include "ui/CocosGUI.h"
#include "Constants.h"

using namespace cocos2d;

bool Tile2048::init()
{
    if (!Node::init()) {
        return false;
    }
    
    number = 0;
    
    this->timeline = CSLoader::createTimeline("Tile.csb");
    
    this->timeline->retain();
    
    return true;
}

void Tile2048::setPositionBasedOnRowColumn(int row, int col)
{
    this->row = row;
    this->col = col;
    resetPosition();
}

void Tile2048::resetPosition()
{
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    float dif = (this->screenWidth * 0.96 - this->width * ROWS) / float(ROWS + 1);
    this->setPosition(dif + float(col) * (this->width + dif) + width / 2.0f,
                      float(ROWS - row) * (this->width + dif) - width / 2.0f);
}

void Tile2048::setNumber(int number)
{
    this->number = number;
    Sprite* bg = this->getChildByName<Sprite*>("bg");
    cocos2d::ui::Text* numberText = bg->getChildByName<cocos2d::ui::Text*>("numberText");
    if (number > 0)
    {
        numberText->setString(to_string(number));
    }
    else
    {
        numberText->setString("");
    }
    std::string imageName = to_string("Assets/Images/tile_") + to_string(number) + to_string(".png");
    bg->setTexture(imageName);
}

void Tile2048::move(Direction direction, int numOfTiles)
{
    MoveBy *move_action;
    this->prevPostition = this->getPosition();
    float dif = (this->screenWidth * 0.96 - this->width * ROWS) / float(ROWS + 1);
    if (numOfTiles == ROWS)
        numOfTiles = ROWS - 1;
    float distance = (this->width + dif) * numOfTiles;
    switch (direction) {
        case Direction::LEFT:
        {
//            if (this->getPosition().x - distance < -width)
//            {
//                CCLOG("-------------------position %f < %f", this->getPosition().x - distance, -width);
//                distance = (this->width + dif) * (numOfTiles - 1);
//            }
            move_action = MoveBy::create(SLIDE_ANIMATION_TIME, Point(-distance, 0));  // create move left action
        }
            break;
        case Direction::RIGHT:
        {
//            if (this->getPosition().x + distance > (this->screenWidth + width))
//            {
//                CCLOG("-------------------position %f > %f", this->getPosition().x + distance, (this->screenWidth + width));
//                distance = (this->width + dif) * (numOfTiles - 1);
//            }
            move_action = MoveBy::create(SLIDE_ANIMATION_TIME, Point(distance, 0));  // create move right action
        }
            break;
        case Direction::UP:
        {
            move_action = MoveBy::create(SLIDE_ANIMATION_TIME, Point(0, distance));  // create move up action
        }
            break;
        case Direction::DOWN:
        {
            move_action = MoveBy::create(SLIDE_ANIMATION_TIME, Point(0, -distance));  // create move down action
        }
            break;
    }
    this->runAction(move_action);
//    this->dummyTile = dynamic_cast<Tile2048*>(CSLoader::createNode("Tile.csb"));
//    dummyTile->setNumber(this->number);
//    dummyTile->setAnchorPoint(Vec2(0.5f, 0.5f));
//    dummyTile->setPosition(this->getPosition());
//    mainGrid->addChild(dummyTile);
//    auto callback = CallFunc::create( this, callfunc_selector(Tile2048::actionFinished) );
//    auto sequence = Sequence::create(move_action, callback, nullptr);
//    this->setVisible(false);
//    this->runAction(sequence);
}

void Tile2048::actionFinished()
{
//    this->mainGrid->removeChild(dummyTile, true);
//    this->setVisible(true);
    resetPosition();
}

void Tile2048::runPopAnimation()
{
//    this->stopAllActions();
//    
//    this->runAction(this->timeline);
//    
//    this->timeline->play("popBg", false);
}

void Tile2048::runShowAnimation()
{
    this->stopAllActions();
    
    this->runAction(this->timeline);
    
    this->timeline->play("show", false);
}

void Tile2048::onExit()
{
    // release the retain we called in init
    this->timeline->release();
    
    Node::onExit();
}

int Tile2048::getNumber()
{
    return this->number;
}

bool Tile2048::equals(Tile2048* tile)
{
    if (this->number == tile->getNumber())
        return true;
    return false;
}

bool Tile2048::isEmpty()
{
    return this->number == 0;
}

void Tile2048::merge(Tile2048 *tile)
{
    this->setNumber(this->number + tile->getNumber());
    this->runPopAnimation();
}

void Tile2048::clear()
{
    this->stopAllActions();
    resetPosition();
    this->setNumber(0);
}

void Tile2048::setWidth(float width)
{
    this->width = width;
}

void Tile2048::setMainGrid(cocos2d::Sprite *mainGrid)
{
    this->mainGrid = mainGrid;
}

void Tile2048::setScreenWidth(float screenWidth)
{
    this->screenWidth = screenWidth;
}

void Tile2048::setIsMoving(bool isMoving)
{
    this->isMoving = isMoving;
}

bool Tile2048::getIsMoving()
{
    return this->isMoving;
}
