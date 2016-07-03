#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Tile2048Reader.h"
#include <cmath>
#include "Constants.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
     // 1. super init first
     if ( !Layer::init() )
     {
     return false;
     }
     
     Size visibleSize = Director::getInstance()->getVisibleSize();
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     
     /////////////////////////////
     // 2. add a menu item with "X" image, which is clicked to quit the program
     //    you may modify it.
     
     // add a "close" icon to exit the progress. it's an autorelease object
     auto closeItem = MenuItemImage::create(
     "CloseNormal.png",
     "CloseSelected.png",
     CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
     
     closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
     origin.y + closeItem->getContentSize().height/2));
     
     // create menu, it's an autorelease object
     auto menu = Menu::create(closeItem, NULL);
     menu->setPosition(Vec2::ZERO);
     this->addChild(menu, 1);
     
     /////////////////////////////
     // 3. add your codes below...
     
     // add a label shows "Hello World"
     // create and initialize a label
     
     auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
     
     // position the label on the center of the screen
     label->setPosition(Vec2(origin.x + visibleSize.width/2,
     origin.y + visibleSize.height - label->getContentSize().height));
     
     // add the label as a child to this layer
     this->addChild(label, 1);
     
     // add "HelloWorld" splash screen"
     auto sprite = Sprite::create("HelloWorld.png");
     
     // position the sprite on the center of the screen
     sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
     
     // add the sprite as a child to this layer
     this->addChild(sprite, 0);
     **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    def = UserDefault::sharedUserDefault();
    this->bestScore = def->getIntegerForKey("highscore", 0);
    
    CSLoader* instance = CSLoader::getInstance();
    // Be very careful to do TileReader::getInstance, not TileReader::getInstance() which will crash
    instance->registReaderObject("Tile2048Reader", (ObjectFactory::Instance) Tile2048Reader::getInstance);
    
    this->mainGrid = rootNode->getChildByName<Sprite*>("mainBG");
    this->overText = rootNode->getChildByName<cocos2d::ui::Text*>("overText");
    this->gameOver = false;
    
    this->score = 0;
    this->undoScore = 0;
    
    auto scoreBg = rootNode->getChildByName("scoreBg");
    this->scoreText = scoreBg->getChildByName<cocos2d::ui::Text*>("scoreText");
    auto bestBg = rootNode->getChildByName("bestBg");
    this->bestText = bestBg->getChildByName<cocos2d::ui::Text*>("bestText");
    this->btnNewgame = rootNode->getChildByName<cocos2d::ui::Button*>("btnNewgame");
    this->btnNewgame->addTouchEventListener(CC_CALLBACK_2(HelloWorld::newgame, this));
    
    showScore();
    
    
    Size size = Director::getInstance()->getVisibleSize();
    rootNode->setContentSize(size);
    ui::Helper::doLayout(rootNode);
    
    addChild(rootNode);
    
    return true;
}

void HelloWorld::onEnter()
{
    Layer::onEnter();
    
    this->setupGrid();
    
    this->setupTouchHandling();
}

void HelloWorld::newgame(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            if (tileArray.size() == ROWS * ROWS)
            {
                for (int i = 0; i < ROWS; i++)
                {
                    for (int j = 0; j < ROWS; j++)
                    {
                        tileArray.at(i * ROWS + j)->clear();
                    }
                }
                
                int index1 = generateRandomIndex(0, ROWS * ROWS);
                this->tileArray.at(index1)->setNumber(2);
                this->tileArray.at(index1)->runPopAnimation();
                
                int index2 = generateRandomIndex(0, ROWS * ROWS);
                this->tileArray.at(index2)->setNumber(4);
                this->tileArray.at(index2)->runPopAnimation();
                
                score = 0;
                gameOver = false;
                overText->setVisible(false);
            }
            
        }
            break;
        default:
            break;
    }
    
}

void HelloWorld::setupGrid()
{
    //    tileWidth = this->mainGrid->getContentSize().width / float(ROWS);
    float screenWidth = this->getContentSize().width;
    
    // setup background tile
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < ROWS; col++)
        {
            Tile2048* tile = dynamic_cast<Tile2048*>(CSLoader::createNode("Tile.csb"));
            tile->setScreenWidth(screenWidth);
            tile->setLocalZOrder(1);
            tile->setWidth(130);
            tile->setPositionBasedOnRowColumn(row, col);
            tile->setNumber(0);
            
            mainGrid->addChild(tile);
        }
    }
    
    
    tileArray.reserve(ROWS * ROWS);
    
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < ROWS; col++)
        {
            Tile2048* tile = dynamic_cast<Tile2048*>(CSLoader::createNode("Tile.csb"));
            tile->setScreenWidth(screenWidth);
            tile->setLocalZOrder(100);
            tile->setWidth(130);
            tile->setPositionBasedOnRowColumn(row, col);
            tile->setNumber(0);
            //            tile->setNumber(row * ROWS + col);
            
            //            tile->setAnchorPoint(Vec2(1.0f, 0.0f));
            //            tile->setPosition(tileWidth * float(j), tileWidth * float(i + 1));
            //            float random = CCRANDOM_0_1();
            //            if (random < 0.5f)
            //            {
            //                tile->setNumber(2);
            //            }
            //            else
            //            {
            //                tile->setNumber(4);
            //            }
            
            mainGrid->addChild(tile);
            tileArray.pushBack(tile);
            
        }
    }
    
    int index1 = generateRandomIndex(0, ROWS * ROWS);
    this->tileArray.at(index1)->setNumber(2);
    
    int index2 = generateRandomIndex(0, ROWS * ROWS);
    this->tileArray.at(index2)->setNumber(4);
}

int HelloWorld::generateRandomIndex(int min, int max)
{
    return min + (rand() % (int)(max - min));
}

void HelloWorld::setupTouchHandling()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    isTouchDown = false;
    
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
    
    this->scheduleUpdate();
}

void HelloWorld::update(float dt)
{
    if (true == isTouchDown)
    {
        if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.05)
        {
            //            CCLOG("SWIPED LEFT");
            onSwipe(Direction::LEFT);
            isTouchDown = false;
            
        }
        else if (initialTouchPos[0] - currentTouchPos[0] < - visibleSize.width * 0.05)
        {
            //            CCLOG("SWIPED RIGHT");
            onSwipe(Direction::RIGHT);
            isTouchDown = false;
            
        }
        else if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.06)
        {
            //            CCLOG("SWIPED DOWN");
            onSwipe(Direction::DOWN);
            isTouchDown = false;
            
        }
        else if (initialTouchPos[1] - currentTouchPos[1] < - visibleSize.width * 0.06)
        {
            //            CCLOG("SWIPED UP");
            onSwipe(Direction::UP);
            isTouchDown = false;
        }
        
    }
    
}

void HelloWorld::displayGameOver()
{
    this->overText->setString("GAME OVER!");
    this->overText->setVisible(true);
}

void HelloWorld::displayWin()
{
    this->overText->setString("YOU WIN!");
    this->overText->setVisible(true);
}

bool HelloWorld::checkFull()
{
    bool flag = true;
    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (tileArray.at(i * ROWS + j)->isEmpty()) {
                flag = false;
                break;
            }
        }
    }
    
    return flag;
}

void HelloWorld::generateNewTile()
{
    bool flag = true;
    if (!checkFull())
    {
        while (flag)
        {
            int i = generateRandomIndex(0, ROWS);
            int j = generateRandomIndex(0, ROWS);
            if (tileArray.at(i * ROWS + j)->isEmpty())
            {
                //                float random = CCRANDOM_0_1();
                //                if (random < 0.5f)
                //                {
                tileArray.at(i * ROWS + j)->setNumber(2);
                tileArray.at(i * ROWS + j)->runShowAnimation();
                //                }
                //                else
                //                {
                //                    tileArray.at(i * ROWS + j)->setNumber(4);
                //                }
                flag = false;
            }
        }
    }
}

void HelloWorld::showScore()
{
    this->scoreText->setString(to_string(score));
    this->bestText->setString(to_string(bestScore));
}

void HelloWorld::onSwipe(Direction direction)
{
    if (gameOver)
        return;
    switch (direction) {
        case Direction::LEFT:
        {
            moveLeftAnimation();
            break;
        }
        case Direction::UP:
        {
            moveUpAnimation();
        }
            break;
        case Direction::RIGHT:
        {
            moveRightAnimation();
        }
            break;
        case Direction::DOWN:
        {
            moveDownAnimation();
        }
            break;
    }
    
    showScore();
    
    // check win or lose
    int find_max=calculateMax();
    if(find_max == 2048)
    {
        displayWin();
        gameOver = true;
        return;
    }
    
    if (checkFull())
    {
        if (checkGameEnds())
        {
            displayGameOver();
            gameOver = true;
        }
    }
}

bool HelloWorld::checkGameEnds()
{
    bool flag = true;
    
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < ROWS - 1; j++)
        {
            if(tileArray.at(i * ROWS + j)->equals(tileArray.at(i * ROWS + j + 1)))
            {
                flag = false;
                break;
            }
        }
        if(flag == false)
        {
            break;
        }
    }
    if(flag == true)
    {
        for(int i = 0; i < ROWS - 1; i++)
        {
            for(int j = 0; j < ROWS; j++)
            {
                if(tileArray.at(i * ROWS + j)->equals(tileArray.at((i + 1) * ROWS + j)))
                {
                    flag = false;
                    break;
                }
            }
            if(flag == false)
            {
                break;
            }
        }
    }
    
    return flag;
}

int HelloWorld::calculateMax()
{
    int max = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            if (tileArray.at(i * ROWS + j)->getNumber() > max)
            {
                max = tileArray.at(i * ROWS + j)->getNumber();
            }
        }
    }
    
    return max;
}

void HelloWorld::doMoveLeft()
{
    moveLeft();
    sumLeft();
    moveLeft();
    generateNewTile();
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < ROWS; j++)
        {
            tileArray.at(i * ROWS + j)->setIsMoving(false);
            tileArray.at(i * ROWS + j)->setVisible(true);
        }
}

void HelloWorld::doMoveRight()
{
    moveRight();
    sumRight();
    moveRight();
    generateNewTile();
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < ROWS; j++)
        {
            tileArray.at(i * ROWS + j)->setIsMoving(false);
            tileArray.at(i * ROWS + j)->setVisible(true);
        }
}

void HelloWorld::doMoveUp()
{
    moveUp();
    sumUp();
    moveUp();
    generateNewTile();
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < ROWS; j++)
        {
            tileArray.at(i * ROWS + j)->setIsMoving(false);
            tileArray.at(i * ROWS + j)->setVisible(true);
        }
}

void HelloWorld::doMoveDown()
{
    moveDown();
    sumDown();
    moveDown();
    generateNewTile();
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < ROWS; j++)
        {
            tileArray.at(i * ROWS + j)->setIsMoving(false);
            tileArray.at(i * ROWS + j)->setVisible(true);
        }
}

void HelloWorld::moveLeftAnimation()
{
    this->runAction( Sequence::create(
                                      DelayTime::create(DELAY_FUNCTION_TIME),
                                      CallFunc::create(CC_CALLBACK_0(HelloWorld::doMoveLeft, this)),
                                      nullptr));
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(!tileArray.at(i * ROWS + j)->isEmpty())
            {
                if (j < ROWS - 1 && tileArray.at(i * ROWS + j)->equals(tileArray.at(i * ROWS +j + 1)))
                {
                    tileArray.at(i * ROWS + j + 1)->increaseNumOfMovesByOne();
                    for (int k = j + 2; k < ROWS; k++)
                    {
                        tileArray.at(i * ROWS + k)->increaseNumOfMovesByOne();
                    }
                }
            }
            else
            {
                for(int k = j + 1; k < ROWS; k++)
                {
                    if(!tileArray.at(i * ROWS + k)->isEmpty())
                    {
                        tileArray.at(i * ROWS + k)->increaseNumOfMovesByOne();
                    }
                }
            }
            
        }
    }
    
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(!tileArray.at(i * ROWS + j)->isEmpty())
            {
                tileArray.at(i * ROWS + j)->move(Direction::LEFT);
                tileArray.at(i * ROWS + j)->setIsMoving(true);
            }
        }
    }
    
}

void HelloWorld::moveLeft()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(tileArray.at(i * ROWS + j)->isEmpty())
            {
                for(int k = j + 1; k < ROWS; k++)
                {
                    if(!tileArray.at(i * ROWS + k)->isEmpty())
                    {
                        tileArray.at(i * ROWS + j)->setNumber(tileArray.at(i * ROWS + k)->getNumber());
                        tileArray.at(i * ROWS + k)->clear();
                        break;
                    }
                }
            }
            
        }
    }
    
    
}

void HelloWorld::moveRightAnimation()
{
    this->runAction( Sequence::create(
                                      DelayTime::create(DELAY_FUNCTION_TIME),
                                      CallFunc::create(CC_CALLBACK_0(HelloWorld::doMoveRight, this)),
                                      nullptr));
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < ROWS; j++)
        {
            if (tileArray.at(i * ROWS + j)->isEmpty())
                tileArray.at(i * ROWS + j)->setVisible(false);
        }
    for(int i = 0; i < ROWS; i++)
    {
        for(int j= ROWS - 1; j >= 0; j--)
        {
            if(!tileArray.at(i * ROWS + j)->isEmpty())
            {
                if (j > 0 && tileArray.at(i * ROWS + j)->equals(tileArray.at(i * ROWS +j - 1)))
                {
                    tileArray.at(i * ROWS + j - 1)->increaseNumOfMovesByOne();
                    for (int k = j - 2; k > 0; k--)
                    {
                        tileArray.at(i * ROWS + k)->increaseNumOfMovesByOne();
                    }
                }
            }
            else
            {
                for(int k = j - 1; k >= 0; k--)
                {
                    if(!tileArray.at(i * ROWS + k)->isEmpty())
                    {
                        tileArray.at(i * ROWS + k)->increaseNumOfMovesByOne();
                    }
                }
            }
            
        }
    }
    
    for(int i = 0; i < ROWS; i++)
    {
        for(int j= ROWS - 1; j >= 0; j--)
        {
            if(!tileArray.at(i * ROWS + j)->isEmpty())
            {
                tileArray.at(i * ROWS + j)->move(Direction::RIGHT);
                tileArray.at(i * ROWS + j)->setIsMoving(true);
            }
        }
    }
}


void HelloWorld::moveRight()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j= ROWS - 1; j >= 0; j--)
        {
            if(tileArray.at(i * ROWS + j)->isEmpty())
            {
                for(int k = j - 1; k >= 0; k--)
                {
                    if(!tileArray.at(i * ROWS + k)->isEmpty())
                    {
                        tileArray.at(i * ROWS + j)->setNumber(tileArray.at(i * ROWS + k)->getNumber());
                        tileArray.at(i * ROWS + k)->clear();
                        break;
                    }
                }
            }
        }
    }
    
}

void HelloWorld::moveUpAnimation()
{
    this->runAction( Sequence::create(
                                      DelayTime::create(DELAY_FUNCTION_TIME),
                                      CallFunc::create(CC_CALLBACK_0(HelloWorld::doMoveUp, this)),
                                      nullptr));
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(!tileArray.at(j * ROWS + i)->isEmpty())
            {
                if (j < ROWS - 1 && tileArray.at(j * ROWS + i)->equals(tileArray.at((j + 1) * ROWS + i)))
                {
                    tileArray.at((j + 1) * ROWS + i)->increaseNumOfMovesByOne();
                    for (int k = j + 2; k < ROWS; k++)
                    {
                        tileArray.at(k * ROWS + i)->increaseNumOfMovesByOne();
                    }
                }
            }
            else
            {
                for(int k = j + 1; k < ROWS; k++)
                {
                    if(!tileArray.at(k * ROWS + i)->isEmpty())
                    {
                        tileArray.at(k * ROWS + i)->increaseNumOfMovesByOne();
                    }
                }
            }
            
        }
    }
    
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(!tileArray.at(j * ROWS + i)->isEmpty())
            {
                tileArray.at(j * ROWS + i)->move(Direction::UP);
                tileArray.at(j * ROWS + i)->setIsMoving(true);
            }
        }
    }
}

void HelloWorld::moveUp()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(tileArray.at(j * ROWS + i)->isEmpty())
            {
                for(int k = j + 1; k < ROWS; k++)
                {
                    if(!tileArray.at(k * ROWS + i)->isEmpty())
                    {
                        tileArray.at(j * ROWS + i)->setNumber(tileArray.at(k * ROWS + i)->getNumber());
                        tileArray.at(k * ROWS + i)->clear();
                        break;
                    }
                }
            }
        }
    }
}

void HelloWorld::moveDownAnimation()
{
    this->runAction( Sequence::create(
                                      DelayTime::create(DELAY_FUNCTION_TIME),
                                      CallFunc::create(CC_CALLBACK_0(HelloWorld::doMoveDown, this)),
                                      nullptr));
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < ROWS; j++)
        {
            if (tileArray.at(i * ROWS + j)->isEmpty())
                tileArray.at(i * ROWS + j)->setVisible(false);
        }
    
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = ROWS - 1;j >= 0; j--)
        {
            if(!tileArray.at(j * ROWS + i)->isEmpty())
            {
                if (j > 0 && tileArray.at(j * ROWS + i)->equals(tileArray.at((j - 1) * ROWS + i)))
                {
                    tileArray.at((j - 1) * ROWS + i)->increaseNumOfMovesByOne();
                    for (int k = j - 2; k > 0; k--)
                    {
                        tileArray.at(k * ROWS + i)->increaseNumOfMovesByOne();
                    }
                }
            }
            else
            {
                for(int k = j - 1; k >= 0; k--)
                {
                    if(!tileArray.at(k * ROWS + i)->isEmpty() && !tileArray.at(k * ROWS + i)->getIsMoving())
                    {
                        tileArray.at(k * ROWS + i)->increaseNumOfMovesByOne();
                    }
                }
            }
            
        }
    }
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = ROWS - 1;j >= 0; j--)
        {
            if(!tileArray.at(j * ROWS + i)->isEmpty())
            {
                tileArray.at(j * ROWS + i)->move(Direction::DOWN);
                tileArray.at(j * ROWS + i)->setIsMoving(true);
            }
        }
    }
}

void HelloWorld::moveDown()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = ROWS - 1;j >= 0; j--)
        {
            if(tileArray.at(j * ROWS + i)->isEmpty())
            {
                for(int k = j-1; k >= 0; k--)
                {
                    if(!tileArray.at(k * ROWS + i)->isEmpty())
                    {
                        tileArray.at(j * ROWS + i)->setNumber(tileArray.at(k * ROWS + i)->getNumber());
                        tileArray.at(k * ROWS + i)->clear();
                        break;
                    }
                }
            }
        }
    }
}

void HelloWorld::sumLeft()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < ROWS - 1; j++)
        {
            if(!tileArray.at(i * ROWS + j)->isEmpty() && tileArray.at(i * ROWS + j)->equals(tileArray.at(i * ROWS + j + 1)))
            {
                tileArray.at(i * ROWS + j)->merge(tileArray.at(i * ROWS + j + 1));
                tileArray.at(i * ROWS + j + 1)->clear();
                score += tileArray.at(i * ROWS + j)->getNumber();
                undoScore += tileArray.at(i * ROWS + j)->getNumber();
                updateHighScore();
            }
        }
    }
}

void HelloWorld::sumRight()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j= ROWS - 1;j > 0; j--)
        {
            if(!tileArray.at(i * ROWS + j)->isEmpty() && tileArray.at(i * ROWS + j)->equals(tileArray.at(i * ROWS + j - 1)))
            {
                tileArray.at(i * ROWS + j)->merge(tileArray.at(i * ROWS + j - 1));
                tileArray.at(i * ROWS + j - 1)->clear();
                score += tileArray.at(i * ROWS + j)->getNumber();
                undoScore += tileArray.at(i * ROWS + j)->getNumber();
                updateHighScore();
            }
        }
    }
}

void HelloWorld::sumUp()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < ROWS - 1; j++)
        {
            if(!tileArray.at(j * ROWS + i)->isEmpty() && tileArray.at(j * ROWS + i)->equals(tileArray.at((j+1) * ROWS + i)))
            {
                tileArray.at(j * ROWS + i)->merge(tileArray.at((j + 1) * ROWS + i));
                tileArray.at((j + 1) * ROWS + i)->clear();
                score += tileArray.at(j * ROWS + i)->getNumber();
                undoScore += tileArray.at(j * ROWS + i)->getNumber();
                updateHighScore();
            }
        }
    }
}

void HelloWorld::sumDown()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = ROWS - 1; j > 0; j--)
        {
            if(!tileArray.at(j * ROWS + i)->isEmpty() && tileArray.at(j * ROWS + i)->equals(tileArray.at((j-1) * ROWS + i)))
            {
                tileArray.at(j * ROWS + i)->merge(tileArray.at((j - 1) * ROWS + i));
                tileArray.at((j - 1) * ROWS + i)->clear();
                score += tileArray.at(j * ROWS + i)->getNumber();
                undoScore += tileArray.at(j * ROWS + i)->getNumber();
                updateHighScore();
            }
        }
    }
}

void HelloWorld::updateHighScore()
{
    if (score > bestScore) {
        bestScore = score;
        def->setIntegerForKey("highscore", bestScore);
    }
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
    initialTouchPos[0] = touch->getLocation().x;
    initialTouchPos[1] = touch->getLocation().y;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    isTouchDown = true;
    
    //    CCLOG("onTouchBegan ID: %d, X: %f, Y: %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
    isTouchDown = false;
}

void HelloWorld::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}
