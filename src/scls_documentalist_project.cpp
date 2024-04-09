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
    Project::Project() {

    }

    // Create a file in the project
    Text_Piece* Project::new_file(std::string file_name, std::string pattern_name) {
        if(contains_file_by_path(file_name)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The file \"" + file_name + "\" you want to add already exist in the project.");
            return 0;
        }

        Text_Piece* file = new Text_Piece(file_name, *pattern_by_name(pattern_name));
        files().push_back(file);

        return file;
    }

    // Create a pattern in the project
    Text_Pattern* Project::new_pattern(std::string pattern_name, std::string base_text) {
        if(contains_pattern_by_name(pattern_name)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The pattern \"" + pattern_name + "\" you want to add already exist in the project.");
            return 0;
        }

        Text_Pattern pattern(pattern_name, base_text);

        for(std::map<std::string, std::string>::iterator it = a_global_variables.begin();it!=a_global_variables.end();it++) {
            pattern.set_global_variable(it->first, it->second);
        }

        patterns().push_back(pattern);
        return &patterns()[patterns().size() - 1];
    }

    // Save the project
    bool Project::save_formatted_as(std::string path) {
        if(!std::filesystem::exists(path)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The path \"" + path + "\" where you want to save the project does not exist.");
            return false;
        }

        if(!std::filesystem::is_directory(path)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The path \"" + path + "\" where you want to save the project is not a directory.");
            return false;
        }

        for(int i = 0;i<static_cast<int>(files().size());i++) {
            std::string final_path = path;
            std::vector<std::string> path_cutted = cut_string(join_string(cut_string(files()[i]->name(), "\\"), "/"), "/");

            if(path_cutted.size() > 1) {
                for(int j = 0;j<static_cast<int>(path_cutted.size()) - 1;j++) {
                    final_path += path_cutted[j] + "/";
                    if(!std::filesystem::exists(final_path)) {
                        std::filesystem::create_directory(final_path);
                    }
                }
            }
            final_path += path_cutted[path_cutted.size() - 1];

            write_in_file(final_path, files()[i]->text());
        }

        return true;
    }

    // Returns a pointer to a SCLS Format "Mary" formatted C++ project created with the new constructor
    Project* cpp_scls_format_project() {
        Project* project = new Project();

        // Create global variables
        std::string license_description = "";
        license_description += "This file is part of " + VARIABLE_START + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + VARIABLE_END + " project.\n\n";
        license_description += VARIABLE_START + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + VARIABLE_END + " is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\n";
        license_description += VARIABLE_START + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + VARIABLE_END + " is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
        license_description += "See the GNU General Public License for more details.\n\n";
        license_description += "You should have received a copy of the GNU General Public License along with " + VARIABLE_START + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + VARIABLE_END + ". If not, see <https://www.gnu.org/licenses/>.";

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

        // Create patterns
        // Create start pattern
        std::string big_separation_pattern = "////////////////////////////\n";
        std::string separation_pattern = "//******************\n";
        std::string pattern = "";
        Text_Pattern* project_pattern = project->new_pattern("file", "");
        Text_Pattern* start_pattern = project_pattern->new_pattern("start", "");
        start_pattern->set_children_separation(separation_pattern);
        start_pattern->set_default_line_start("// ");
        start_pattern->set_end_separation(big_separation_pattern);
        start_pattern->set_start_separation(big_separation_pattern);
        pattern = "";
        pattern += "//\n";
        pattern += "// " + VARIABLE_START + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + VARIABLE_END + " -> " + VARIABLE_START + "file_path" + VARIABLE_END + "\n";
        pattern += "//\n";
        start_pattern->new_pattern("main_title", pattern); pattern = "";
        pattern += "//\n";
        pattern += "// " + VARIABLE_START + SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE + VARIABLE_END + " description\n";
        pattern += "//\n";
        pattern += "// " + VARIABLE_START + SCLS_DOCUMENTALIST_PROJECT_DESCRIPTION_VARIABLE + VARIABLE_END + "\n";
        pattern += "//\n";
        start_pattern->new_pattern("project_description", pattern); pattern = "";
        pattern += "//\n";
        pattern += "// " + VARIABLE_START + "file_name_extension" + VARIABLE_END + " description\n";
        pattern += "//\n";
        pattern += "// " + VARIABLE_START + "file_description-*>\n";
        pattern += "//\n";
        start_pattern->new_pattern("file_description", pattern); pattern = "";
        pattern += "//\n";
        pattern += "// License description (" + VARIABLE_START + SCLS_DOCUMENTALIST_LICENCE_NAME_VARIABLE + VARIABLE_END + ")\n";
        pattern += "//\n";
        pattern += "// " + VARIABLE_START + SCLS_DOCUMENTALIST_LICENCE_DESCRIPTION_VARIABLE + VARIABLE_END + "\n";
        pattern += "//\n";
        start_pattern->new_pattern("license_description", pattern); pattern = "";
        pattern += "//\n";
        pattern += "// This project uses the Aster System SCLS Format \"Mary\" code format, in the public domain.\n";
        pattern += "// It is also formatted using the Aster System SCLS Documentalist \"Agatha\" library under the GPL V3.0 license.\n";
        pattern += "// See https://aster-system.github.io/aster-system/projects/scls.html for more informations.\n";
        pattern += "//\n";
        start_pattern->new_pattern("mary_agatha_description", pattern); pattern = "";

        return project;
    };

    // Project destructor
    Project::~Project() {
        for(int i = 0;i<static_cast<int>(files().size());i++) {
            delete files()[i]; files()[i] = 0;
        }
    }
}
