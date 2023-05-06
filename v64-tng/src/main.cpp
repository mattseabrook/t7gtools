// main.cpp

/*
 * GROOVIE Tool
 *
 * This tool is designed for the extraction and processing of resource files
 * related to the 7th Guest game.
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

#include "rl.h"
#include "gjd.h"
#include "bitmap.h"

//
// Main Entrypoint
//
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " [-i|-x|-b] file" << std::endl;
        return 1;
    }

    std::string option = argv[1];
    std::string filename = argv[2];

    try
    {
        if (option == "-i")
        {
            // Print the list of VDX files in the RL-GJD resource files
            auto vdxFiles = parseRLFile(filename);

            std::cout << "Number of VDX Files: " << vdxFiles.size() << std::endl;

            for (const auto &vdxFile : vdxFiles)
            {
                std::cout << vdxFile.filename << " | " << vdxFile.offset << " | " << vdxFile.length << std::endl;
            }
        }
        else if (option == "-x")
        {
            std::cout << "Extracting..." << std::endl;
            std::string dirName = filename;
            std::replace(dirName.begin(), dirName.end(), '.', '_');
            std::filesystem::create_directory(dirName);

            parseGJDFile(filename);
        }
        else if (option == "-b")
        {
            std::cout << "Processing Bitmap..." << std::endl;

            // Extract the first 0x20 chunk type from the specified VDX file
            // VDXFile vdxFile = loadVDXFile(filename);
            // processType20Chunk(vdxFile);

            // Save the output image as a PNG file
            // savePNG("output_image.png", outputImageData, width, height);
        }
        else
        {
            std::cerr << "Invalid option: " << option << std::endl;
            return 1;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
