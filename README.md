# 42_fract-ol

(started 16/12/2021)

Todo-list:

- Leaks!
	- Got still reachables, dunno from where, 6 (1647 allocs 1641 frees)
	- Got an invalid read of size 4 (int) in get_gradient_palette (create_palette < create_color < decode_colors < fractol_init < main)
	- Got a weird error I never had before, Syscall param writev points to uninitialised byte(s) - this might be mlx...
- Add mandel3, mandel4 and also maybe more (it rhymes) (zn+1 = zn³ + c etc)
- Implement anti-aliasing with an option to turn off

Cut content:

- Cleaning up code
Reason : lazy
- Test several configurations to optimize rendering time... mults instead of adds in complex loops... less variables... and try to optimize code where possible
Reason : no time and multithreading already more than made up for optimization problems
- Implement a way to time how long last frame took to render
Reason : not enough payoff, need to finish this quick
- Moving by holding RMB
Reason : I can call a function when RMB is pressed down and released and when the cursor moves while RMB is held, but how do I make a function get called when RMB is pressed down and wait for RMB releasing? Since idk how and it'll take too much time to figure out, this is cut.
- Drawing a rectangle by holding LMB
Reason : same as above plus the fact that there is no transparency in mlx so it'd be super hard to draw the outlines of a moving rectangle. Too much effort.
- Multiple windows
Reason : too hard to make at this point, should've structured my program around it from the start
- A way to save locations and load them up so when you find something cool you can get back to it quickly
Reason : came up with this already really late in the project and I just wanna be done with it, but this is actually pretty doable (have to write to a file and parse it though...)

# Resources:

https://harm-smits.github.io/42docs/libs/minilibx

https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set (complicated math for drawing mandelbrot fractals)

https://math.hws.edu/eck/js/mandelbrot/MB.html

https://en.wikipedia.org/wiki/Spatial_anti-aliasing
