// main.cpp

/*
 * GROOVIE 2023
 *
 * Game Engine Re-creation, including tooling designed for the extraction and
 * processing of resource files related to the 7th Guest game.
 *
 * Author: Matt Seabrook
 * Email: info@mattseabrook.net
 * Website: www.mattseabrook.net
 *
 * MIT License
 *
 * Copyright (c) 2023 Matt Seabrook
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <fstream>

#include "rl.h"
#include "gjd.h"
#include "vdx.h"
#include "bitmap.h"

/*
====================
    MAIN ENTRY POINT
====================
*/

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " [-i|-x|-b] file" << std::endl;
        return 1;
    }

    std::string option = argv[1];
    std::string filename = argv[2];

    if (option == "-i")
    {
        auto vdxFiles = parseRLFile(filename);

        for (const auto &vdxFile : vdxFiles)
        {
            std::cout << vdxFile.filename << " | " << vdxFile.offset << " | " << vdxFile.length << std::endl;
        }

        std::cout << "Number of VDX Files: " << vdxFiles.size() << std::endl;
    }
    else if (option == "-x")
    {
        if (argc < 4)
        {
            std::cerr << "Usage: " << argv[0] << " -x [gjd|vdx] file" << std::endl;
            return 1;
        }

        std::string extraction_type = argv[2];
        std::string rl_filename = argv[3];

        std::string dirName = rl_filename;
        std::replace(dirName.begin(), dirName.end(), '.', '_');
        std::filesystem::create_directory(dirName);

        if (extraction_type == "gjd")
        {
            std::cout << "Extracting GJD..." << std::endl;

            std::vector<VDXFile> VDXFiles = parseGJDFile(rl_filename);

            for (const auto &vdxFile : VDXFiles)
            {
                writeVDXFile(vdxFile, dirName);
            }
        }
        else if (extraction_type == "vdx")
        {
            std::cout << "Extracting VDX..." << std::endl;

            std::string vdx_filename = argv[4];

            std::vector<VDXFile> VDXFile = parseGJDFile(rl_filename, vdx_filename);

            writeVDXFile(VDXFile[0], dirName);
        }
        else
        {
            std::cerr << "Invalid extraction type: " << extraction_type << std::endl;
            return 1;
        }
    }
    else
    {
        std::cerr << "Invalid option: " << option << std::endl;
        return 1;
    }

    return 0;
}
