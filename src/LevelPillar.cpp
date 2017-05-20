//---------------------------------------------------------------------------//
//!
//! \file   LevelPillar.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillar class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "LevelPillar.h"

namespace QtD1{

// Constructor
LevelPillar::LevelPillar(
            const std::vector<std::shared_ptr<JustInTimeImage> >& level_images,
            const std::vector<uint32_t>& level_image_indices,
            const int lower_left_x_pos_wrt_global,
            const int lower_left_y_pos_wrt_global )
  : d_height( 0 ),
    d_images(),
    d_lower_left_x_pos_wrt_global( lower_left_x_pos_wrt_global ),
    d_lower_left_y_pos_wrt_global( lower_left_y_pos_wrt_global )
{

}

// Get the pillar width
int LevelPillar::getWidth() const
{
  return s_width;
}

// Get the pillar height
int LevelPillar::getHeight() const
{
  return d_height;
}

// Check if the pillar is colliding with the bounding box
bool LevelPillar::isColliding( const SDL_Rect& bounding_box ) const
{

}

// Check if the pillar is colliding with a projectile bounding box
bool LevelPillar::isProjectileColliding( const SDL_Rect& bounding_box ) const
{

}

// Intersect the pillar with a view port
void LevelPillar::intersectWithViewport( std::vector<SDL_Color>& viewport_image,
                                         const SDL_Rect& viewport ) const
{

}

// Render the part of the pillar that intersects the viewport
virtual void renderInViewport( const SDL_Rect& viewport,
                               SDL_Renderer* renderer ) const
{
  
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelPillar.cpp
//---------------------------------------------------------------------------//
