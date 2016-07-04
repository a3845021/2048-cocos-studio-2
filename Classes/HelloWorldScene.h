#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Tile2048.h"
#include "Constants.h"
#include "ui/CocosGUI.h"
#include "CCNativeAlert.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    cocos2d::Size visibleSize;
    
    // touch events
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) override;
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event) override;
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;
    void onQuitGame(int tag, cocos2d::NativeAlert::ButtonType type);

    
    bool isTouchDown;
    
    float initialTouchPos[2];
    float currentTouchPos[2];
    
    void update(float dt) override;
    
protected:
    cocos2d::Sprite* mainGrid;
    cocos2d::ui::Text* scoreText;
    cocos2d::ui::Text* bestText;
    cocos2d::ui::Text* overText;
    cocos2d::ui::Button* btnNewgame;
    cocos2d::ui::Button* btnUndo;
    cocos2d::Vector<Tile2048*> tileArray;
    int undoArray[ROWS * ROWS];
    float tileWidth;
    int score;
    int undoScore;
    int bestScore;
    bool gameOver;
    cocos2d::UserDefault* def;
    bool animation;
    
    void onEnter() override;
    
    void setupTouchHandling();
    
    void setupGrid();
    
    void newgame(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void undo(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    
    void onSwipe(Direction direction);
    
    int generateRandomIndex(int min, int max);
    void moveLeft();
    void moveLeftAnimation();
    void doMoveLeft();
    void moveRight();
    void moveRightAnimation();
    void doMoveRight();
    void moveUp();
    void moveUpAnimation();
    void doMoveUp();
    void moveDown();
    void moveDownAnimation();
    void doMoveDown();
    void sumLeft();
    void sumRight();
    void sumUp();
    void sumDown();
    bool checkFull();
    void restart();
    void displayWin();
    void displayGameOver();
    int calculateMax();
    bool checkGameEnds();
    void generateNewTile();
    
    void showScore();
    void updateHighScore();
};

#endif // __HELLOWORLD_SCENE_H__
