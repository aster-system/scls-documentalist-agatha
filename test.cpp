//******************
//
// SCLS Documentalist -> test.cpp
//
//******************
//
// SCLS Documentalist description
//
// SCLS Documentalist "Agatha" is a part of the Aster System SCLS project.
// This part is made to easily document C++ files.
// It is made for SCLS, but you can still use it in your project. However, it may be a little less adapted.
// This part is named after one of the most famous author, Agatha Christie.
//
//******************
//
// test.cpp description
//
// This file represents a test of the library.
// It also provide a way to document the library.
// Indeed, this documentation is made with SCLS Documentalist.
//
//******************
//
// License (GPLv3)
//
// This file is part of SCLS Documentalist.
//
// SCLS Documentalist is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// SCLS Documentalist is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with SCLS Documentalist. If not, see <https://www.gnu.org/licenses/>.
//

#include <iostream>
#include "scls_documentalist.h"

int main() {
    scls::Project* project = scls::cpp_scls_format_project();

    project->set_description("SCLS Documentalist \"Agatha\" is a part of the Aster System SCLS project.\nThis part is made to easily document C++ files.\nIt is made for SCLS, but you can still use it in your project. However, it may be a little less adapted.\nThis part is named after one of the most famous author, Agatha Christie.");
    project->set_name("SCLS Documentalist");

    scls::Text_Piece* core_cpp = project->new_file("src/scls_documentalist_core.cpp");
    core_cpp->set_variable("file_description", "This file contains the source code of \"headers/scls_documentalist_core.h\".");
    core_cpp->set_variable("file_name_extension", "scls_documentalist_core.cpp");
    core_cpp->set_variable("file_path", "src/scls_documentalist_core.cpp");

    scls::Text_Piece* core_h = project->new_file("headers/scls_documentalist_core.h");
    core_h->set_variable("file_description", "This file contains all the core of SCLS Documentalist.\nIt handles text pattern and pieces.");
    core_h->set_variable("file_name_extension", "scls_documentalist_core.h");
    core_h->set_variable("file_path", "headers/scls_documentalist_core.h");

    scls::Text_Piece* project_cpp = project->new_file("src/scls_documentalist_project.cpp");
    project_cpp->set_variable("file_description", "This file contains the source code of \"headers/scls_documentalist_project.h\".");
    project_cpp->set_variable("file_name_extension", "scls_documentalist_project.cpp");
    project_cpp->set_variable("file_path", "src/scls_documentalist_project.cpp");

    scls::Text_Piece* project_h = project->new_file("headers/scls_documentalist_project.h");
    project_h->set_variable("file_description", "This file contains all the needed things to handle an entire project with SCLS Documentalist.\nHowever, some of the core things are in others files included in this one.");
    project_h->set_variable("file_name_extension", "scls_documentalist_project.h");
    project_h->set_variable("file_path", "headers/scls_documentalist_project.h");

    scls::Text_Piece* base_h = project->new_file("scls_documentalist.h");
    base_h->pattern("include").set_iteration_number(base_h->id(), 5);
    base_h->set_variable("file_description", "This file includes each needed files in SCLS Documentalist.");
    base_h->set_variable("file_name_extension", "scls_documentalist.h");
    base_h->set_variable("file_path", "scls_documentalist.h");

    scls::Text_Piece* test_cpp = project->new_file("test.cpp");
    test_cpp->set_variable("file_description", "This file handles the testing of SCLS Documentalist.\nThe test is to recreate the project with SCLS Documentalist.");
    test_cpp->set_variable("file_name_extension", "test.cpp");
    test_cpp->set_variable("file_path", "test.cpp");

    project->save_formatted_as("test/");

    // project.save_all("scls_documentalist_test");

    return 0;
}
