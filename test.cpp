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

#include "scls_documentalist.h"

// Create a simple hello world
void create_hello_world() {
    scls::Project* project = scls::cpp_scls_format_project();

    project->set_global_variable(SCLS_DOCUMENTALIST_PROJECT_DESCRIPTION_VARIABLE, "Hello World is a test project, fully made with the experiment SCLS library SCLS Documentalist \"Agatha\".");
    project->set_global_variable(SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE, "Hello World");

    scls::Text_Piece* core_cpp = project->new_file("main.cpp", "file_cpp");
    core_cpp->set_variable("file_description", "This file contains the main code of the project.");
    core_cpp->set_variable("file_name_extension", "main.cpp");
    core_cpp->set_variable("file_path", "main.cpp");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "Use the in/out C++ functions.");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "<iostream>");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_MACRO_CONTENT, "\"Hello world !\"");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_MACRO_DESCRIPTION, "Test said by the file.");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_MACRO_NAME, "text");

    project->save_formatted_as("test/");
}

// Create this project
void create_scls_documentalist() {
    scls::Project* project = scls::cpp_scls_format_project();

    project->set_description("SCLS Documentalist \"Agatha\" is a part of the Aster System SCLS project.\nThis part is made to easily document C++ files.\nIt is made for SCLS, but you can still use it in your project. However, it may be a little less adapted.\nThis part is named after one of the most famous author, Agatha Christie.");
    project->set_name("SCLS Documentalist");

    scls::Text_Piece* core_cpp = project->new_file("src/scls_documentalist_core.cpp", "file_cpp");
    core_cpp->set_variable("file_description", "This file contains the source code of \"headers/scls_documentalist_core.h\".");
    core_cpp->set_variable("file_name_extension", "scls_documentalist_core.cpp");
    core_cpp->set_variable("file_path", "src/scls_documentalist_core.cpp");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "Header of this source file.");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "\"../headers/scls_documentalist_core.h\"");

    scls::Text_Piece* core_h = project->new_file("headers/scls_documentalist_core.h", "file_h");
    core_h->set_variable(SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION, "SCLS_DOCUMENTALIST_CORE");
    core_h->set_variable("file_description", "This file contains all the core of SCLS Documentalist.\nIt handles text pattern and pieces.");
    core_h->set_variable("file_name_extension", "scls_documentalist_core.h");
    core_h->set_variable("file_path", "headers/scls_documentalist_core.h");
    core_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "Foundation part of SCLS.");
    core_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "<scls_foundation.h>");

    scls::Text_Piece* project_cpp = project->new_file("src/scls_documentalist_project.cpp", "file_cpp");
    project_cpp->set_variable("file_description", "This file contains the source code of \"headers/scls_documentalist_project.h\".");
    project_cpp->set_variable("file_name_extension", "scls_documentalist_project.cpp");
    project_cpp->set_variable("file_path", "src/scls_documentalist_project.cpp");
    project_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "Header of this source file.");
    project_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "\"../headers/scls_documentalist_project.h\"");

    scls::Text_Piece* project_h = project->new_file("headers/scls_documentalist_project.h", "file_h");
    project_h->set_variable(SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION, "SCLS_DOCUMENTALIST_PROJECT");
    project_h->set_variable("file_description", "This file contains all the needed things to handle an entire project with SCLS Documentalist.\nHowever, some of the core things are in others files included in this one.");
    project_h->set_variable("file_name_extension", "scls_documentalist_project.h");
    project_h->set_variable("file_path", "headers/scls_documentalist_project.h");
    project_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "Core of SCLS Documentalist.");
    project_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "\"scls_documentalist_core.h\"");

    scls::Text_Piece* base_h = project->new_file("scls_documentalist.h", "file_h");
    base_h->pattern("include")->set_iteration_number(base_h->id(), 2);
    base_h->set_variable(SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION, "SCLS_DOCUMENTALIST");
    base_h->set_variable("file_description", "This file includes each needed files in SCLS Documentalist.");
    base_h->set_variable("file_name_extension", "scls_documentalist.h");
    base_h->set_variable("file_path", "scls_documentalist.h");
    base_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "[0]", "\"headers/scls_documentalist_core.h\"");
    base_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "[0]", "File containing the core of the library.");
    base_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "[1]", "\"headers/scls_documentalist_project.h\"");
    base_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "[1]", "File allowing to use complex project.");

    scls::Text_Piece* test_cpp = project->new_file("test.cpp", "file_cpp");
    test_cpp->set_variable("file_description", "This file handles the testing of SCLS Documentalist.\nThe test is to recreate the project with SCLS Documentalist.");
    test_cpp->set_variable("file_name_extension", "test.cpp");
    test_cpp->set_variable("file_path", "test.cpp");
    test_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "SCLS Documentalist file which includes each needed files.");
    test_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "\"scls_documentalist.h\"");

    project->save_formatted_as("test/");
}

int main() {
    create_hello_world();
    create_scls_documentalist();

    return 0;
}
