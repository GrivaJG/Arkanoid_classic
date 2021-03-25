

#include "Config.h" 
#include "Menu.h"
#include "Levels.h"
#include "Event.h"

int main()
{
    RenderWindow window(VideoMode(1100, 600), "Arkanoid");
    window.setVerticalSyncEnabled(0);

    Image image;
    image.loadFromFile(IMGPATH);

    Music music;
    music.openFromFile(MUSIC_BASE);
    music.setLoop(true);
    music.setVolume(30);
    music.play();

    
    Menu::GetInstance();
    
    Levels lvs(image);

    while(window.isOpen())
        lvs.StartGame(window);
        
    
    return 0;
}


