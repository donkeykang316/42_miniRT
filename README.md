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
- **viewport_upper_left**
= 
- **pixel00_loc** The position of the bottom-left corner pixel (often denoted as pixel (0,0)) on the viewport in world space coordinates
= (pixel_delta_u + pixel_delta_v) * 0.5
