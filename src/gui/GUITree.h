//
// Created by rostard on 09.11.18.
//

#ifndef INC_2DPROJECT_GUITREE_H
#define INC_2DPROJECT_GUITREE_H


#include "GUIObject.h"

class GUITree {
public:
    void addObject(GUIObject* object);

    void renderClickable();
private:
    GUIObject root;
};


#endif //INC_2DPROJECT_GUITREE_H
