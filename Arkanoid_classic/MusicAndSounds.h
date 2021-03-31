
#ifndef _MUSICANDSOUNDS_H
#define _MUSICANDSOUNDS_H

#include "Config.h"

class MusicAndSounds
{
private:
    Music _baseMusic;

    SoundBuffer _bufferBallBounceOfPlatform;
    SoundBuffer _bufferBallBounceOfBorderMap;
    SoundBuffer _bufferBallBounceOfBlock;
    SoundBuffer _bufferBallFall;
    SoundBuffer _bufferPlatformCollBonus;
    SoundBuffer _bufferPlatformFire;
    SoundBuffer _bufferBulletsHitBlock;
    SoundBuffer _bufferBulletsHitBorderMap;
    SoundBuffer _bufferBallStart;
    SoundBuffer _bufferBallCatch;
    SoundBuffer _bufferChangePlatform;

    Sound _ballBounceOfPlatform;
    Sound _ballBounceOfBorderMap;
    Sound _ballBounceOfBlock;
    Sound _ballFall;
    Sound _platformCollBonus;
    Sound _platformFire;
    Sound _bulletsHitBlock;
    Sound _bulletsHitBorderMap;
    Sound _ballStart;
    Sound _ballCatch;
    Sound _changePlatform;
   

    MusicAndSounds();
    

public:
    MusicAndSounds(MusicAndSounds& otner) = delete;
    void operator=(const MusicAndSounds&) = delete;

    static MusicAndSounds& GetInstance() //статическая функция инициализатор
    {
        static MusicAndSounds musicAndSounds_;
        return musicAndSounds_;
    }

    void BallBounceOfPlatformPlay() { _ballBounceOfPlatform.play(); }
    void BallBounceOfBorderMapPlay() { _ballBounceOfBorderMap.play(); }
    void BallBounceOfBlockPlay() { _ballBounceOfBlock.play(); }
    void BallFallPlay() { _ballFall.play(); }
    void PlatformCollBonusPlay() { _platformCollBonus.play(); }
    void PlatformFirePlay() { _platformFire.play(); }
    void BulletsHitBlockPlay() { _bulletsHitBlock.play(); }
    void BulletsHitBorderMapPlay() { _bulletsHitBorderMap.play(); }
    void BallStartPlay() { _ballStart.play(); }
    void BallCatchPlay() { _ballCatch.play(); }
    void ChangePlatformPlay() { _changePlatform.play(); }

    void BaseMusicPlay() { _baseMusic.play(); }


};

#endif

