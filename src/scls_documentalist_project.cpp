//******************
//
// scls_documentalist_test -> src/scls_documentalist_project.cpp
//
//******************
//
// scls_documentalist_test description
//
// SCLS Documentalist "Agatha" is a part of the Aster System SCLS project.
// This part is made to easily document C++ files.
// It is made for SCLS, but you can still use it in your project. However, it may be a little less adapted.
// This part is named after one of the most famous author, Agatha Christie.
//
//******************
//
// src/scls_documentalist_project.cpp description
//
// This file is the source file of scls_documentalist_project.h.
//
//******************
//
// License (GPLv3)
//
// This file is part of scls_documentalist_test.
//
// scls_documentalist_test is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// scls_documentalist_test is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with scls_documentalist_test. If not, see <https://www.gnu.org/licenses/>.
//

#include "../headers/scls_documentalist_project.h"

// Use of the "scls" namespace to be more easily usable
namespace scls {

    // Most basic Project constructor
    Project::Project(std::string name) : a_name(name) {

    }

    // Create a pattern in the project
    Text_Pattern* Project::new_pattern(std::string pattern_name, std::string base_text) {
        if(contains_pattern_by_name(pattern_name)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The pattern \"" + pattern_name + "\" you want to add already exist in the project.");
            return 0;
        }

        Text_Pattern* pattern = new Text_Pattern(pattern_name, base_text);

        patterns().push_back(pattern);
        return pattern;
    }

    // Save the project unformatted
    bool Project::save_sda_0_1(std::string path) {
        if(!std::filesystem::exists(path)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The path \"" + path + "\" where you want to save the project does not exist.");
            return false;
        }

        if(!std::filesystem::is_directory(path)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The path \"" + path + "\" where you want to save the project is not a directory.");
            return false;
        }

        // Save each files
        std::string all_file_config = "<all_files>";
        for(int i = 0;i<static_cast<int>(patterns().size());i++) {
            std::string file_path = path + patterns()[i]->name().to_std_string() + ".sdapf";
            all_file_config += file_path + ";";
            scls::write_in_file(file_path, patterns()[i]->base_text());
        }
        all_file_config = all_file_config.substr(0, all_file_config.size() - 1);

        // Create the .sda file
        std::string config_file = "<version>SDA 0.1" + all_file_config;
        std::string config_file_path = path + name() + ".sda";
        write_in_file(config_file_path, config_file);

        return true;
    }

    // Returns a pointer to a SCLS Format "Mary" formatted C++ project created with the new constructor
    Project* cpp_scls_format_project(std::string project_name) {
        Project* project = new Project(project_name);

        // Create global variables
        std::string license_description = "";
        license_description += "This file is part of " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " project.\n\n";
        license_description += SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\n";
        license_description += SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
        license_description += "See the GNU General Public License for more details.\n\n";
        license_description += "You should have received a copy of the GNU General Public License along with " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + ". If not, see <https://www.gnu.org/licenses/>.";

        std::string project_description = "";
        project_description += "SCLS Documentalist is a part of the SCLS library.\n\n";
        project_description += "SLCS is a set of C++ library, made to make C++ development easier.\n";
        project_description += "For more information, see https://aster-system.github.io/aster-system/projects/scls.html.\n\n";
        project_description += "The Documentalist part is a part of the library made to handle easily file documentation.\n";
        project_description += "For that, it uses the SCLS Format \"Mary\" C++ format.\n";
        project_description += "For more information, see https://aster-system.github.io/aster-system/scls/documentalist.html.";

        project->set_global_variable(SCLS_DOCUMENTALIST_LICENCE_NAME_VARIABLE, "GPL V3.0");
        project->set_global_variable(SCLS_DOCUMENTALIST_LICENCE_DESCRIPTION_VARIABLE, license_description);
        project->set_global_variable(SCLS_DOCUMENTALIST_PROJECT_DESCRIPTION_VARIABLE, project_description);
        project->set_global_variable(SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE, "SCLS Documentalist");

        std::string big_separation_pattern = "\n\n////////////////////////////////////////////////////////\n//****************************************************//\n////////////////////////////////////////////////////////\n\n\n";
        std::string external_separation_pattern = "////////////////////////////\n";
        std::string separation_pattern = "//******************\n";
        std::string pattern = "";

        // Create cpp pattern
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " -> " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + "file_path" + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "//\n";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " description\n";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_PROJECT_DESCRIPTION_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "//\n";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + "file_name_extension" + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " description\n";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + "file_description-*>\n";
        pattern += "//\n";
        pattern += "//\n";
        pattern += "// License description (" + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_LICENCE_NAME_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + ")\n";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_LICENCE_DESCRIPTION_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "//\n";
        pattern += "//\n";
        pattern += "// This project uses the Aster System SCLS Format \"Mary\" code format, in the public domain.\n";
        pattern += "// It is also formatted using the Aster System SCLS Documentalist \"Agatha\" library under the GPL V3.0 license.\n";
        pattern += "// See https://aster-system.github.io/aster-system/projects/scls.html for more informations.\n";
        pattern += "//\n";
        // Set the project preprocessors
        // Set the include part
        pattern += external_separation_pattern;
        pattern += "//\n";
        pattern += "// Included files\n";
        pattern += "//\n";
        pattern += external_separation_pattern + "\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_INCLUDE_PATH + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " -> " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "#include " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_INCLUDE_PATH + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        // Set the macro part
        pattern += "\n" + external_separation_pattern;
        pattern += "//\n";
        pattern += "// Macros definitions\n";
        pattern += "//\n";
        pattern += external_separation_pattern + "\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_MACRO_NAME + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " -> " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_MACRO_DESCRIPTION + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "#ifndef " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_MACRO_NAME + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "#define " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_MACRO_NAME + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_MACRO_CONTENT + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "#endif // " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_MACRO_NAME + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        // Set the code part
        pattern += external_separation_pattern;
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_TITLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "//\n";
        pattern += external_separation_pattern + "\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_CODE_PART_TITLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_CODE_PART + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n\n";
        Text_Pattern* project_pattern = project->new_pattern("file_cpp", pattern);

        // Create header pattern
        // Set the project presentation
        pattern = "";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " -> " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + "file_path" + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "//\n";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " description\n";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_PROJECT_DESCRIPTION_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "//\n";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + "file_name_extension" + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " description\n";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + "file_description-*>\n";
        pattern += "//\n";
        pattern += "//\n";
        pattern += "// License description (" + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_LICENCE_NAME_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + ")\n";
        pattern += "//\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_LICENCE_DESCRIPTION_VARIABLE + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "//\n";
        pattern += "//\n";
        pattern += "// This project uses the Aster System SCLS Format \"Mary\" code format, in the public domain.\n";
        pattern += "// It is also formatted using the Aster System SCLS Documentalist \"Agatha\" library under the GPL V3.0 license.\n";
        pattern += "// See https://aster-system.github.io/aster-system/projects/scls.html for more informations.\n";
        pattern += "//\n";
        // Set the project preprocessors
        pattern = "";
        pattern += external_separation_pattern;
        pattern += "//\n";
        pattern += "// Avoid multiple header repetitions\n";
        pattern += "//\n";
        pattern += external_separation_pattern + "\n";
        pattern += "#ifndef " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n#define " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY;
        pattern += "\n";
        // Set the include part
        pattern += "\n" + external_separation_pattern;
        pattern += "//\n";
        pattern += "// Included files\n";
        pattern += "//\n";
        pattern += external_separation_pattern + "\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_INCLUDE_PATH + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " -> " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "#include " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_INCLUDE_PATH + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        // Set the macro part
        pattern += "\n" + external_separation_pattern;
        pattern += "//\n";
        pattern += "// Macros definitions\n";
        pattern += "//\n";
        pattern += external_separation_pattern + "\n";
        pattern += "// " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_MACRO_NAME + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " -> " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_MACRO_DESCRIPTION + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "#ifndef " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_MACRO_NAME + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "#define " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_MACRO_NAME + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + " " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_MACRO_CONTENT + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        pattern += "#endif // " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_MACRO_NAME + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY + "\n";
        // Set the project last endif
        pattern = "";
        pattern += external_separation_pattern;
        pattern += "//\n";
        pattern += "// Avoid multiple header repetitions\n";
        pattern += "//\n";
        pattern += external_separation_pattern + "\n";
        pattern += "#endif // " + SCLS_BALISE_START_PLAIN_TEXT_STD_STRING + SCLS_DOCUMENTALIST_VARIABLE_KEYWORD + " " + SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION + SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY;
        project_pattern = project->new_pattern("file_h", pattern);

        return project;
    };

    // Project destructor
    Project::~Project() {
        for(int i = 0;i<static_cast<int>(patterns().size());i++) {
            delete patterns()[i]; patterns()[i] = 0;
        } patterns().clear();
    }
}
