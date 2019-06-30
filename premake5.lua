-- Clean Function --
newaction {
  trigger     = "clean",
  description = "clean the software",
    execute     = function ()
      print("clean the build...")
      os.rmdir("./build")
      os.rmdir("./bin")
      os.rmdir("./obj")
      os.rmdir("./.vs")
      print("done.")
  end
}

-- workspace --
workspace "AmxxNcrypto"
  location ("build/" .. _ACTION)
  configurations { "ReleaseDLL", "DebugDLL" }
  staticruntime "On"
  architecture "x86"
  cppdialect "C++14"
  
  characterset("MBCS") -- use multibyte character set in msvs

  -- flags & options --
  flags { "No64BitChecks", "MultiProcessorCompile" }
  defines "NO_MSVC8_AUTO_COMPAT"
  
  filter "configurations:DebugDLL"
    defines { "DEBUG", "_DEBUG" }
    symbols "On"

  filter "configurations:ReleaseDLL"
    defines { "NDEBUG" }
    optimize "Full"
    flags { "NoBufferSecurityCheck", "NoRuntimeChecks" }

  filter { "system:windows", "configurations:ReleaseDLL" }
    flags { "NoIncrementalLink", "LinkTimeOptimization" }
	
  filter { "system:windows" }
    defines { "_CRT_SECURE_NO_WARNINGS", "_WIN32_WINNT=0x0600", "WIN32" }
    systemversion "latest"
  
  filter "configurations:*"
    defines {
      "HAVE_STDINT_H" -- prevent C2371 for int32_t in amxmodx
    }

project "AmxxNcrypto"
  targetname  "ncrypto_amxx_i386"
  kind        "SharedLib"
  language    "C++"
  targetdir   "bin/%{cfg.buildcfg}"

  files { 
    "src/**.h",
    "src/**.cc",
    "src/sdk/**.cpp",
    "src/hash-library/**.cpp"
  }
  
  filter "system:windows"
    links { "rpcrt4" }

  filter "system:linux"
    links { "uuid" }
    toolset "gcc"
    linkgroups "On"
    linkoptions { "-static-libgcc -static-libstdc++" }

