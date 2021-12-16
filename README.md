# 42_fract-ol
Started 16/12/2021

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


#Resources:
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


#Explanation on Julia and Mandelbrot:
Take a complex number. Complex numbers are x + yi. x and y are variable, i is the square root of -1 (an imaginary number).

Square it. Add c, c being another complex number (x+yi). Square it and add c. Square it and add c. Do this infinitely.

There are only 2 outcomes. Either the number will approach a certain value, or it will approach infinity.

There are two variables here : the starting point, and c. Let c always be the same, and let us vary starting points. This is a Julia set.

Take every possible starting point in an area (the area is infinite on a mathematical graph, but finite if you impose a grid on it, such as pixels do). Operate the function on each one of them, some number of times. Some will approach infinity, some will not. Those that do are colored black, those that do not are colored white.

And you're done. You've got a visualisation of a Julia set.

>>>This<<< is how a Julia set works. There are infinite Julia sets since there are infinite complex numbers. Each Julia set will have some starting points approaching infinity, some not. Varying c gives you differents Julia sets. 0 0 gives you a simple sphere of radius 1. -1 0 gives you an interesting julia set.

Now, go back and instead of considering c to always be the same and varying the starting points, consider the starting point to always be the same (0, 0) and vary c. This time, take every possible c in an area. Operate the function on each one of them, keep the starting point at 0, 0, and once again, some will approach infinity, some won't. Color those that do black, those that don't white.

>>>This<<< is the Mandelbrot set. You've got a visualisation of it. The Mandelbrot set is like the mother of all Julia sets. Each point in the Mandelbrot set (each c) has its own Julia set (where the c is now constant and the starting points vary).

Now... consider that any point outside a circle of radius 2 of center 0, 0 (after adding c) will always tend towards infinity. This is a mathematical rule. This is how you decide whether something approaches infinity or not, since you lack infinite computation with which to actually test every point.

Also consider that some starting points will cross that line of no return faster than others. For example, 1.5 at iteration 1 with c = 0 becomes 2.25, it's gone in only 1 iteration. 1.1 will take 3 iterations. 1.01 will take 7. 1 never will.

If you decide to color stuff that's gone after 1 iteration in black, 2 in dark grey, 3 in grey, 4 in light grey, etc... and those that are never gone in, say, white, you've suddenly got a gradient, and can visualize your Mandelbrot/Julia set in more than just 2 colors. Substitute the colors with whatever and however many you want.

You can set the amount of iterations that's the limit. If n = 1, you'll have a simple sphere. n = 2, you'll start seeing the beginning of your fractal. n = 3, etc etc... at around n=7 you should already have something pretty pleasing visually. No need for heavy computation.


#Thoughts on how to do this:
This the first (really) complicated project of 42... it really doesn't seem easy at first glance.

Thinking about basic fractal shapes (ex: triangles composed of triangles composed of triangles... refer to the video above), it's relatively easy (with some basic math) to draw them on screen with mlx. The two challenges in this are getting the math & recursion right, and coding sub-functions (like drawing a line) which would be pre-made in other, simpler languages, with better libs. Note that even drawing a simple line is not as easy as it would seem.

Two thoughts about such basic fractals : how do you zoom in, and also, how do you increase the depth without having to wait for exponentially increasing amounts of time?

Before thinking about zooming let's think about moving around. Moving around is essentially just moving the pixels on-screen. We can first note that efficiency requires that we devise a way to only redraw pixels that need to be replaced, ex: no need to redraw white pixels over 99% of the screen when they haven't moved. Then, we can note that moving pixels out of the screen, we need to remember they're still there somewhere. So, if we were following the basic video linked above, we note that we have to do it differently as soon as we want to move pixels around for directional keys or zooming in.

One way of solving our problem is simply remembering where the pixels are. There are two obvious ways of doing this... we can remember the position of each pixel (won't work for zooming in and out, but will work for moving around), or we can simply remember the geometric points, and redraw the lines between them. Note that remembering the geometric points isn't simple either. Due to inevitable rounding of values, points might get translated differently after two opposite operations (zoom +100%, zoom -100%).

A problem arises when considering these solutions for fractals... fractals are technically infinite, and should in practice at least go pretty far when zooming in. Now the problem is that if we have to remember every point, including those off screen, and calculate their fractal offsprings (which will of course be necessary for our graphical representation, even if the starting fractal points are off-screen), we'll very quickly be locked into infinite calculations, if we don't run out of memory before that. So, we'd need a way to remember points outside the screen without using up too much memory and we'd need a way not to do useless off-screen calculations.

Not only that, but we have to limit depth to what'll make a visible difference in our drawings, so we don't make useless calculations, but still calculate more depth as we zoom in. To do this, we'd need to have a depth limit, and increase that depth as we zoom in. Or, we could keep the same depth, but start the calculations from the shapes that are visible on screen (and more... since off-screen shapes can have offspring which are visible on-screen...).

... We start to get an idea of just how complicated this is getting. Almost like we have fractal problems. Literally problems generating problems infinitely. But the real problem is that we're using a very basic & naive approach which can get simplified by tons if only we dive into the complicated maths of fractals. Unfortunately, I've got no idea how to even approach the non-naive solution described in the wikipedia article, or what it's even about.

Given the complexity of this project, it's clear we have to proceed slowly, step by step, so we can fully understand what we're doing instead of blindly following wikipedia articles. So... todo-list.


#Todo list:
- Understand how to use mlx by following the guide
	- Get the basics of manipulating images, writing pixels to them, and everything
	- Create basic functions, for example to draw lines or shapes, to make sure the basics are understood and dive into a bit of maths and graphical problems
	- Manipulate events to, for example, exit the program
- With the help of the functions created above, do the same as the basic fractal vids
	- This is the naive approach but whatever, let's at least try it, if we can't do the naive approach we'll never understand anything about the non-naive one
- Make a first attempt at being able to move around the image using events
- Make a first attempt at zooming in, without adding more depth or anything
- At this point, either try to see if I get any ideas about how to solve the depth problem for these basic shapes, or...
- Read more material about escape time algorithms (which is the non-naive approach) and try to make it work, without zooming or anything
- If I get that far I'll have more ideas about where to go next
