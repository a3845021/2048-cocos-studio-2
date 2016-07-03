//
//  Constants.h
//  2048Clone
//
//  Created by huunc on 6/29/16.
//
//

#ifndef Constants_h
#define Constants_h

const int ROWS = 4;
const float SLIDE_ANIMATION_TIME = 0.167f;
const float DELAY_FUNCTION_TIME = 0.167f;

enum class Direction {
    LEFT,
    UP,
    RIGHT,
    DOWN
};

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}


#endif /* Constants_h */
