# lua-cpp
My attempts at integrating LUA with C++

## Notes

- I took the x64 Lua Binaries from [here](https://sourceforge.net/projects/luabinaries/files/5.1.5/Windows%20Libraries/Dynamic/).
- I added a custom build step that copies the Lua DLL to the project's output directory. 

   In PropertySheet.props I defined the macro `$(LuaDir)`

        <?xml version="1.0" encoding="utf-8"?>
        <Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
            <ImportGroup Label="PropertySheets" />
            <PropertyGroup Label="UserMacros">
                <LuaDir>$(SolutionDir)..\lua-5.1.5\</LuaDir>
            </PropertyGroup>
            <PropertyGroup />
            <ItemDefinitionGroup />
            <ItemGroup>
                <BuildMacro Include="LuaDir">
                    <Value>$(LuaDir)</Value>
                </BuildMacro>
            </ItemGroup>
        </Project>

    In app1.vcxproj I added a `PostBuildEvent`

        <PostBuildEvent>
            <Command>xcopy /y $(LuaDir)x64\*.dll $(OutDir)</Command>
        </PostBuildEvent>`        