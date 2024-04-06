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

    // Analyse the project
    void Project::analyse() {
        // Check the asserts
        if(!std::filesystem::exists(path())) {
            print("Warning", "SCLS Documentalist Project", "The project \"" + path() + "\" you want to read does not exist.");
            return;
        }
        if(!std::filesystem::is_directory(path())) {
            print("Warning", "SCLS Documentalist Project", "The project \"" + path() + "\" you want to read is not a directory.");
            return;
        }

        // Get each source files
        std::vector<std::string> src_files = std::vector<std::string>();
        std::vector<std::string> sub_files = directory_content(path(), true);
        for(int i = 0;i<static_cast<int>(sub_files.size());i++) {
            if(file_extension(sub_files[i]) == "cpp") {
                src_files.push_back(sub_files[i]);
            }
        }

        for(int i = 0;i<static_cast<int>(src_files.size());i++) {
            analyse_file(src_files[i]);
        }
    }

    // Analyse a file of the project
    void Project::analyse_file(std::string path) {
        std::vector<std::string> content = cut_string(read_file(path), "\n", true, true);

        for(int i = 0;i<static_cast<int>(content.size());i++) {
            // Ignore the comments and the empty lines
            content[i] = content[i].substr(0, content[i].size() - 1);
            if(content[i].substr(0, 2) == "//" || content[i] == "") continue;

            print("Debug", "SCLS Project analyse", content[i]);
        }
    }

    // Save all the project in the asked path
    bool Project::save_all(std::string save_path) {
        if(!std::filesystem::exists(save_path)) {
            scls::print("Warning", "SCLS Documentalist project \"" + path() + "\"", "The path \"" + save_path + "\" you want to save the project does not exist.");
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

            write_in_file(save_path + "/" + files()[i].path(), write(files()[i].path()));
        }

        return true;
    }

    // Writes and returns the project
    std::string Project::write(std::string file) {
        std::string result = "";

        if(!contains_file_by_path(file)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The file \"" + file + "\" you want to write does not exist in the project.");
            return result;
        }

        File_To_Document* file_to_write = file_by_path(file);
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
        std::vector<std::string> cutted = cut_string(description(), "\n");
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

        // Write the included files
        result += "\n";
        result += file_to_write->include_part();
        result += "\n";

        return result;
    }
}
