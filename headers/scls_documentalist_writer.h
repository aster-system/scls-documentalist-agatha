//******************
//
// scls_documentalist.h
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Documentalist "Agatha" part represents a easy way to document a SCLS part.
// It is named after one of the greatest author of all time, Agatha Christie.
//
// This file contains the writer of the part.
//
//******************
//
// License (GPL V3.0) :
//
// Copyright (C) 2024 by Aster System, Inc. <https://aster-system.github.io/aster-system/>
// This file is part of SCLS.
// SCLS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// SCLS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with SCLS. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef SCLS_DOCUMENTALIST_WRITER
#define SCLS_DOCUMENTALIST_WRITER

#include <scls_foundation.h>

// Use of the "scls" namespace to be more easily usable
namespace scls {

    // Base text
    static std::string source_cpp_description_text = "This file is the source file of *.";

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
        inline void set_source_cpp_description() {if(!is_header()) { set_description(replace(source_cpp_description_text, "*", file_name(path()) + ".h")); }};

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
