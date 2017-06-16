# Color Maps
* Rainbow
* Luminance Based: Hot, Cold, Gray Scale, Hue: You can choose color
* Isoluminant:
	* Good for shading
	* Very little detail
* Divergent 
	* Good for seeing the median.
* Zebra
	* Good for seeing differences in values.
	We reduce the number of colors to hide the gray values.
* We can do the same for the other color maps, for example the ```cold``` color map. Color Banding.
If we are interested in one specific range of values we can use clamping. This also works for other color * maps, for example ``Hot``.
* Dynamic vs. static range

# Glyphs

* Triangles: Equilateral
* Airplanes: Show direction
* Different Grid Size: airplanes	
* Scaling: Increase global scale
* Hedgehogs
	* Don't show direction.
	* Useful to show of jittering.

* Jittering
	* Freeze
	* Jitter factor 0
	* Jitter factor 1.0

# Gradient
* We visualize the gradient with glyphs, if show them on top of the scalar visualization we see that they point in the direction of the greatest change.

# Stream Lines
* 20 x 20 grid of seed points.
* Color maps can be changed independently.
* Time step
* Increase edge length, function of cell size.
* Minimum magnitude
* Add seed points manually.
* Clear the seed points
* 40 x 40 grid

# Slices
* Smoke slices
* Show that color map can be changed
* Increase the number of slices
* Increase number states per slice
* Change combination method
* Global alpha
* Rotate

# Stream Surface
* Enable smoke to draw the seed curve
* Show only lines
* Decrease resolution
* Enable surface