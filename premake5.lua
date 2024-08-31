-- premake5.lua
workspace "DOEngine"
   configurations { "Debug", "Release" }
   platforms { "Win32", "Win64", "Linux" }
   -- location "proj_%{_ACTION}"

project "DOEngine"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   objdir "obj/%{cfg.buildcfg}"
   -- targetname("DOEngine")
   location("proj%{_ACTION}")

   includedirs{
	"src",
	"thirdparty/SDL/include",
	"thirdparty/SDL/build/include/",
	"thirdparty/SDL_ttf/"
	}

   files {
      "src/**.h*",
      "src/**.c*",
      "*.lua"
	}

   defines({"SQLITE_THREADSAFE=1"})

   --postbuildcommands{"{COPY} assets %{cfg.buildtarget.directory}"}

   libdirs {
		"thirdparty/SDL/build",
      "thirdparty/SDL_ttf/build",
      "thirdparty/SDL_ttf/build/external/freetype"
	}

   links {
      "SDL2",
      "SDL2_ttf",
      "SDL2lib",
      "SDL2_ttflib",
      "freetype"
     }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"

  filter  "platforms:Win32" 
    defines{"WIN32"}
    system "windows"
    architecture "x32"
 
     libdirs{
         "thirdparty/SDL2_ttf/lib/x86"
     }

  filter  "platforms:Linux" 
    defines{"LINUX"}
    system "linux"

project "SDL2lib"
   kind "Makefile"
   objdir()
   
   location("thirdparty/SDL/")
   includedirs{"./include"}
   targetname "SDL2"

   cleancommands {
	   "{RMDIR} %{prj.location}/build/"
   }
   
   filter "configurations:Debug"
		targetdir "%{prj.location}/build/Debug"
   
   buildcommands {
      "cmake %{prj.location} -B %{cfg.targetdir}",
	   "cmake --build %{cfg.targetdir}"
   }
   
   rebuildcommands {
	   "{RMDIR} %{prj.location}/build/",
	   "cmake %{prj.location} -B %{cfg.targetdir}",
	   "cmake --build %{cfg.targetdir}"
   }
   
   filter "configurations:Release"
		targetdir "thirdparty/SDL/build/Release"
   
   buildcommands {
	   "cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -B %{cfg.targetdir}",
	   "cmake --build %{cfg.targetdir} --config Release"
   }
   
   rebuildcommands {
	   "{RMDIR} %{prj.location}/build/",
	   "cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -B %{cfg.targetdir}",
	   "cmake --build %{cfg.targetdir} --config Release"
   }

project "SDL2_ttflib"
   kind "Makefile"
   objdir()

   location("thirdparty/SDL_ttf/")
   includedirs{"./"}
   targetname "SDL2_ttf"
   
   filter "configurations:Debug"
		targetdir "%{prj.location}/build/Debug"
   
   buildcommands {
      "cmake %{prj.location} -DSDL2TTF_VENDORED=ON -DBUILD_SHARED_LIBS=OFF -B %{cfg.targetdir}",
	   "cmake --build %{cfg.targetdir}"
   }
   
   rebuildcommands {
	   "{RMDIR} %{cfg.targetdir}",
	   "cmake %{prj.location} -DSDL2TTF_VENDORED=ON -DBUILD_SHARED_LIBS=OFF -B %{cfg.targetdir}",
	   "cmake --build %{cfg.targetdir}"
   }

   cleancommands {
	   "{RMDIR} %{cfg.targetdir}"
   }
   
   filter "configurations:Release"
		targetdir "%{prj.location}/build/Release"
   
   buildcommands {
	   "cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -DSDL2TTF_VENDORED=ON -DBUILD_SHARED_LIBS=OFF -B %{cfg.targetdir}",
	   "cmake --build %{cfg.targetdir} --config Release"
   }
   
   rebuildcommands {
	   "{RMDIR} %{cfg.targetdir}",
	   "cmake -DCMAKE_BUILD_TYPE=Release %{prj.location} -DSDL2TTF_VENDORED=ON -DBUILD_SHARED_LIBS=OFF -B %{cfg.targetdir}",
	   "cmake --build %{cfg.targetdir} --config Release"
   }

   cleancommands {
	   "{RMDIR} %{cfg.targetdir}"
   }
