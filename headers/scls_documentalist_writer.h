//******************
//
// SCLS Documentalist -> scls_documentalist_directory/scls_documentalist_writer.h
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
// scls_documentalist_directory/scls_documentalist_writer.h description
//
// This file contains the writing system of SCLS Documentalist.
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

#ifndef SCLS_DOCUMENTALIST_WRITER
#define SCLS_DOCUMENTALIST_WRITER

#include <scls_foundation.h>

// Use of the "scls" namespace to be more easily usable
namespace scls {

    // Base text
    static std::string source_cpp_description_text = "This file is the source file of *.";

    struct Include {
        // Struct representing datas about included files

        // Description of the included file
        std::string description = "Iostream is a standart C++ library.\nIt allows the program to communicate with the user easily.";
        // If the included file is a system included file or not
        bool is_system = true;
        // Name of the included file
        std::string name = "iostream";
    };

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

        // Add an include to the file
        inline Include* new_include(std::string name, std::string description) {if(contains_include_by_name(name)) return 0;Include inc;inc.name = name;inc.description = description;included_files().push_back(inc);return &(included_files()[included_files().size() - 1]);};
        // Add an include to the file which can be a local file
        inline Include* new_include(std::string name, std::string description, bool is_system) {if(contains_include_by_name(name)) return 0;Include inc;inc.name = name;inc.description = description;inc.is_system = is_system;included_files().push_back(inc);return &(included_files()[included_files().size() - 1]);};

        // Returns the include part of the file
        std::string include_part() {
            std::string result = "//******************\n//\n// Includes\n//\n//******************\n\n";
            for(int i = 0;i<static_cast<int>(included_files().size());i++) {
                std::string include_part = included_files()[i].name;
                if(included_files()[i].is_system) {
                   include_part = "<" + include_part + ">";
                }
                else {
                    include_part = "\"" + include_part + "\"";
                }

                result += "// " + included_files()[i].name + " -> " + included_files()[i].description + "\n";
                result += "#include " + include_part + "\n";
            }
            return result;
        };

        // Getters and setters (ONLY WITHOUT ATTRIBUTES)
        inline bool contains_include_by_name(std::string name) {for(int i = 0;i<static_cast<int>(included_files().size());i++){if(included_files()[i].name == name) {return true;}} return false;};
        inline bool is_header() const {std::string ext = file_extension(path());return ext == "h" || ext == "hpp";};
        inline void set_source_cpp_description() {if(!is_header()) { set_description(replace(source_cpp_description_text, "*", file_name(path()) + ".h")); }};

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::string description() const {return a_description;};
        inline std::vector<Include>& included_files() {return a_included_files;};
        inline std::string path() const {return a_path;};
        inline void set_description(std::string new_description) {a_description = new_description;};
    private:
        // Description of the file
        std::string a_description = "";
        // Included files into the file
        std::vector<Include> a_included_files = std::vector<Include>();
        // Path of the file
        std::string a_path = "";
    };

    class Writer {
        // Class representing the writer of the part, which can print an entire project
    public:
        // Most basic Writer constructor
        Writer();

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::string project_description() const {return a_project_description;};
        inline std::string project_name() const {return a_project_name;};
        inline void set_project_description(std::string new_project_description) {a_project_description = new_project_description;};
        inline void set_project_name(std::string new_project_name) {a_project_name = new_project_name;};

        // Create a file in the project
        File_To_Document* new_file(std::string name);

        // Getters and setters (ONLY WITHOUT ATTRIBUTES)
        inline bool contains_file_by_path(std::string path) {for(int i = 0;i<static_cast<int>(files().size());i++) {if(path == files()[i].path()) { return true; } } return false; };
        inline File_To_Document* file_by_path(std::string path) {for(int i = 0;i<static_cast<int>(files().size());i++) {if(path == files()[i].path()) { return &files()[i]; } } return 0; };

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::vector<File_To_Document>& files() {return a_files;};

        // Save all the project in the asked path
        bool save_all(std::string path);
        // Writes and returns a file of the project
        std::string write(std::string file);
    private:
        // Vector of all the files in the project
        std::vector<File_To_Document> a_files = std::vector<File_To_Document>();

        // Description of the project
        std::string a_project_description = "";
        // Name of the project
        std::string a_project_name = "";
    };
}

#endif // SCLS_DOCUMENTALIST_WRITER
