# Color Maps

## Different Color Maps
* Rainbow
* Luminance Based
	* Hot
	* Cold
	* Gray Scale
	* Hue: You can choose color
* Isoluminant:
	* Good for shading
	* Very little detail
* Divergent 
	* Good for seeing the median.
* Zebra
	* Good for seeing differences in values.
	We reduce the number of colors to hide the gray values.

## Number of Colors
We can do the same for the other color maps, for example the ```cold``` color map.

## Clamping
If we are interested in one specific range of values we can use clamping. This also works for other color maps, for example ``Hot``.

## Dynamic / Static Range
If we turn clamping of and set the number of colors back to 256 and thaw the simulation we see that the range of the color map is continuously updated. This is useful for seeing the detail at every state, but not so useful for the evolution. Thus we can also update the static ranges, to see how the simulation changes as a function of time. Update static range again. 

# Glyphs

## Different glyphs
* Triangles
	* Equilateral
* Airplanes
 * Show direction

## Different Grid Size
	* Back to airplanes

## Scaling
	* 
	* Increase global scale

# Hedgehogs
	* Don't show direction.
	* Useful to show of jittering.

# Jittering
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
	* Add seedpoints manually.
	* Clear the seedpoints
	* 40 x 40 grid

# Slices
	* Smoke slices
	* Show that colormap can be changed
	* Increase the number of slices
	* Increase number states per slice
	* Change combination method
	* Global alpha
	* Rotate

# Stream Surface
	* Enable smoke to draw the seedcurve
	* Show only lines
	* Decrease resolution
	* Enable surface