# lua-cpp
My attempts at integrating LUA with C++

## Notes

- I took the x64 Lua v5.1.5 Binaries for x64 from [here](https://sourceforge.net/projects/luabinaries/files/5.1.5/Windows%20Libraries/Dynamic/) and extracted its contents into folder `$(SolutionDir)\lua-5.1.5\x64`
- For LUA documention, see [here](https://www.lua.org/docs.html)
- I added a custom build step that copies the Lua DLL to the project's output directory. 

   In PropertySheet.props I defined the macro `$(LuaDir)`

        <?xml version="1.0" encoding="utf-8"?>
        <Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
            <ImportGroup Label="PropertySheets" />
            <PropertyGroup Label="UserMacros">
                <LuaDir>$(SolutionDir)..\lua-5.1.5\$(Platform)\</LuaDir>
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
            <Command>xcopy /y $(LuaDir)*.dll $(OutDir)</Command>
        </PostBuildEvent>`

    In the project configuration I added include directories:

        <AdditionalIncludeDirectories>$(LuaDir)include</AdditionalIncludeDirectories>

    And library directories:

        <AdditionalLibraryDirectories>$(LuaDir)</AdditionalLibraryDirectories>