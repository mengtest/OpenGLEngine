//
//  label.h
//  OpenGLEngine
//
//  Created by 彭怀亮 on 5/15/19.
//  Copyright © 2019 彭怀亮. All rights reserved.
//

#ifndef label_h
#define label_h

#include <glm/glm.hpp>
#include <string>
#include "uibase.h"
#include "uievent.h"
#include "eventmgr.h"
#include "uimgr.h"
#include "ttfont.h"


class Label : public UIBase, public UIEvent
{
public:
    Label(){ std::cout<<"warn: called default constructor of label"<<std::endl; }
    
    Label(const glm::vec2 pos,const glm::vec3 color = glm::vec3(1), const float scale = 1.0f,
          const std::string text="", const int evtid = 0,const bool interact=true)
    {
        UIEvent::evtid = evtid;
        this->scales = scale;
        this->interact = interact;
        this->text = text;
        this->color = color;
        SetPos(pos.x, pos.y);
        if(interact)
        {
            EventMgr::getInstance()->RegistEvt(this);
        }
        UIManager::getInstance()->Regist(this);
        Draw();
    }
    
    virtual ~Label();
    
    virtual void Draw();
    
    bool IsHit(float x, float y);
    
    virtual void OnTriger();
    
    void setText(const std::string text);
    
    float getCenterX();
    
    std::string getText();
    
protected:
    std::string text;
    glm::vec3 color;
    float len;
    float scales;
};

#endif /* label_h */
