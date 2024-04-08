//******************
//
// scls_documentalist_test -> headers/scls_documentalist_project.h
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
// headers/scls_documentalist_project.h description
//
// This file contains the project system of SCLS Documentalist.
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

#ifndef SCLS_DOCUMENTALIST_PROJECT
#define SCLS_DOCUMENTALIST_PROJECT

#include "scls_documentalist_core.h"

// Use of the "scls" namespace to be more easily usable
namespace scls {

    struct License {
        // Struct representing the used license in a project, by default to GPL V3.0

        // Name of the license
        std::string name = "GPLv3";
        // Notice of the license
        std::string notice = "This file is part of *.\n\n* is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\n* is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\nSee the GNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License along with *. If not, see <https://www.gnu.org/licenses/>.";
    };

    class File_To_Document {
        // File representing a file to document
    public:
        // Most basic _File_To_Document constructor
        File_To_Document(std::string path);

        // Getters and setters (ONLY WITHOUT ATTRIBUTES)
        inline bool is_header() const {std::string ext = file_extension(path());return ext == "h" || ext == "hpp";};

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::string description() const {return a_description;};
        inline std::string path() const {return a_path;};
        inline void set_description(std::string new_description) {a_description = new_description;};
    private:
        // Description of the file
        std::string a_description = "";
        // Path of the file
        std::string a_path = "";
    };

    // Returns a code without any comments
    static std::string remove_comments(std::string code) {

        // Remove one lines comments
        std::vector<std::string> content = cut_string_out_quotes(code, "\n");
        std::vector<std::string> final_content = std::vector<std::string>();
        for(int i = 0;i<static_cast<int>(content.size());i++) {
            std::string start_line = content[i];
            std::string line = cut_string_out_quotes(" " + start_line, "//")[0]; line = line.substr(1, line.size() - 1);

            if(line != "")final_content.push_back(line);
        }
        return join_string(final_content, "\n");
    };

    class Project {
        // Class representing the entire project
    public:
        // Most basic Project constructor
        Project();

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::string description() const {return a_description;};
        inline std::string name() const {return a_name;};
        inline void set_description(std::string new_project_description) {a_description = new_project_description;};
        inline void set_name(std::string new_project_name) {a_name = new_project_name;};

        // Create a file in the project
        File_To_Document* new_file(std::string name);
        // Create a pattern in the project
        Text_Pattern* new_pattern(std::string pattern_name, std::string base_text);

        // Getters and setters (ONLY WITHOUT ATTRIBUTES)
        inline bool contains_file_by_path(std::string path) {for(int i = 0;i<static_cast<int>(files().size());i++) {if(path == files()[i].path()) { return true; } } return false; };
        inline bool contains_pattern_by_name(std::string pattern_name) {return pattern_by_name(pattern_name) != 0; };
        inline File_To_Document* file_by_path(std::string path) {for(int i = 0;i<static_cast<int>(files().size());i++) {if(path == files()[i].path()) { return &files()[i]; } } return 0; };
        inline Text_Pattern* pattern_by_name(std::string pattern_name) {for(int i = 0;i<static_cast<int>(patterns().size());i++){ if(patterns()[i].name() == pattern_name) return &patterns()[i]; } return 0;};

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::vector<File_To_Document>& files() {return a_files;};
        inline std::vector<Text_Pattern>& patterns() {return a_patterns;};

        // Save all the project in the asked path in AAP
        bool save_as_aap(std::string path);
    private:
        // Vector of all the files in the project
        std::vector<File_To_Document> a_files = std::vector<File_To_Document>();

        // Datas for Agatha
        // Each defined patterns
        std::vector<Text_Pattern> a_patterns = std::vector<Text_Pattern>();

        // Datas about the project
        // Description of the project
        std::string a_description = "";
        // Name of the project
        std::string a_name = "";
    };

    // Returns a pointer to a SCLS Format "Mary" formatted C++ project created with the new constructor
    Project* cpp_scls_format_project();
}

#endif // SCLS_DOCUMENTALIST_PROJECT
