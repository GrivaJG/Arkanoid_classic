#include "MusicAndSounds.h"


MusicAndSounds::MusicAndSounds()
{
    _baseMusic.openFromFile(MUSIC_BASE);
    _baseMusic.setVolume(10.f);
    _baseMusic.setLoop(true);
    
    _bufferBallBounceOfBlock.loadFromFile(SOUND_BALL_BOUNCE_OFF_BLOCK);
    _bufferBallBounceOfBorderMap.loadFromFile(SOUND_BALL_BOUNCE_OFF_BORDER_MAP);
    _bufferBallBounceOfPlatform.loadFromFile(SOUND_BALL_BOUNCE_OFF_PLATFORM);
    _bufferBallFall.loadFromFile(SOUND_BALL_FALL);
    _bufferPlatformCollBonus.loadFromFile(SOUND_PLATFORM_COLLECTS_BONUS);
    _bufferPlatformFire.loadFromFile(SOUND_PLATFORM_FIRE);
    _bufferBulletsHitBlock.loadFromFile(SOUND_BULLET_HIT_BLOCK);
    _bufferBulletsHitBorderMap.loadFromFile(SOUND_BULLET_HIT_BORDER_MAP);
    _bufferBallStart.loadFromFile(SOUND_BALL_START);
    _bufferBallCatch.loadFromFile(SOUND_BALL_CATCH);
    _bufferChangePlatform.loadFromFile(SOUND_CHANGE_PLATFORM);

    _ballBounceOfBlock.setBuffer(_bufferBallBounceOfBlock);
    _ballBounceOfBorderMap.setBuffer(_bufferBallBounceOfBorderMap);
    _ballBounceOfPlatform.setBuffer(_bufferBallBounceOfPlatform);
    _ballFall.setBuffer(_bufferBallFall);
    _platformCollBonus.setBuffer(_bufferPlatformCollBonus);
    _platformFire.setBuffer(_bufferPlatformFire);
    _bulletsHitBlock.setBuffer(_bufferBulletsHitBlock);
    _bulletsHitBorderMap.setBuffer(_bufferBulletsHitBorderMap);
    _ballStart.setBuffer(_bufferBallStart);
    _ballCatch.setBuffer(_bufferBallCatch);
    _changePlatform.setBuffer(_bufferChangePlatform);
    
}