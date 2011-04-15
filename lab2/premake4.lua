solution "lab2"
   configurations {"Debug", "Release"}
 
   -- A project defines one build target
   project "lab2"
      kind "ConsoleApp"
      language "C++"
      platforms {"x32"}
      files {"src/*.h", "src/*.cpp", "libpng/*.c"}
      includedirs {".", "./pngpp"}

      configuration "linux"
         links {"glut"}

      configuration "windows"
         includedirs {"./glut"}
         defines {"_CRT_SECURE_NO_DEPRECATE"}
         buildoptions {"/wd4355"}
         linkoptions {"/NODEFAULTLIB:LIBCMT"}
         links {"freeglut_static"}
         libdirs {"./glut"}
      
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }
