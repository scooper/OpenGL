project "SOIL"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/image_DXT.c",
		"src/image_helper.c",
		"src/SOIL.c",
		"src/stb_image_aug.c",
		"src/image_DXT.h",
		"src/image_helper.h",
		"src/SOIL.h",
		"src/stb_image_aug.h",
		"src/stbi_DDS_aug.h",
		"src/stbi_DDS_aug_c.h"
    }

	filter "system:windows"
		systemversion "latest"

		defines {
			"WIN32",
			"_LIB"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

		defines {
			"_DEBUG"
		}

	filter "configurations:Release"
		runtime "Release"
        optimize "on"
