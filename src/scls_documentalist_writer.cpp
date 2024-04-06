//******************
//
// SCLS Documentalist -> scls_documentalist_directory/scls_documentalist_writer.cpp
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
// scls_documentalist_directory/scls_documentalist_writer.cpp description
//
// This file is the source file of scls_documentalist_writer.h.
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

#include "../headers/scls_documentalist_writer.h"

// Use of the "scls" namespace to be more easily usable
namespace scls {

    // Most basic _File_To_Document constructor
    File_To_Document::File_To_Document(std::string path) : a_path(path) {

    }

    // Most basic Writer constructor
    Writer::Writer() {

    }

    // Create a file in the project
    File_To_Document* Writer::new_file(std::string name) {
        if(contains_file_by_path(name)) {
            scls::print("Warning", "SCLS Documentalist project \"" + project_name() + "\"", "The file \"" + name + "\" you want to add already exist in the project.");
            return 0;
        }

        File_To_Document file(name);
        files().push_back(file);

        return &(files()[files().size() - 1]);
    }

    // Save all the project in the asked path
    bool Writer::save_all(std::string path) {
        if(!std::filesystem::exists(path)) {
            scls::print("Warning", "SCLS Documentalist project \"" + project_name() + "\"", "The path \"" + path + "\" you want to save the project does not exist.");
            return false;
        }

        for(int i = 0;i<static_cast<int>(files().size());i++) {
            // Checks and creates the sub directories
            std::vector<std::string> cutted = cut_string(join_string(cut_string(files()[i].path(), "/"), "\\"), "\\");
            std::string full_path = path;
            if(cutted.size() > 1)
            {
                for(int i = 0;i<static_cast<int>(cutted.size() - 1);i++) {
                    full_path += "\\" + cutted[i];
                    if(!std::filesystem::exists(full_path)) {
                        std::filesystem::create_directory(full_path);
                    }
                }
            }

            write_in_file(path + "/" + files()[i].path(), write(files()[i].path()));
        }

        return true;
    }

    // Writes and returns the project
    std::string Writer::write(std::string file) {
        std::string result = "";

        if(!contains_file_by_path(file)) {
            scls::print("Warning", "SCLS Documentalist project \"" + project_name() + "\"", "The file \"" + file + "\" you want to write does not exist in the project.");
            return result;
        }

        File_To_Document* file_to_write = file_by_path(file);
        License license;

        // Write the header of the file
        result += "//******************\n";
        result += "//\n";
        result += "// " + project_name() + " -> " + file_to_write->path() + "\n";
        result += "//\n";
        result += "//******************\n";
        result += "//\n";
        result += "// " + project_name() + " description\n";
        result += "//\n";
        std::vector<std::string> cutted = cut_string(project_description(), "\n");
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
        cutted = cut_string(replace(license.notice, "*", project_name()), "\n");
        for(int i = 0;i<static_cast<int>(cutted.size());i++) result += "// " + cutted[i] + "\n";
        result += "//\n";

        // Write the included files
        result += "\n";
        result += file_to_write->include_part();
        result += "\n";

        return result;
    }
}
