# 42_fract-ol
Started 16/12/2021

- I was going for fluid motion but fluid motion is impossible.
	- So, since it's all about static and slow zooming, zooming should be as good as possible.
	- Zooming with mousewheel doesn't make much sense if the user is trying to get a specific shot.
	- It's either too fast and the user will be frustrated or too slow and the computer will spend forever on each frame.
	- The best way is to allow the use to draw an area by holding LMB and dragging the mouse.
- Colors need to be improved badly.
	- For this I can use palettes of differing sizes (50, 100, 250, 500, 1000, 2500, 5000) with differing colors.
	- Palettes of differing sizes means you've got the same colors, but spread out further.
	- Then, 1 iteration before escape is palette[0], 2 is palette[1], 50 is palette[49], 51 is back to palette[0], etc...
- There's a problem with rendering. There needs to be some kind of anti-aliasing option
- Program can probably be way more optimized
- Beyond some point, even long doubles aren't big enough and the image starts being badly pixelated ... it's pretty much the point at which https://math.hws.edu/eck/js/mandelbrot/MB.html starts having to take way longer "high precision, 22 digits". There needs to be a solution for that.
- Need Julia sets

# Project goals:
- Program opens a window where the mandelbrot set or a julia set is drawn
- Arrow keys can be used to move around fluidly
- Lmb/Rmb (or keys) can be used to zoom in or out centered on mouse position
- When launching the program, parameters can be used as such:
	- ./fractol set [x y] [-window] [-theme] [-depth]
	- set should either be mandelbrot or julia
	- set can be followed by x and y if it is julia, julia will default to -1 0 if x and y are absent
	- window should be followed by x and y, defaults to 1800 1200 if absent, can't be less than 100 100
	- theme should be followed by one of several options such as "classic" "rainbow" "drugs" which will change the colors preset (and even make the colors change in real time). Defaults to classic.
	- depth is the max amount of iterations. Defaults to something that's not too intensive on the cpu but pleasant visually.
- Bad params will cause a usage description
- That's about it, but there could be bonuses such as
	- Other fractal sets than mandelbrot and julia (which? are they any other?)
	- An interactive menu inside the window, with, for example
		- help menu (H key)
		- colors menu (C key) to change on the fly
		- colors menu could also let the user customize colors to their liking, by choosing 8 (or more? less?) different colors as a palette that goes from iterations 1 to max
		- an additional option to enable or disable color banding
		- an option to change depth inside the program
		- interactive with mouse support
	- Really smooth movement
	- Really optimized code so the program runs as fast as possible


# Resources:
- Understand how to use mlx
	- https://elearning.intra.42.fr/notions/minilibx/subnotions/mlx-introduction/videos/introduction-to-minilibx
	- https://elearning.intra.42.fr/notions/minilibx/subnotions/mlx-events/videos/minilibx-events
	- https://elearning.intra.42.fr/notions/fdf/subnotions/introduction-to-fdf/videos/introduction-to-fdf
	- https://harm-smits.github.io/42docs/libs/minilibx
- Understand how fractals work
	- https://youtu.be/FFftmWSzgmk
	- https://youtu.be/NGMRB4O922I
	- https://youtu.be/oCkQ7WK7vuY
- Understand how to code fractals
	- https://www.youtube.com/watch?v=bIfNwgUVjV8 (very basic fractal shapes)
	- https://www.youtube.com/watch?v=8JmoI4q7fTg (fractal trees, still pretty basic)
	- https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set (complicated math for drawing mandelbrot fractals)
- Online fractal program
	- https://math.hws.edu/eck/js/mandelbrot/MB.html
- Anti-aliasing with fractal examples
	- https://en.wikipedia.org/wiki/Spatial_anti-aliasing


# Explanation on Julia and Mandelbrot:
Take a complex number. Complex numbers are x + yi. x and y are variable, i is the square root of -1 (an imaginary number).

Square it. Add c, c being another complex number (x+yi). Square it and add c. Square it and add c. Do this infinitely.

There are only 2 outcomes. Either the number will approach a certain value, or it will approach infinity.

There are two variables here : the starting point, and c. Let c always be the same, and let us vary starting points. This is a Julia set.

Take every possible starting point in an area (the area is infinite on a mathematical graph, but finite if you impose a grid on it, such as pixels do). Operate the function on each one of them, some number of times. Some will approach infinity, some will not. Those that do are colored black, those that do not are colored white.

And you're done. You've got a visualisation of a Julia set.

\>\>\>This<<< is how a Julia set works. There are infinite Julia sets since there are infinite complex numbers. Each Julia set will have some starting points approaching infinity, some not. Varying c gives you differents Julia sets. 0 0 gives you a simple sphere of radius 1. -1 0 gives you an interesting julia set.

Now, go back and instead of considering c to always be the same and varying the starting points, consider the starting point to always be the same (0, 0) and vary c. This time, take every possible c in an area. Operate the function on each one of them, keep the starting point at 0, 0, and once again, some will approach infinity, some won't. Color those that do black, those that don't white.

\>\>\>This<<< is the Mandelbrot set. You've got a visualisation of it. The Mandelbrot set is like the mother of all Julia sets. Each point in the Mandelbrot set (each c) has its own Julia set (where the c is now constant and the starting points vary).

Now... consider that any point outside a circle of radius 2 of center 0, 0 (after adding c) will always tend towards infinity. This is a mathematical rule. This is how you decide whether something approaches infinity or not, since you lack infinite computation with which to actually test every point.

Also consider that some starting points will cross that line of no return faster than others. For example, 1.5 at iteration 1 with c = 0 becomes 2.25, it's gone in only 1 iteration. 1.1 will take 3 iterations. 1.01 will take 7. 1 never will.

If you decide to color stuff that's gone after 1 iteration in black, 2 in dark grey, 3 in grey, 4 in light grey, etc... and those that are never gone in, say, white, you've suddenly got a gradient, and can visualize your Mandelbrot/Julia set in more than just 2 colors. Substitute the colors with whatever and however many you want.

You can set the amount of iterations that's the limit. If n = 1, you'll have a simple sphere. n = 2, you'll start seeing the beginning of your fractal. n = 3, etc etc... at around n=7 you should already have something pretty pleasing visually. No need for heavy computation.


# Zooming and moving
Your window is an area inside the Mandelbrot set's plane. Each pixel represents a complex number.

Assuming you start your calculations from the top left of your screen, the very first pixel's complex number can be considered to be your position in the set. Moving around is only a matter of changing that first pixel's complex number, or its position.

Using this method, you can draw the initial Mandelbrot shape by choosing a starting point not too far from the center of the plane (0,0). When moving pixel by pixel (to draw on your window), it's just a matter of adding a certain value to your starting point. Let us consider this value to be our step.

Choosing a smaller step will cause the visual to be more zoomed in, and vice versa. Now we know how we can zoom : just changing the step.

This step value will also be needed when moving around, because we have to account for zoom when changing our starting position. It's a simple matter of factoring step into our movement. We can decide one key-press moves by one pixel, for example, and so we'll have to change our starting position by... you got it, step. If we want to move by 2 pixels, we change our starting position by 2 * step. Etc.

So far, we're only zooming to the top-left of our screen. How can we zoom towards our mouse's position?

Imagine that we're zooming in based on the cursor position. What does that mean? The step still decreases the same amount, it's just that our top-left position will change. Imagine our cursor is top-left. The position will barely change. Imagine it's bottom-right. Now the position will change a great deal.

What's zooming based on the cursor, anyway? Zooming is making everything go away from the center of the zoom (in our case, the cursor). Making everything move backwards on a line that goes through the center and the thing we're moving. But our top-left position isn't a thing we're making go away, it's where our drawing starts on the plane. In fact, unlike the "objects", it should get closer to the center, since... well... we're zooming IN. The area should get smaller. And thus, the starting position of our area should get closer to the center of the zoom.

One thing we can notice when playing around with zooms from other programs (such as 42's holy graph for example) is that the position will only ever move towards the cursor. That's only logical based on what we figured out right above. It moves on a line drawn between the top-left of the screen and the cursor. It will move way more if the cursor is far away, too. In fact, it will move a certain percentage of the distance, on that line.

What does moving on a line mean mathematically, anyway? Thinking about it for a few minutes we can realize that our top-left x,y (xa,ya) and our cursor x,y (xb,yb) represent both extremities of the line. xb,yb is just xa,ya + ((xb,yb) - (xa,ya)) or in other words, our cursor's position is our top-left position plus the difference between our cursor and our top left. And any movement on that line will be top-left plus some fraction of the cursor's position.

If that fraction is 0, we've got our top-left position. If it is 1, we've got our cursor position. If it is anything between 0 and 1, it'll be on our line.

Ok so that's how we move our top-left position relative to the cursor. But how much do you move it? 1%? 99%? Well... it's going to depend on how much you want to zoom, and it's going to have to be relative to your step ratio (how much you multiply or divide your step). Moving the top-left position by 99% of the difference can make sense if you zoom really really hard. 1% can also make sense if you barely zoom at all. But what's the math formula that links them?

Imagine your cursor is bottom-right. If you move top-left by 50%, you should also divide step by 2. If you move top-left by 75%, you should divide step by 4. And so on. These two examples are enough to see the formula : if you divide step by x, divide 100 by x and subtract it to 100. That's how much you move your top-left on the top-left/cursor line.

This is it for the theory and mathematics of zooming and moving around. There are ways to optimize moving around, by avoiding calculations we've already done, but zooming in is much more complicated.
