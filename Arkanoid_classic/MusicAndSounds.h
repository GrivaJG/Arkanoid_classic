
#ifndef _MUSICANDSOUNDS_H_
#define _MUSICANDSOUNDS_H_

#include "Config.h"

class MusicAndSounds
{
public:
    MusicAndSounds(MusicAndSounds& otner) = delete;
    void operator=(const MusicAndSounds&) = delete;

    static MusicAndSounds& GetInstance() //статическая функция инициализатор
    {
        static MusicAndSounds musicAndSounds_;
        return musicAndSounds_;
    }

    void BallBounceOfPlatformPlay() { m_ball_bounce_of_platform.play(); }
    void BallBounceOfBorderMapPlay() { m_ball_bounce_of_border_map.play(); }
    void BallBounceOfBlockPlay() { m_ball_bounce_of_block.play(); }
    void BallFallPlay() { m_ball_fall.play(); }
    void PlatformCollBonusPlay() { m_platform_coll_bonus.play(); }
    void PlatformFirePlay() { m_platform_fire.play(); }
    void BulletsHitBlockPlay() { m_bullets_hit_block.play(); }
    void BulletsHitBorderMapPlay() { m_bullets_hit_border_map.play(); }
    void BallStartPlay() { m_ball_start.play(); }
    void BallCatchPlay() { m_ball_catch.play(); }
    void ChangePlatformPlay() { m_change_platform.play(); }

    void BaseMusicPlay() { m_base_music.play(); }

private:
    Music m_base_music;

    SoundBuffer m_buffer_ball_bounce_of_platform;
    SoundBuffer m_buffer_ball_bounce_of_border_map;
    SoundBuffer m_buffer_ball_bounce_of_block;
    SoundBuffer m_buffer_ball_fall;
    SoundBuffer m_buffer_platform_coll_bonus;
    SoundBuffer m_buffer_platform_fire;
    SoundBuffer m_buffer_bullets_hit_block;
    SoundBuffer m_buffer_bullets_hit_border_map;
    SoundBuffer m_buffer_ball_start;
    SoundBuffer m_buffer_ball_catch;
    SoundBuffer m_buffer_change_platform;

    Sound m_ball_bounce_of_platform;
    Sound m_ball_bounce_of_border_map;
    Sound m_ball_bounce_of_block;
    Sound m_ball_fall;
    Sound m_platform_coll_bonus;
    Sound m_platform_fire;
    Sound m_bullets_hit_block;
    Sound m_bullets_hit_border_map;
    Sound m_ball_start;
    Sound m_ball_catch;
    Sound m_change_platform;
   
    MusicAndSounds();    
};
#endif

