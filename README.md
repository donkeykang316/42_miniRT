## Mathmatical Breakdown (WIP)

### Camera
- **aspect_ratio** Aspect ratio is the ratio of the width of an image to its height
= 16.0 / 9.0
- **image_width** The number of pixels horizontally across the image
= 400
- **image_height** The number of pixels vertically across the image
= image_width / aspect_ratio
- **focal_length** The distance between the camera's lens and the image plane (viewport)
= 1.0
- **viewport_height** The physical height of the camera's viewport in world units, not pixels
= 2.0
- **viewport_width** The physical width of the camera's viewport in world units
= viewport_height * image_width / image_height
- **center** The central point of the viewport or the image plane in the 3D space
= vec3(0, 0, 0)
- **vec:**
= vec3(0, 0, focal_length)
- **viewport_u** A unit vector representing the horizontal direction in the viewport
= vec3(viewport_width, 0, 0)
- **viewport_v** A unit vector representing the vertical direction in the viewport
= vec3(0, -viewport_height, 0)
- **pixel_delta_u** The horizontal step size between adjacent pixels on the viewport
= viewport_u / image_width
- **pixel_delta_v** The vertical step size between adjacent pixels on the viewport
= viewport_v / image_height
- **viewport_upper_left** Coordinates of the top-left corner of a viewport in a 3D graphics application
= center - (vec + (viewport_u / 2 + viewport_v / 2))
- **pixel00_loc** The position of the bottom-left corner pixel (often denoted as pixel (0,0)) on the viewport in world space coordinates
= viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5

### world
- **world.sphere** Add sphere(s) to the "world"

### ray
- **origin** The starting point from which the ray is cast
= vec3(camera.center.x, camera.center.y, camera.center.z)
- **direction** A vector that specifies the direction in which the ray travels from its origin
= pixel_center - camera.center

### hit record
- **rec** 
= 
- **rec** 
= 
- **rec** 
= 

### ray color
- **interval.min** This represents the lower bound of an interval. It is used to denote the minimum valid value of a parameter, such as the parameter t in the ray equation that defines the position along the ray
= 0
- **interval.max** This represents the upper bound of an interval. It defines the maximum valid value for computations, ensuring that calculations do not exceed this bound
= INFINITY

### hit objects
- **rec** 
= 
- **hit_anything** 
= 
- **closest_so_far** 
= 
- **max** 
= 
- **max** 
= 

### render
- **pixel_center** The exact center point of a pixel in the image space or viewport. It is a specific coordinate used to cast a ray through the pixel for rendering.
= pixel00_loc + (pixel_delta_u * i + pixel_delta_v * j)
- **ray.origin**
= vec3(camera.center.x, camera.center.y, camera.center.z)
- **ray.direction** 
= pixel_center - camera.center
- **pixel_color** The final color assigned to a pixel after all calculations, including ray intersections, lighting, and shading, have been completed
= ray_color