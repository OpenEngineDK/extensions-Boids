
# Create the extension library
ADD_LIBRARY(Extensions_Boids
  Animations/Boid.h
  Animations/Boid.cpp
  Animations/Flock.h
  Animations/Flock.cpp
)

TARGET_LINK_LIBRARIES(Extensions_Boids
  Extensions_PropertyTree
)