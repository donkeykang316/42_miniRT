## Code Breakdown (WIP)

### Camera
- **aspect_ratio** Aspect ratio is the ratio of the width of an image to its height
  - `= 1`
- **image_width** The number of pixels horizontally across the image
  - `= 400`
- **image_height** The number of pixels vertically across the image
  - `= image_width / aspect_ratio`
- **samples_per_pixel** refers to the number of rays shot per pixel to gather color information (anti-aliasing)
  - `= 100`
- **vfov** stands for vertical field of view. It is a critical parameter used to define how much of the scene is visible through the camera vertically and is typically measured in degrees
  - `= 90`
- **lookfrom**defines the point in space from which the camera is viewing the scene
- **lookat**efines the direction in which the camera is looking
- **vup**stands for "view up vector." It is a vector that defines which direction is "up" for the camera
- **theta**refers to the angle in radians that describes the vfov
  - `= vfov * PI / 180`
- **h** determine the size of the viewport based on the field of view
  - `= tan(theta / 2)`
- **center** The central point of the viewport or the image plane in the 3D space
  - `= lookfrom`
- **focal_length** The distance between the camera's lens and the image plane (viewport)
  - `= sqrt(dot(lookfrom - lookat))`
- **viewport_height** The physical height of the camera's viewport in world units, not pixels
  - `= 2.0 * h * focal_length`
- **viewport_width** The physical width of the camera's viewport in world units
  - `= viewport_height * image_width / image_height`
- **w, u, v** Calculate the direction vecto that points from the camera's position (lookfrom) towards the point it is looking at (lookat)
  - `w = sqrt(dot(lookfrom - lookat, lookfrom - lookat))`
  - `u = sqrt(dot(corss(vup - w), corss(vup - w)))`
  - `v = corss(w, u)`
- **viewport_u** A unit vector representing the horizontal direction in the viewport
  - `= u * viewport_width`
- **viewport_v** A unit vector representing the vertical direction in the viewport
  - `= viewport_height * -v`
- **pixel_samples_scale** is the factor used to average the colors obtained from the multiple samples per pixel (anti-aliasing)
  - `= 1.0 / samples_per_pixel`
- **max_depth** refers to the maximum number of times a ray is allowed to bounce or reflect within the scene before the recursion stops.
  - `= 50`
- **viewport_upper_left** Coordinates of the top-left corner of a viewport in a 3D graphics application
  - `= center - (w * focal_length  + viewport_u / 2 + viewport_v / 2)`
- **pixel_delta_u** The horizontal step size between adjacent pixels on the viewport
  - `= viewport_u / image_width`
- **pixel_delta_v** The vertical step size between adjacent pixels on the viewport
  - `= viewport_v / image_height`
- **pixel00_loc** The position of the bottom-left corner pixel (often denoted as pixel (0,0)) on the viewport in world space coordinates
  - `= viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5`

### Ray
- **offset** refers to a small adjustment or displacement applied to a position, it is here to achieve anti-aliasing effects
  - `= vec3(random_nbr - 0.5, random_nbr - 0.5, 0)`
- **pixel_sample** calculate the exact sample position (i, j) on the image plane for the current pixel
  - `= camera.pixel00_loc + (camera.pixel_delta_u * (i + offset.x)) + (camera.pixel_delta_v * (j + offset.y))`
- **origin** The starting point from which the ray is cast
  - `= camera.center`
- **direction** specifies the direction in which the ray travels from its origin
  - `= pixel_sample - camera.center`

### Interval
- **interval** define the range of distances along the ray that should be considered for intersections with objects
- **min** sets the minimum distance along the ray to start checking for intersections, set to a small positive value to avoid self-intersection artifacts (visual errors) and skip any intersections that are too close to the origin of the ray
  - `= 0.001`
- **max** defines the maximum distance along the ray to check for intersections. Setting it to INFINITY means the ray will be checked for intersections with objects indefinitely far away from the ray's origi
  - `= INFINITY`

### Objects (ray intersection/hittble)
- **Types: sphere, quad, triangle, cylinder** 
- **sphere.center** origin of the sphere
- **sphere.radius** the distance from its center to any point on its surface
- **sphere.oc** The vector/offset from the sphere's center to the ray's origin
- **sphere.a** The coefficient of the quadratic term in the ray-sphere intersection equation
- **sphere.a** (or "b" in some other text books) determine the linear component in the quadratic equation for the intersection
- **sphere.c** a constant term derived from the squared length of the vector oc minus the squared radius of the sphere
- **sphere.discriminant** part of the quadratic formula used to determine the number and type of solutions (intersections). A negative discriminant indicates no real roots, meaning the ray does not intersect the sphere
- **sphere.root** determine if the intersection points of a ray with a sphere/ray interval 
- **quad.q** the starting corner
- **quad.u** representing the first side. Q+u gives one of the corners adjacent to Q
- **quad.v** representing the second side. Q+v gives the other corner adjacent to Q
- **quad.w** constant for a given quadrilateral
- **quad.denom** calculates the denominator for the ray-plane intersection equation (n * ray.direction), if the absolute value of this denominator is smaller than a very small constant (EPSILON 1e-8), it indicates that the ray is nearly parallel to the quad, indicating no valid intersection.
- **quadrat.t** determines the distance from the ray's origin to the intersection point on the plane
- **quadrat.intersection** ray intersection point
- **quadrat.planar_hitpt_vector** a reference point from starting corner to the intersection point
- **quadrat.alpha & beta** compute barycentric coordinates (alpha and beta) to determine if the intersection point is inside the quad
- **triangle** similiar to quad with different barycentric coordinates determination
- **cylinder.center** origin of the cylinder
- **cylinder.radius** radius of the cylinder
- **cylinder.axis** direction of the cylinder
- **cylinder.height** tube lenth of the cylinder
- **cylinder.oc** The vector/offset from the cylinder's center to the ray's origin
- **cylinder.cad** Projection of ray direction onto cylinder axis
- **cylinder.caoc** Projection of oc onto cylinder axis
- **cylinder.a & h & c** The coefficients of the quadratic term in the ray-sphere intersection equation
- **cylinder.discriminant** part of the quadratic formula used to determine the number and type of solutions (intersections). A negative discriminant indicates no real roots, meaning the ray does not intersect the sphere
- **cylinder.root1 & root2** determine  the two potential intersection points
- **cylinder.cap** Calculate the intersections on the cylinder's cap
- **cylinder.intersection** ray intersection point
- **cylinder.cy_ax** Calculate the projection of the intersection point onto the cylinder's axis

### hit record
- **p** Hit point, the exact location in 3D space where the ray intersects the object
- **normal** The surface normal at the hit point, which is used for lighting calculations
- **t** The parameter value in the ray equation that indicates the distance from the ray's origin to the hit point
- **front_face** A boolean indicating whether the ray hit the front face or back face of the object, important for correct lighting and shading

### material
- **albedo** refers to the intrinsic reflectivity or base color of a surface

### ray color
- **place holder**

### Background Color
- **sky**
    - `= color1 = vec_init(1.0, 1.0, 1.0)`
    - `= color2 = vec_init(0.5, 0.7, 1.0)`
- **dark for light**
    - `= color1 = vec_init(0.0, 0.0, 0.0)`
    - `= color2 = vec_init(0.20, 0.30, 0.50)`
