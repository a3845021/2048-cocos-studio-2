//
//  Tile2048.hpp
//  2048Clone
//
//  Created by huunc on 6/26/16.
//
//

#ifndef Tile2048_h
#define Tile2048_h

#include "cocos2d.h"
#include "Constants.h"
#include "cocostudio/CocoStudio.h"

class Tile2048 : public cocos2d::Node
{
public:
    CREATE_FUNC(Tile2048);

    bool init() override;
    void onExit() override;
    
    void setNumber(int number);
    int getNumber();
    void setIsMoving(bool isMoving);
    bool getIsMoving();
    void increaseNumOfMovesByOne();
    int getNumOfMoves();
    void setWidth(float width);
    void setScreenWidth(float screenWidth);
    
    bool equals(Tile2048* tile);
    void merge(Tile2048* tile);
    void clear();
    void setPositionBasedOnRowColumn(int row, int col);
    
    void move(Direction direction);
    bool isEmpty();
    
    void runPopAnimation();
    void runShowAnimation();
    void actionFinished();
    void resetPosition();
protected:
    int number;
    int row;
    int col;
    int numOfMoves;
    float width;
    float screenWidth;
    cocos2d::Vec2 prevPostition;
    bool isMoving;
    
    cocostudio::timeline::ActionTimeline* timeline;
};

#endif /* Tile2048_h */
