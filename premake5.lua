-- premake5.lua
workspace "DOEngine"
   configurations { "Debug", "Release" }
   platforms { "Win32", "Linux" }

project "DOEngine"
   kind "WindowedApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   -- targetname("DOEngine")
   location("proj%{_ACTION}")

   includedirs{
	"src",
	"thirdparty/SDL/include",
	"thirdparty/SDL/build/include/"
	}

   files {
	"src/**.h",
	"src/**.cpp",
	"src/**.c",
	"*.lua"
	}

	-- removefiles {"src/old_state/**"}

   defines({"SQLITE_THREADSAFE=1"})

   --postbuildcommands{"{COPY} assets %{cfg.buildtarget.directory}"}

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"
	
	-- libdirs {
		-- "thirdparty/SDL/build/Debug"
	-- }

	links {
      -- "Mingw32",
      "SDL2Maind",
      "SDL2d",
      "wsock32"
     }

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
	
	--libdirs {
	--	"thirdparty/SDL/build/Release"
	--}

  filter  "platforms:Win32" 
    defines{"__WIN32__"}
    system "windows"
    architecture "x32"
 
     libdirs{
      -- "thirdparty/SDL2-2.0.10/lib/x86/",
	  "thirdparty/SDL/build/Debug"
     }

  filter  "platforms:Linux" 
    defines{"LINUX"}
    system "linux"
    links {
      "SDL2"
     }

project "SDL2"
   kind "Makefile"
   targetdir "thirdparty/SDL/build/Debug"
   targetname "SDL2d.dll"
   
   cleancommands {
	"{ECHO} Cleaning SDL2",
	"{RMDIR} thirdparty/SDL/build/"
   }
   
   filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		targetname "SDL2d.dll"
   
   buildcommands {
	"{ECHO} Building SDL2",
	"cmake thirdparty/SDL/ -A Win32 -B thirdparty/SDL/build/",
	"cmake --build thirdparty/SDL/build/"
   }
   
   rebuildcommands {
	"{ECHO} Re Building SDL2",
	"{RMDIR} thirdparty/SDL/build/",
	"cmake thirdparty/SDL/ -A Win32 -B thirdparty/SDL/build/",
	"cmake --build thirdparty/SDL/build/"
   }
   
   filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		targetname "SDL2d.dll"
   
   buildcommands {
	"{ECHO} Building SDL2",
	"cmake -DCMAKE_BUILD_TYPE=Release thirdparty/SDL/ -A Win32 -B thirdparty/SDL/build/",
	"cmake --build thirdparty/SDL/build/"
   }
   
   rebuildcommands {
	"{ECHO} Re Building SDL2",
	"{RMDIR} thirdparty/SDL/build/",
	"cmake -DCMAKE_BUILD_TYPE=Release thirdparty/SDL/ -A Win32 -B thirdparty/SDL/build/",
	"cmake --build thirdparty/SDL/build/"
   }
   
		