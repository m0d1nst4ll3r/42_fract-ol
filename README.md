# 42_fract-ol

(started 16/12/2021)

Todo-list:

1. Implement auto-incrementing iterations
2. Implement color smoothing with an option to turn off
3. Implement anti-aliasing with an option to turn off
4. Implement a way to time how long last frame took to render
5. Test several configurations to optimize rendering time... mults instead of adds in complex loops... less variables... and try to optimize code where possible
6. Implement multithreading for everything (map calculation including partial AND coloring)
Last, details... code readability, comments...

Cut content:

- Moving by holding RMB
Reason : I can call a function when RMB is pressed down and released and when the cursor moves while RMB is held, but how do I make a function get called when RMB is pressed down and wait for RMB releasing? Since idk how and it'll take too much time to figure out, this is cut.
- Drawing a rectangle by holding LMB
Reason : same as above plus the fact that there is no transparency in mlx so it'd be super hard to draw the outlines of a moving rectangle. Too much effort.
- Multiple windows
Reason : too hard to make at this point, should've structured my program around it from the start

# Resources:

https://harm-smits.github.io/42docs/libs/minilibx
https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set (complicated math for drawing mandelbrot fractals)
https://math.hws.edu/eck/js/mandelbrot/MB.html
https://en.wikipedia.org/wiki/Spatial_anti-aliasing
