#include <iostream>
#include "camera.hpp"

#include "../state/istate.hpp"

#include "../state/notshooting/notshooting.hpp"
#include "../state/notshooting/idle.hpp"
#include "../state/shooting/shooting.hpp"

using namespace std;

Camera::Camera()
{
    cout << "Construct Camera" << endl;
}

Camera::~Camera()
{
    cout << "Destruct Camera" << endl;
}

bool Camera::isMemAvail() const 
{
    return true;
}

bool Camera::isBatteryLow() const 
{
    return false;
}

string Camera::getCurState() const 
{
    return string("CurrentState -------->") + state_cast< const IState &>().getStateName();
}

void Camera::displayFocused(const EvInFocus & evInFocus)
{
    cout << "[Transition Action] : Camera focused on objects" << endl;
}

void Camera::allocMem(const EvShutterFull & evShutterFull)
{
    cout << "[Transition Action] : Memory allocated for storing the picture." << endl;
}

void Camera::powerSavingMode(const EvConfig & evConfig)
{
    cout << "[Transition Action] : Camera goes into Power Saving Mode" << endl;
}

int main()
{
    Camera camera;

    camera.initiate();
    cout << camera.getCurState() << endl;

    camera.process_event(EvConfig());  //模拟按Config键  
    cout<<camera.getCurState()<<endl;  
         
    camera.process_event(EvConfig());  //<span style="font-family: Arial, Helvetica, sans-serif;">模拟按Config键</span>  
    cout<<camera.getCurState()<<endl;  
              
    camera.process_event(EvShutterHalf());  //模拟半按快门  
    cout<<camera.getCurState()<<endl;  
                  
    cout<<"Press Shutter Full before focused"<<endl;  
    camera.process_event(EvShutterFull());  //在对焦完成之前，模拟全按快门  
    cout<<camera.getCurState()<<endl;  
                        
    camera.process_event(EvInFocus());      //模拟对焦完成事件  
    cout<<camera.getCurState()<<endl;  
                            
    camera.process_event(EvShutterRelease()); //模拟释放快门  
    cout<<camera.getCurState()<<endl;  
                                
    camera.process_event(EvStored());         //模拟存储完成  
    cout<<camera.getCurState()<<endl;  
                                    
    return 0;  
}
