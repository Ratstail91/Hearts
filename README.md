# Project Hearts version 1.0, 22nd June 2011

#### Introduction

This project is over 1 1/2 years old, so it doesn't reflect my current programming skills. Regardless, it's a pretty good demonstration of my development. From the KAGE engine, you can see what my thought processes at the time were, and you can probably guess that this evolved into my [Codebase](https://github.com/Ratstail91/Codebase). This has a sound system, and some aspects are different, but it's not a terrible start. I’ve also included all of the unused modules including NetworkManager, which aren’t used here, but are simply part of KAGE.

I'd say that my biggest problem when I was learning was my overreliance on inheritance. You can see this from Card being descended from Image, a common habit in my old code. Also, the presence of NamedManager, which was essentially a wrapper for std::map, and was used to create several different Manager classes isn’t something I’d do today.

Finally, my biggest mistake I believe, was that I made the KAGE engine closed source. This is a bad idea, since having code visible shows off what you can do. Whether it’s to a potential employer, or to someone critiquing your code, it’s always a good idea to show what you can do. That’s exactly why I’m uploading this old project. Maybe if I had someone to guide me on the engine’s design at the time, I’d have a radically different Codebase and coding style today.

I don’t consider this project complete, since it’s still missing a score display and a card passing button, but the scores are shown in the console window (stdout) and the F1 button compensates for a lack of graphical buttons. I’d like to remake this, using the existing game logic to rely on my current Codebase version. If I do, I’ll release the modified version under the zlib license.

#### Instructions

To select a card, click on it
To pass three cards at the start of the round, select them and press F1
To speed up the wait after a round, press F1

#### License

Built using Simple DirectMedia Layer (SDL) API. See http://www.libsdl.org for more information.

Built using Kayne's All-purpose Game Engine (KAGE). See KAGE documentation for more information (no longer available).

Programming by Kayne Ruse
Freeware Graphics
Freeware Audio

Hearts is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Hearts is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Hearts.  If not, see http://www.gnu.org/licenses/.

#### References

Blog: http://kr-studios.tumblr.com/  
Oldest known version: https://dl.dropbox.com/u/46669050/Hearts%20by%20Kayne%20Ruse.rar  
