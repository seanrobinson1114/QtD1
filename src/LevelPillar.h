//---------------------------------------------------------------------------//
//!
//! \file   LevelPillar.h
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillar class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_PILLAR_H
#define LEVEL_PILLAR_H

// Std Lib Includes
#include <vector>
#include <memory>

// SDL Includes
#include <SDL.h>

// QtD1 Includes
#include "JustInTimeImage.h"

namespace QtD1{

//! The level pillar class
class LevelPillar
{

public:

  //! Constructor
  LevelPillar( const std::vector<std::shared_ptr<JustInTimeImage> >& level_images,
               const std::vector<uint32_t>& level_image_indices,
               const int lower_left_x_pos_wrt_global,
               const int lower_left_y_pos_wrt_global );

  //! Destructor
  virtual ~LevelPillar()
  { /* ... */ }

  //! Get the pillar width
  int getWidth() const;

  //! Get the pillar height
  int getHeight() const;

  //! Check if the pillar is colliding with the bounding box
  virtual bool isColliding( const SDL_Rect& bounding_box ) const = 0;

  //! Check if the pillar is hiding the bounding box
  virtual bool isHiding( const SDL_Rect& bounding_box ) const = 0;

  //! Check if the pillar is colliding with a projectile bounding box
  virtual bool isProjectileColliding( const SDL_Rect& bounding_box ) const = 0;

  //! Intersect the pillar with a view port
  virtual void intersectWithViewport( std::vector<SDL_Color>& viewport_image,
                                      const SDL_Rect& viewport ) const = 0;

  //! Render the part of the pillar that intersects the viewport
  virtual void renderInViewport( const SDL_Rect& viewport,
                                 SDL_Renderer* renderer ) const = 0;

private:

  // The width of the pillar
  static int s_width = 64;

  // The height of the pillar
  int d_height;
  
  // The just-in-time images that make up this pillar
  std::vector<std::shared_ptr<JustInTimeImage> > d_images;

  // The lower left corner of the pillar w.r.t. global coordinate system
  int d_lower_left_x_pos_wrt_global;
  int d_lower_left_y_pos_wrt_global;
};
  
} // end QtD1 namespace

#endif // end LEVEL_PILLAR_H

//---------------------------------------------------------------------------//
// end LevelPillar.h
//---------------------------------------------------------------------------//
