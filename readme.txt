   _____                           ________                                   __                
  /     \ _____  ________ ____    /  _____/  ____   ____   ________________ _/  |_  ___________ 
 /  \ /  \\__  \ \___   // __ \  /   \  ____/ __ \ /    \_/ __ \_  __ \__  \\   __\/  _ \_  __ \
/    Y    \/ __ \_/    /\  ___/  \    \_\  \  ___/|   |  \  ___/|  | \// __ \|  | (  <_> )  | \/
\____|__  (____  /_____ \\___  >  \______  /\___  >___|  /\___  >__|  (____  /__|  \____/|__|   
        \/     \/      \/    \/          \/     \/     \/     \/           \/                   

/********************************************************************
File: readme.txt
Author: s3435406 : Chris Snell
********************************************************************/

SVG:
---
Line Colors
Red = Path from start to finish (If their is one)
White = Pathways. Edges/Cell Adjacency.
Blue = Walls dividing the pathways up

Adjacency Edges are drawn along the centre of a cell, rather than the upper left - looks nicer :)


Prims:
------
Runs a little on the slow side :(. Didn't have enough time to refactor or optimize .
#uniproblems


Command Line Arguments:
-----------------------
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

General Notes / Bugs / Etc.
--------------
A Better, Cleaner Method of traversal is needed across A*
The current just uses an extension of A* for the different heuristics.
There should be a better way.... somehow :)
	Policy Pattern should work, but some magic will be required so the 
entire A* algorithm isn't implemented in the .h or included via .hpp file

Wall Follower was implemented slightly wrong - it should have only pushed/popped junctions, and follow the path until the next junction.