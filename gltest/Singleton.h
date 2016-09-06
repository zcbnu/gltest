//
//  Singleton.h
//  gltest
//
//  Created by 黄保应 on 16/3/18.
//  Copyright © 2016年 黄保应. All rights reserved.
//

#ifndef Singleton_h
#define Singleton_h

class Singleton
{
public:
    static Singleton* getInstance() {
        return new Singleton;
    }
    
    Singleton():m_pInstance(nullptr){}
private:
    Singleton* m_pInstance;
};
#endif /* Singleton_h */
