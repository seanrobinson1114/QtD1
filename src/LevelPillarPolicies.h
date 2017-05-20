//---------------------------------------------------------------------------//
//!
//! \file   LevelPillarPolicies.h
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillar policy classes
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_PILLAR_POLICIES_H
#define LEVEL_PILLAR_POLICIES_H

namespace QtD1{

//! The passable pillar policy (characters can pass through the pillar)
struct PassablePillarPolicy
{
  // Check if the pillars bounding box is colliding the bounding box of interest
  static inline bool isColliding( const SDL_Rect& pillar_bounding_box,
                                  const SDL_Rect& bounding_box )
  {
    return false;
  }

  // Check if the pillar is hiding the bounding box of interest
  bool isHiding( const SDL_Rect& pillar_bounding_box,
                 const SDL_Rect& bounding_box )
  {
    return false;
  }

  // Check if the pillar is colliding with a projectile bounding box
  bool isProjectileColliding( const SDL_Rect& pillar_bounding_box,
                              const SDL_Rect& bounding_box )
  {
    return false;
  }

  // Intersect the pillar with a view port
  void intersectWithViewport( std::vector<SDL_Color>& viewport_image,
                              const SDL_Rect& viewport )
  {
    // TODO
  }

  // Render the part of the pillar that intersects the viewport
  void renderInViewport( const SDL_Rect& viewport,
                         SDL_Renderer* renderer )
  {
    // TODO
  }
};

//! The impassable pillar policy  (characters cannot pass through the pillar)
struct ImpassablePillarPolicy
{
  // Check if the pillars bounding box is colliding the bounding box of interest
  static inline bool isColliding( const SDL_Rect& pillar_bounding_box,
                                  const SDL_Rect& bounding_box )
  {
    // TODO: Implement collision detection
  }

  // Check if the pillar is hiding the bounding box of interest
  bool isHiding( const SDL_Rect& pillar_bounding_box,
                 const SDL_Rect& bounding_box )
  {
    return false;
  }

  // Check if the pillar is colliding with a projectile bounding box
  bool isProjectileColliding( const SDL_Rect& pillar_bounding_box,
                              const SDL_Rect& bounding_box )
  {
    if( this.isColliding( const SDL_Rect& pillar_bounding_box, const SDL_Rect& bounding_box) )
      return true;
    else
      return false;
  }

  // Intersect the pillar with a view port
  void intersectWithViewport( std::vector<SDL_Color>& viewport_image,
                              const SDL_Rect& viewport )
  {
    // TODO
  }

  // Render the part of the pillar that intersects the viewport
  void renderInViewport( const SDL_Rect& viewport,
                         SDL_Renderer* renderer )
  {
    // TODO
  }
};

//! The passable projectile policy (projectiles can pass through the pillar)
struct PassableProjectilePolicy
{
  // Check if the pillars bounding box is colliding the bounding box of interest
  static inline bool isColliding( const SDL_Rect& pillar_bounding_box,
                                  const SDL_Rect& bounding_box )
  {
    // TODO: implement collision detection
  }

  // Check if the pillar is hiding the bounding box of interest
  bool isHiding( const SDL_Rect& pillar_bounding_box,
                 const SDL_Rect& bounding_box )
  {
    return false;
  }

  // Check if the pillar is colliding with a projectile bounding box
  bool isProjectileColliding( const SDL_Rect& pillar_bounding_box,
                              const SDL_Rect& bounding_box )
  {
    return false;
  }

  // Intersect the pillar with a view port
  void intersectWithViewport( std::vector<SDL_Color>& viewport_image,
                              const SDL_Rect& viewport )
  {
    // TODO
  }

  // Render the part of the pillar that intersects the viewport
  void renderInViewport( const SDL_Rect& viewport,
                         SDL_Renderer* renderer )
  {
    // TODO
  }
};

//! The impassable projectile pillar policy (projectiles cannot pass through the pillar)
struct ImpassableProjectilePillarPolicy
{
  // Check if the pillars bounding box is colliding the bounding box of interest
  static inline bool isColliding( const SDL_Rect& pillar_bounding_box,
                                  const SDL_Rect& bounding_box )
  {
    // TODO: implement collision detection
  }

  // Check if the pillar is hiding the bounding box of interest
  bool isHiding( const SDL_Rect& pillar_bounding_box,
                 const SDL_Rect& bounding_box )
  {
    return false;
  }

  // Check if the pillar is colliding with a projectile bounding box
  bool isProjectileColliding( const SDL_Rect& pillar_bounding_box,
                              const SDL_Rect& bounding_box )
  {
    if( this.isColliding( const SDL_Rect& pillar_bounding_box, const SDL_Rect& bounding_box) )
      return true;
    else
      return false;
  }

  // Intersect the pillar with a view port
  void intersectWithViewport( std::vector<SDL_Color>& viewport_image,
                              const SDL_Rect& viewport )
  {
    // TODO
  }

  // Render the part of the pillar that intersects the viewport
  void renderInViewport( const SDL_Rect& viewport,
                         SDL_Renderer* renderer )
  {
    // TODO
  }
};

//! The transparent pillar policy (characters and projectiles can be seen through pillar)
struct TransparentPillarPolicy
{
  // Check if the pillars bounding box is colliding the boudning box of interest
  static inline bool isColliding( const SDL_Rect& pillar_bounding_box,
                                  const SDL_Rect& bounding_box )
  {
    // TODO: implement collision detection
  }

  // Check if the pillar is hiding the bounding box of interest
  bool isHiding( const SDL_Rect& pillar_bounding_box,
                 const SDL_Rect& bounding_box )
  {
    return false;
  }

  // Check if the pillar is colliding with a projectile bounding box
  bool isProjectileColliding( const SDL_Rect& pillar_bounding_box,
                              const SDL_Rect& bounding_box )
  {
    if( this.isColliding( const SDL_Rect& pillar_bounding_box, const SDL_Rect& bounding_box) )
      return true;
    else
      return false;
  }

  // Intersect the pillar with a view port
  void intersectWithViewport( std::vector<SDL_Color>& viewport_image,
                              const SDL_Rect& viewport )
  {
    // TODO
  }

  // Render the part of the pillar that intersects the viewport
  void renderInViewport( const SDL_Rect& viewport,
                         SDL_Renderer* renderer )
  {
    // TODO
  }
};

//! The nontransparent pillar policy (characters and projectiles can't be seen through pillar)
struct NontransparentPillarPolicy
{
  // Check if the pillars bounding box is colliding the bounding box of interest
  static inline bool isColliding( const SDL_Rect& pillar_bounding_box,
                                  const SDL_Rect& bounding_box )
  {
    // TODO: implement collision detection (will need to render character first)
  }

  // Check if the pillar is hiding the bounding box of interest
  bool isHiding( const SDL_Rect& pillar_bounding_box,
                 const SDL_Rect& bounding_box )
  {
    if( this.isColliding( const SDL_Rect& pillar_bounding_box, const SDL_Rect& bounding_box) )
      return true;
    else
      return false;
  }

  // Check if the pillar is colliding with a projectile bounding box
  bool isProjectileColliding( const SDL_Rect& pillar_bounding_box,
                              const SDL_Rect& bounding_box )
  {
    if( this.isColliding( const SDL_Rect& pillar_bounding_box, const SDL_Rect& bounding_box) )
      return true;
    else
      return false;
  }

  // Intersect the pillar with a view port
  void intersectWithViewport( std::vector<SDL_Color>& viewport_image,
                              const SDL_Rect& viewport )
  {
    // TODO
  }

  // Render the part of the pillar that intersects the viewport
  void renderInViewport( const SDL_Rect& viewport,
                         SDL_Renderer* renderer )
  {
    // TODO
  }
};

} // end QtD1 namespace

#endif // end LEVEL_PILLAR_POLICIES_H

//---------------------------------------------------------------------------//
// end LevelPillarPolicies.h
//---------------------------------------------------------------------------//
