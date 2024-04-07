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

    // Most basic _File_To_Document constructor
    File_To_Document::File_To_Document(std::string path) : a_path(path) {

    }

    // Most basic Project constructor
    Project::Project() {

    }

    // Create a file in the project
    File_To_Document* Project::new_file(std::string file_name) {
        if(contains_file_by_path(file_name)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The file \"" + file_name + "\" you want to add already exist in the project.");
            return 0;
        }

        File_To_Document file(file_name);
        files().push_back(file);

        return &(files()[files().size() - 1]);
    }

    // Create a pattern in the project
    Text_Pattern* Project::new_pattern(std::string pattern_name, std::string base_text) {
        if(contains_pattern_by_name(pattern_name)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The pattern \"" + pattern_name + "\" you want to add already exist in the project.");
            return 0;
        }

        Text_Pattern pattern(pattern_name, base_text);
        patterns().push_back(pattern);
        return &patterns()[patterns().size() - 1];
    }

    // Save all the project in the asked path
    bool Project::save_as_aap(std::string save_path) {
        if(!std::filesystem::exists(save_path)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The path \"" + save_path + "\" you want to save the project does not exist.");
            return false;
        }

        for(int i = 0;i<static_cast<int>(files().size());i++) {
            // Checks and creates the sub directories
            std::vector<std::string> cutted = cut_string(join_string(cut_string(files()[i].path(), "/"), "\\"), "\\");
            std::string full_path = save_path;
            if(cutted.size() > 1)
            {
                for(int i = 0;i<static_cast<int>(cutted.size() - 1);i++) {
                    full_path += "\\" + cutted[i];
                    if(!std::filesystem::exists(full_path)) {
                        std::filesystem::create_directory(full_path);
                    }
                }
            }

        std::string result = "";
        File_To_Document* file_to_write = file_by_path(save_path);
        License license;

        // Write the header of the file
        result += "//******************\n";
        result += "//\n";
        result += "// " + name() + " -> " + file_to_write->path() + "\n";
        result += "//\n";
        result += "//******************\n";
        result += "//\n";
        result += "// " + name() + " description\n";
        result += "//\n";
        cutted = cut_string(description(), "\n");
        for(int i = 0;i<static_cast<int>(cutted.size());i++) result += "// " + cutted[i] + "\n";
        result += "//\n";
        result += "//******************\n";
        result += "//\n";
        result += "// " + file_to_write->path() + " description\n";
        result += "//\n";
        cutted = cut_string(file_to_write->description(), "\n");
        for(int i = 0;i<static_cast<int>(cutted.size());i++) result += "// " + cutted[i] + "\n";
        result += "//\n";
        result += "//******************\n";
        result += "//\n";
        result += "// License (" + license.name + ")\n";
        result += "//\n";
        cutted = cut_string(replace(license.notice, "*", name()), "\n");
        for(int i = 0;i<static_cast<int>(cutted.size());i++) result += "// " + cutted[i] + "\n";
        result += "//\n";

            write_in_file(save_path + "/" + files()[i].path(), result);
        }

        return true;
    }

}
