# Project Hearts version 1.0, 22nd June 2011

## Introduction

This project is over 1 1/2 years old, so it doesn't reflect my current programming skills. Regardless, it's a pretty good demonstration of my development. From the KAGE engine, you can see what my thought processes at the time were, and you can probably guess that this evolved into my [Codebase](https://github.com/Ratstail91/Codebase). This has a sound system, and some aspects are different, but it's not a terrible start. I’ve also included all of the unused modules including NetworkManager, which aren’t used here, but are simply part of KAGE.

I'd say that my biggest problem when I was learning was my overreliance on inheritance. You can see this from Card being descended from Image, a common habit in my old code. Also, the presence of NamedManager, which was essentially a wrapper for std::map, and was used to create several different Manager classes isn’t something I’d do today.

Finally, my biggest mistake I believe, was that I made the KAGE engine closed source. This is a bad idea, since having code visible shows off what you can do. Whether it’s to a potential employer, or to someone critiquing your code, it’s always a good idea to show what you can do. That’s exactly why I’m uploading this old project. Maybe if I had someone to guide me on the engine’s design at the time, I’d have a radically different Codebase and coding style today.

I don’t consider this project complete, since it’s still missing a score display and a card passing button, but the scores are shown in the console window (stdout) and the F1 button compensates for a lack of graphical buttons. I’d like to remake this, using the existing game logic to rely on my current Codebase version. If I do, I’ll release the modified version under the zlib license.

## Instructions

Drop the "rsc" folder into the same directory as the executable  
To select a card, click on it  
To pass three cards at the start of the round, select them and press F1  
To speed up the wait after a round, press F1  

## Copyright

Copyright (c) Kayne Ruse 2011, 2012, 2013

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source distribution.

## Contact information

ratstail91@yahoo.com.au  
http://kr-studios.tumblr.com/  
http://www.facebook.com/krgamestudios  
Oldest known version: https://dl.dropbox.com/u/46669050/Hearts%20by%20Kayne%20Ruse.rar  
