#include "MusicAndSounds.h"


MusicAndSounds::MusicAndSounds()
{
    m_base_music.openFromFile(MUSIC_BASE);
    m_base_music.setVolume(10.f);
    m_base_music.setLoop(true);
    
    m_buffer_ball_bounce_of_block.loadFromFile(SOUND_BALL_BOUNCE_OFF_BLOCK);
    m_buffer_ball_bounce_of_border_map.loadFromFile(SOUND_BALL_BOUNCE_OFF_BORDER_MAP);
    m_buffer_ball_bounce_of_platform.loadFromFile(SOUND_BALL_BOUNCE_OFF_PLATFORM);
    m_buffer_ball_fall.loadFromFile(SOUND_BALL_FALL);
    m_buffer_platform_coll_bonus.loadFromFile(SOUND_PLATFORM_COLLECTS_BONUS);
    m_buffer_platform_fire.loadFromFile(SOUND_PLATFORM_FIRE);
    m_buffer_bullets_hit_block.loadFromFile(SOUND_BULLET_HIT_BLOCK);
    m_buffer_bullets_hit_border_map.loadFromFile(SOUND_BULLET_HIT_BORDER_MAP);
    m_buffer_ball_start.loadFromFile(SOUND_BALL_START);
    m_buffer_ball_catch.loadFromFile(SOUND_BALL_CATCH);
    m_buffer_change_platform.loadFromFile(SOUND_CHANGE_PLATFORM);

    m_ball_bounce_of_block.setBuffer(m_buffer_ball_bounce_of_block);
    m_ball_bounce_of_border_map.setBuffer(m_buffer_ball_bounce_of_border_map);
    m_ball_bounce_of_platform.setBuffer(m_buffer_ball_bounce_of_platform);
    m_ball_fall.setBuffer(m_buffer_ball_fall);
    m_platform_coll_bonus.setBuffer(m_buffer_platform_coll_bonus);
    m_platform_fire.setBuffer(m_buffer_platform_fire);
    m_bullets_hit_block.setBuffer(m_buffer_bullets_hit_block);
    m_bullets_hit_border_map.setBuffer(m_buffer_bullets_hit_border_map);
    m_ball_start.setBuffer(m_buffer_ball_start);
    m_ball_catch.setBuffer(m_buffer_ball_catch);
    m_change_platform.setBuffer(m_buffer_change_platform);    
}