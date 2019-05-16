//
//  EventMgr.h
//  LearnGL
//
//  Created by 彭怀亮 on 5/15/19.
//  Copyright © 2019 彭怀亮. All rights reserved.
//

#ifndef EventMgr_h
#define EventMgr_h

#include "../common.h"
#include "uievent.h"


class EventMgr
{
public:
    
    static EventMgr* getInstance()
    {
        return &instance;
    }
    
    void RegistEvt(UIEvent* evt)
    {
        ui_events.push_back(evt);
        std::cout<<"RegistEvt: "<<ui_events.size()<<std::endl;
    }
    
    void RemoveEvt(UIEvent* evt)
    {
        for(vector<UIEvent*>::iterator iter=ui_events.begin(); iter!=ui_events.end();iter++)
        {
            if(*iter == evt)
            {
                ui_events.erase(iter);
                std::cout<<"remove: "<<ui_events.size()<<std::endl;
                break;
            }
        }
    }
    
    void Triger(float x, float y, int action)
    {
        size_t size = ui_events.size();
        for (size_t i=0; i<size; i++)
        {
            UIEvent* et = ui_events[i];
            if(action == GLFW_RELEASE && et->IsHit(x, y))
            {
                et->OnTriger();
                et->Dispacher();
            }
        }
    }
    
private:
    EventMgr() { /*std::cout<<"EventMgr created!"<<std::endl;*/ }
    ~EventMgr() { /*std::cout<<"EventMgr destroyed!"<<std::endl;*/ }
    EventMgr(const EventMgr &);
    EventMgr& operator=(const EventMgr &);
    static EventMgr instance;
    
    std::vector<UIEvent*> ui_events;
};


#endif /* EventMgr_h */
