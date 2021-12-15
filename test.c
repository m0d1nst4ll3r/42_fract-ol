#include <mlx.h>
#include <stdio.h>

int	main()
{
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 2400, 1300, "test");
	for (int j = 0; j < 1000; j++)
	{
		for (int i = 0; i < 1000; i++)
			mlx_pixel_put(mlx_ptr, win_ptr, j + i, i, i);
	}
	mlx_loop(mlx_ptr);
}
