/********************************************************************
File: readme.txt
Author: s3435406
********************************************************************/

Notes:
------
SVG Notes:
Line Colors
Red = Path from start to finish (If their is one)
White = Pathways. Edges/Cell Adjacency.
Blue = Walls dividing the pathways up

Adjacency Edges are drawn along the "center" of the cell, rather than the upper left.
The results... it looks more like a maze :)

Prims Notes:
Runs slow :(. Didn't have enough time to refactor or optimize 
#uniproblems




Command Line Arguments:
Generation
--gr [<seed>] [<width>] [<height>]		: Generate using Recursive Division
--gp [<seed>] [<width>] [<height>]		: Generate using Prims Classic Algorithm
--gpm [<seed>] [<width>] [<height>]		: Generate using Prims Modified Algorithm

Traversal
--pw									: Wall follower
--pt									: Tremaux
--pm									: AStar Manhatten Distance
--pe									: AStar Euclidean Distance

IO
--lb <filename>							: Load Binary
--sb <filename>							: Save Binary
--sv <filename>							: Save SVG

Notes To Self:
--------------
A Better, Cleaner Method of traversal is needed across A*
The current just uses an extension of A* for the different heuristics.
There should be a better way.... somehow :)
	Policy Pattern should work, but some magic will be required so the 
entire A* algorithm isn't implemented in the .h or included via .hpp file

Requirements: (Includes A1 reqs, that still need to work!)
-------------
Design:
	UML									[x]

Report: (Seriously??)
	Report								[ ] :(

Command Line Arguments:
	- Parsing & Validation				[x]
	- Generate Recursive Division		[x]
	- Generate Prims Classic			[x]
	- Generate Prims Modified			[x]
	- Traverse Wall Follower			[x]
	- Traverse Tremaux					[x]
	- Traverse AStar					[x]
	- Load Binary						[x]
	- Save Binary						[x]
	- Save SVG							[x]

Loading:								[x]
	- Load from Binary File				[.]
		(Hasn't been tested since A1)
	- Validate file						[x]

Saving:
	- Save to Binary File				[.]
		(Hasn't been tested since A1)
	- Save as SVG Image					[x]	
		- Edge List Only				[x]
		- Actual Maze					[x]
		- Path Taken					[x]

Generation:
	- Recursive Division				[x]
	- Prims Classic						[x]
	- Prims Modified					[x]
	- Custom Set						[x]
		(yeah kinda i think)

Traversal
	- Wall Follower						[x]
	- Tremaux							[x]
	- AStar	[Manhatten]					[x]
	- AStar [Ecludian]					[x]
		(90% sure the A* pathfinding
		is working correctly)
	- Binary Heap						[.]
		(Using std::priority_queue
		with an "array like data structure"
		aka, a std::vector)

Timing
	- Generation						[x]
	- Pathfinding						[x]
	- Saving

General:
	- Modularisation					[x]
	- Containers						[.]
	- Comments!							[.]
		(oh gawd)
	- File Header with ID/Desc!			[x]
	- 80 Character Limit				[x]
		(I think so)

Linux/G++:
	- Makefile							[x]
		(Need a new Makefile)
	- C++14								[x]
	- No reference to platform headers	[x]
	

Timing Generate:	Seed = 0, Size = [2000, 2000]
	Prims Classic						[x]
	Prims Modified						[x]
	Recursive Division					[x]
	
Timing IO:				
	Prims Classic:
	Save Binary							[x]
	Save SVG							[x]
	
	Prims Modified:
	Save Binary							[x]
	Save SVG							[x]					

	Recursive Division:
	Save Binary							[x]
	Save SVG							[x]
	
		
Timing Traversal:						
	Export Binary Prims Classic			[x]
	Export Binary Prim Modified			[x]
	Export Binary Recursive Division	[x] 

	Prims Classic:
	Wall Hugger							[x]
	Tremaux								[x]
	A* Manhattan						[x]
	A* Euclidean						[x]

	Prims Modified:
	Wall Hugger							[x]
	Tremaux								[x]
	A* Manhattan						[x]
	A* Euclidean						[x]

	Recursive Division:
	Wall Hugger							[x]
	Tremaux								[x]
	A* Manhattan						[x]
	A* Euclidean						[x]

