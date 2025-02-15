- kare olceklenerek duvar yapilacak (80 20 1 hocadaki)
- secilen modelin ustunde piramit olacak
- view port - diger kamerayi gosterecek
- save scene -> herseyi kaydet
- camera oldugu yerde cizgileri olan bir piramit, bakilan yere donecek

- check rotation
- check textures/shapes

## Control
- model selection
	- model id
	- shape type
- textures
	- texture name
	- repeat (x, y)
- transform
	- position
	- rotation
	- scale
- camera selection
	- camera id
- camera transform
	- cam position
	- cam rotation
- camera specs
	- fov
	- near
	- far
	- aspect

## Creation
- model create
	- shape
	- texture
	- repeat
- camera create
	- fov
	- near
	- far
	- width
	- height




## CHANGES

- added setscale

- fixed light texture shader
Fixed the lighting calculation in the vertex shader
Added proper ambient lighting factor
Added the light direction uniform to settings.json
