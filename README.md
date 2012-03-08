IIDE
====


About
-----

This is an attempt to build an IDE quite unlike anything out there. While a lot of well developed IDEs exist, there is little variation between them at least when it comes down to the actual writing of software. This might be because the current methodology is optimal, but I am not quite convinced and as such I'll try to build a new type of IDE.


Main Idea
---------

The driving difference between what I have in mind and what exists is the representation of a source file as a monolithic block. This in my mind is sub-optimal representation of data and it adds unnecessary mental and menial overhead to the programmer.

For example, when adding a new method to a class, the programmer has to open the file which contains the class and then scroll through all of the previous code until a proper place to add the new code is reached. Opening the needed file or finding the opened tab for the file requires a search through either your directory listing or opened tabs. To add the new code you have to scroll through the old code. Both of these things are not what you really want to do, you just want to add a method to an existing class. So why not have an interface where you press a key to explore/search through classes (not files), select a class and press a key to tell the IDE you want to create a new method and then choose between which two previous method the code should be added and then just type to your heart's content? Given you still essentially do the same steps as before, but you do them quicker. No need to mess with opened tabs; no need to scroll through code needlessly. Even better, when adding code, you don't need to keep as much track of how your project is stored in the file which gives you the freedom to explore how the file is stored logically.

That's one, perhaps minor, example of how current IDE's can be innovated - or at least try to be innovated. Who knows, this might turn out to be a completely impracticable way to code, but we won't know unless it's tried.


Feature Wish-list
-----------------

These will be expounded on when I start implementing them. For now this is a rough outline of what I would like to have one day...

### Class/function centric editing
Concentrate on editing functions and classes without caring about the structure of the file.


### Class/function explorer
Be able to quickly see class/file data relations


### Class/function designer
Give prototypes of classes or functions and those get created for you


### Integrated documentation
Easy way to view documentation of classes or functions


### Integrated versioning and timeline
Not sure how doable this is but it would be great to be able to go back in time and see the changed to a class or a project through a smooth progression.


### Automatic callgraph, complexity analysis, and profiling
That's actually three mostly separate things with various "do-ability" levels but they have been accomplished to various extents before (idk about complexity analysis though).


Plan
----

As a complete newbie in this area I'll claim success if I accomplish the first feature...

I'll be using C++, Qt for development and will concentrate on making the IDE first for one of C, C++, or python.


