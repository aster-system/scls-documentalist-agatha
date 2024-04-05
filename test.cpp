//******************
//
// test.cpp
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Documentalist "Agatha" part represents a easy way to document a SCLS part.
// It is named after one of the greatest author of all time, Agatha Christie.
//
// This file is the main file of the project.
//
//******************
//
// License (GPL V3.0) :
//
// Copyright (C) 2024 by Aster System, Inc. <https://aster-system.github.io/aster-system/>
// This file is part of SCLS.
// SCLS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// SCLS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with SCLS. If not, see <https://www.gnu.org/licenses/>.
//

#include <iostream>
#include "scls_documentalist.h"

using namespace std;

int main()
{
    scls::Writer writer = scls::Writer();
    writer.set_project_description("Mandelbrot maker is a little project made to create a Mandelbrot fractal.\nIt also allows to make Julia and Burning Ship fractals.");
    writer.set_project_name("Mandelbrot maker");

    scls::File_To_Document* main_cpp = writer.new_file("mandelbrot.cpp");
    main_cpp->set_description("This file contains the necessary things to draw the fractal.\nFor it, it uses the SCLS Image \"Michelangelo\" Image system.");

    writer.save_all("mandelbrot_maker");
    std::cout << writer.write("mandelbrot.cpp") << std::endl;

    return 0;
}
