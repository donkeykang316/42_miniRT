## Code Breakdown (WIP)

### Camera
- **aspect_ratio** Aspect ratio is the ratio of the width of an image to its height
  - `= 16.0 / 9.0`
- **image_width** The number of pixels horizontally across the image
  - `= 400`
- **image_height** The number of pixels vertically across the image
  - `= image_width / aspect_ratio`
- **focal_length** The distance between the camera's lens and the image plane (viewport)
  - `= 1.0`
- **viewport_height** The physical height of the camera's viewport in world units, not pixels
  - `= 2.0`
- **viewport_width** The physical width of the camera's viewport in world units
  - `= viewport_height * image_width / image_height`
- **center** The central point of the viewport or the image plane in the 3D space
  - `= vec3(0, 0, 0)`
- **vec:**
  - `= vec3(0, 0, focal_length)`
- **viewport_u** A unit vector representing the horizontal direction in the viewport
  - `= vec3(viewport_width, 0, 0)`
- **viewport_v** A unit vector representing the vertical direction in the viewport
  - `= vec3(0, -viewport_height, 0)`
- **pixel_delta_u** The horizontal step size between adjacent pixels on the viewport
  - `= viewport_u / image_width`
- **pixel_delta_v** The vertical step size between adjacent pixels on the viewport
  - `= viewport_v / image_height`
- **viewport_upper_left** Coordinates of the top-left corner of a viewport in a 3D graphics application
  - `= center - (vec + (viewport_u / 2 + viewport_v / 2))`
- **pixel00_loc** The position of the bottom-left corner pixel (often denoted as pixel (0,0)) on the viewport in world space coordinates
  - `= viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5`

### world
- **world.sphere** Add sphere(s) to the "world"

### hit record
- **p** Hit point, the exact location in 3D space where the ray intersects the object
- **normal** The surface normal at the hit point, which is used for lighting calculations
- **t** The parameter value in the ray equation that indicates the distance from the ray's origin to the hit point
- **front_face** A boolean indicating whether the ray hit the front face or back face of the object, important for correct lighting and shading

### hit sphere
- **center** The center point of the sphere
- **radius** The distance from the center to any point on the surface of the sphere
- **oc** The offset from the ray's origin to the sphere's center
  - `= sphere.center - ray.origin`
- **a** Dot product of the ray's direction vector with itself
  - `= dot(ray.direction, ray.direction)`
- **h** Half the coefficient of t in the quadratic equation derived from the sphere-ray intersection equation
  - `= dot(ray.direction, oc)`
- **c** It represents the constant term in the quadratic equation
  - `= dot(oc, oc) - sphere.radius * sphere.radius` 
- **discriminant** A value derived from the quadratic formula that indicates the nature of the roots
  - `= h*h - a*c`
- **root** is the square root of the discriminant, used to find the actual intersection points. It's used to find the two potential intersection points along the ray
  - `= (h - sqrt(discriminant)) / a`
  - `= (h + sqrt(discriminant)) / a`
- **rec.t**
  - `= root`
- **rec.p**
  - `= ray.origin + ray.direction * t`
- **rec.normal**
  - `= (rec.p - sphere.center) / sphere.radius`

### ray
- **offset** refers to a small adjustment or displacement applied to a position, often used to perturb sample points within a pixel to achieve anti-aliasing effects
  - `= vec3(random_double - 0.5, random_double - 0.5, 0)`
  - **pixel_sample** refers to a specific point or a set of points within a pixel where color calculations are performed. Multiple samples per pixel are often used in techniques like anti-aliasing to average the results and produce smoother images
  - `= camera.pixel00_loc + (camera.pixel_delta_u + (i + offset.x)) + (camera.pixel_delta_v + (j + offset.y))`
- **origin** The starting point from which the ray is cast
  - `= vec3(camera.center.x, camera.center.y, camera.center.z)`
- **direction** A vector that specifies the direction in which the ray travels from its origin
  - `= pixel_sample - camera.center`

### ray color
- **interval.min** This represents the lower bound of an interval. It is used to denote the minimum valid value of a parameter, such as the parameter t in the ray equation that defines the position along the ray
  - `= 0`
- **interval.max** This represents the upper bound of an interval. It defines the maximum valid value for computations, ensuring that calculations do not exceed this bound
  - `= INFINITY`
- **color1(1, 1, 1)** Represent a color(r,g,b) with all its components set to the maximum intensity (white) (o for no intensity)
- **if hit object (sphere)**
  - **ray_color** Color of the ray
    - `= (rec.normal + color1) * 0.5`
- **else**
  - **color2(0.5, 0.7, 1.0)** soft blue color for the sky
    - `= (rec.normal + color1) * 0.5`
  - **unit_direction** Normalized version of a direction vector, ensure that the vector only indicates direction without any magnitude, which is vital for calculations involving directions like lighting, reflection, and refraction
  - **a** Blending factor to mix two colors, such as the ground color and the sky color, creating a gradient effect that simulates a sky. This is often used for backgrounds where the ground is typically lighter and the sky is blue
    - `= 0.5 * (unit_direction.y +1.0)`
  - **ray_color**
    - `= color1 * (1.0 - a) + color2 * a`

### write color
- **place holder**

### render
- **pixel_center** The exact center point of a pixel in the image space or viewport. It is a specific coordinate used to cast a ray through the pixel for rendering.
  - `= pixel00_loc + (pixel_delta_u * i + pixel_delta_v * j)`
- **ray.origin**
  - `= vec3(camera.center.x, camera.center.y, camera.center.z)`
- **ray.direction** 
  - `= pixel_center - camera.center`
- **pixel_color** The final color assigned to a pixel after all calculations, including ray intersections, lighting, and shading, have been completed
  - `= ray_color`
