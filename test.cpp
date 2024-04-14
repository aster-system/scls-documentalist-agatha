////////////////////////////
//
// SCLS Documentalist -> test.cpp
//
//******************
//
// SCLS Documentalist description
//
// SCLS Documentalist is a part of the SCLS library.
//
// SLCS is a set of C++ library, made to make C++ development easier.
// For more information, see https://aster-system.github.io/aster-system/projects/scls.html.
//
// The Documentalist part is a part of the library made to handle easily file documentation.
// For that, it uses the SCLS Format "Mary" C++ format.
// For more information, see https://aster-system.github.io/aster-system/scls/documentalist.html.
//
//******************
//
// test.cpp description
//
// This file handles the testing of SCLS Documentalist.
// The test is to recreate the project with SCLS Documentalist.
//
//******************
//
// License description (GPL V3.0)
//
// This file is part of SCLS Documentalist project.
//
// SCLS Documentalist is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// SCLS Documentalist is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with SCLS Documentalist. If not, see <https://www.gnu.org/licenses/>.
//
//******************
//
// This project uses the Aster System SCLS Format "Mary" code format, in the public domain.
// It is also formatted using the Aster System SCLS Documentalist "Agatha" library under the GPL V3.0 license.
// See https://aster-system.github.io/aster-system/projects/scls.html for more informations.
//
////////////////////////////


////////////////////////////////////////////////////////
//****************************************************//
////////////////////////////////////////////////////////


////////////////////////////
//
// Included files
//
////////////////////////////

// "scls_documentalist.h" -> SCLS Documentalist file which includes each needed files.
#include "scls_documentalist.h"


////////////////////////////////////////////////////////
//****************************************************//
////////////////////////////////////////////////////////


////////////////////////////
//
// Testing functions
//
////////////////////////////

// Test the project with a simple Hello World project.
void create_hello_world() {
    scls::Project* project = scls::cpp_scls_format_project();

    project->set_global_variable(SCLS_DOCUMENTALIST_PROJECT_DESCRIPTION_VARIABLE, "Hello World is a test project, fully made with the experiment SCLS library SCLS Documentalist \"Agatha\".");
    project->set_global_variable(SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE, "Hello World");

    scls::Text_Piece* core_cpp = project->new_file("main.cpp", "file_cpp");
    core_cpp->set_pattern_iterations_number("code_content[0]", 2);
    core_cpp->set_variable("file_description", "This file contains the main code of the project.");
    core_cpp->set_variable("file_name_extension", "main.cpp");
    core_cpp->set_variable("file_path", "main.cpp");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_CODE_PART_TITLE, "Print \"to_print\" in the C++ console.");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_CODE_PART, "void print(std::string to_print) {\n    std::cout << to_print << std::endl;\n}");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_CODE_PART_TITLE, "[0][1]", "Main function of the program");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_CODE_PART, "[0][1]", "int main() {\n    print(TEXT);\n}");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "Use the in/out C++ functions.");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "<iostream>");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_MACRO_CONTENT, "\"Hello world !\"");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_MACRO_DESCRIPTION, "Test said by the file.");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_MACRO_NAME, "TEXT");
    core_cpp->set_variable(SCLS_DOCUMENTALIST_TITLE, "Mains functions");

    project->save_formatted_as("test/");
}

// Test the project by remaking it.
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
    core_h->set_pattern_iterations_number("macro", 4);
    core_h->set_variable(SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION, "SCLS_DOCUMENTALIST_CORE");
    core_h->set_variable("file_description", "This file contains all the core of SCLS Documentalist.\nIt handles text pattern and pieces.");
    core_h->set_variable("file_name_extension", "scls_documentalist_core.h");
    core_h->set_variable("file_path", "headers/scls_documentalist_core.h");
    core_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "Foundation part of SCLS.");
    core_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "<scls_foundation.h>");
    // Core.h macros
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_CONTENT, "[0]", "std::string(\"=\")");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_DESCRIPTION, "[0]", "String used to cut an error in SCLS Documentalist.");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_NAME, "[0]", "SCLS_DOCUMENTALIST_ERROR_CUTTER");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_CONTENT, "[1]", "std::string(\"-_\\\"{<;>\")");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_DESCRIPTION, "[1]", "String used to recognize an undefined variable forced to be use.");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_NAME, "[1]", "SCLS_DOCUMENTALIST_FORCED_USER_DEFINED_VARIABLE_ERROR");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_CONTENT, "[2]", "std::string(\"-*>\")");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_DESCRIPTION, "[2]", "String used to recognize the end of a variable in SCLS Documentalist.");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_NAME, "[2]", "SCLS_DOCUMENTALIST_VARIABLE_END");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_CONTENT, "[3]", "std::string(\"<*-\")");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_DESCRIPTION, "[3]", "String used to recognize the start of a variable in SCLS Documentalist.");
    core_h->set_variable(SCLS_DOCUMENTALIST_MACRO_NAME, "[3]", "SCLS_DOCUMENTALIST_VARIABLE_START");

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
    base_h->set_pattern_iterations_number("include", 2);
    base_h->set_variable(SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION, "SCLS_DOCUMENTALIST");
    base_h->set_variable("file_description", "This file includes each needed files in SCLS Documentalist.");
    base_h->set_variable("file_name_extension", "scls_documentalist.h");
    base_h->set_variable("file_path", "scls_documentalist.h");
    base_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "[0]", "\"headers/scls_documentalist_core.h\"");
    base_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "[0]", "File containing the core of the library.");
    base_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "[1]", "\"headers/scls_documentalist_project.h\"");
    base_h->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "[1]", "File allowing to use complex project.");

    scls::Text_Piece* test_cpp = project->new_file("test.cpp", "file_cpp");
    test_cpp->set_pattern_iterations_number("code", 2);
    test_cpp->set_pattern_iterations_number("code_content[0]", 2);
    test_cpp->set_pattern_iterations_number("code_content[1]", 1);
    test_cpp->set_variable("file_description", "This file handles the testing of SCLS Documentalist.\nThe test is to recreate the project with SCLS Documentalist.");
    test_cpp->set_variable("file_name_extension", "test.cpp");
    test_cpp->set_variable("file_path", "test.cpp");
    test_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION, "[0]", "SCLS Documentalist file which includes each needed files.");
    test_cpp->set_variable(SCLS_DOCUMENTALIST_INCLUDE_PATH, "[0]", "\"scls_documentalist.h\"");

    std::string c = "\r\n";
    test_cpp->set_variable(SCLS_DOCUMENTALIST_CODE_PART, "[0][0]", scls::replace(scls::read_file("test/codes/p_0_0.txt"), c, "\n"));
    test_cpp->set_variable(SCLS_DOCUMENTALIST_CODE_PART, "[0][1]", scls::replace(scls::read_file("test/codes/p_0_1.txt"), c, "\n"));
    test_cpp->set_variable(SCLS_DOCUMENTALIST_CODE_PART_TITLE, "[0][0]", "Test the project with a simple Hello World project.");
    test_cpp->set_variable(SCLS_DOCUMENTALIST_CODE_PART_TITLE, "[0][1]", "Test the project by remaking it.");
    test_cpp->set_variable(SCLS_DOCUMENTALIST_CODE_PART, "[1][0]", scls::replace(scls::read_file("test/codes/p_1_0.txt"), c, "\n"));
    test_cpp->set_variable(SCLS_DOCUMENTALIST_CODE_PART_TITLE, "[1][0]", "Main function of the program.");
    test_cpp->set_variable(SCLS_DOCUMENTALIST_TITLE, "[0]", "Testing functions");
    test_cpp->set_variable(SCLS_DOCUMENTALIST_TITLE, "[1]", "Mains functions");

    project->save_formatted_as("test/");
}

////////////////////////////
//
// Mains functions
//
////////////////////////////

// Main function of the program.
int main() {
    create_hello_world();
    create_scls_documentalist();

    return 0;
}
