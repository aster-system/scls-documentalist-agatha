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

#include "scls_documentalist_cpp_ressources.h"

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

        // Add an include to the file
        inline Included_File* new_include(std::string name, std::string description) {if(contains_include_by_name(name)) return 0;Included_File inc;inc.name = name;inc.description = description;included_files().push_back(inc);return &(included_files()[included_files().size() - 1]);};
        // Add an include to the file which can be a local file
        inline Included_File* new_include(std::string name, std::string description, bool is_system) {if(contains_include_by_name(name)) return 0;Included_File inc;inc.name = name;inc.description = description;inc.is_system = is_system;included_files().push_back(inc);return &(included_files()[included_files().size() - 1]);};

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
        inline std::vector<Included_File>& included_files() {return a_included_files;};
        inline std::string path() const {return a_path;};
        inline void set_description(std::string new_description) {a_description = new_description;};
    private:
        // Description of the file
        std::string a_description = "";
        // Included files into the file
        std::vector<Included_File> a_included_files = std::vector<Included_File>();
        // Path of the file
        std::string a_path = "";
    };

    // Returns a string cutted by ignoring quote
    static std::vector<std::string> cut_string_out_quotes(std::string string, std::string cut, bool erase_blank = false, bool erase_last_if_blank = true) {
		bool in_quotes = false;
		bool special_character = false;
		std::string last_string = ""; // String since the last cut
		std::string last_string_cut = ""; // String of the "cut" size which allows to know where to cut
		std::vector<std::string> result = std::vector<std::string>();
		for (int i = 0; i < static_cast<int>(string.size()); i++) // Browse the string char by char
		{
		    if(!in_quotes)
            {
                last_string_cut += string[i];
                if (last_string_cut.size() > cut.size()) // If the string which allows to know where to cut is too long, cut him
                {
                    last_string_cut = last_string_cut.substr(1, cut.size());
                }
            }

            if (last_string_cut == cut && !in_quotes) // If the string which allows to know where to cut is equal to the part to cut, do a cut
			{
				std::string final_string = last_string.substr(0, last_string.size() - (cut.size() - 1));
				if (erase_blank)
				{
					if (final_string != "")
					{
						result.push_back(final_string);
					}
				}
				else
				{
					result.push_back(final_string);
				}
				last_string = "";
				last_string_cut = "";
			}
			else if(string[i] == '\\')
            {
                if(special_character) special_character = false;
                else special_character = true;

                last_string += string[i];
            }
			else if(string[i] == '\"' && !special_character)
            {
                in_quotes = !in_quotes;
                last_string += string[i];
                last_string_cut = "";
            }
			else
			{
				last_string += string[i];
				special_character = false;
			}
		}

		if (last_string.size() > 0 || !erase_last_if_blank) { result.push_back(last_string); } // Add the last non-cutted element
		return result;
    }

    // Returns a code without any comments
    static std::string remove_comments(std::string code) {

        // Remove one lines comments
        std::vector<std::string> content = cut_string_out_quotes(code, "\n");
        std::vector<std::string> final_content = std::vector<std::string>();
        for(int i = 0;i<static_cast<int>(content.size());i++) {
            std::string start_line = content[i];
            std::string line = cut_string_out_quotes(" " + start_line, "//")[0]; line.substr(1, line.size() - 1);

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
        inline std::string compiler_includes_path() const {return a_compiler_includes_path;};
        inline std::string description() const {return a_description;};
        inline std::string name() const {return a_name;};
        inline std::string path() const {return a_path;};
        inline void set_path(std::string new_path) {a_path = new_path;};
        inline void set_project_description(std::string new_project_description) {a_description = new_project_description;};
        inline void set_project_name(std::string new_project_name) {a_name = new_project_name;};

        // Create a file in the project
        File_To_Document* new_file(std::string name);
        // Create a macro in the project
        inline void new_macro(std::string macro_name, std::string macro_content){
            if(contains_macro_by_name(macro_name)) {
                print("Error", "SCLS Documentalist project \"" + name() + "\"", "The macro \"" + macro_name + "\" is already defined.");
                return;
            }
            Macro macro;
            macro.name = macro_name;
            macro.content = macro_content;
            macros().push_back(macro);
        };
        // Remove a macro from the project
        inline void remove_macro(std::string macro_name) {
            for(int i = 0;i<static_cast<int>(macros().size());i++) {
                if(macro_name == macros()[i].name) {
                    macros().erase(macros().begin() + i, macros().begin() + i + 1);
                    return;
                }
            }
        };

        // Getters and setters (ONLY WITHOUT ATTRIBUTES)
        inline bool contains_file_by_path(std::string path) {for(int i = 0;i<static_cast<int>(files().size());i++) {if(path == files()[i].path()) { return true; } } return false; };
        inline bool contains_macro_by_name(std::string name) {for(int i = 0;i<static_cast<int>(macros().size());i++) if(name == macros()[i].name) { return true; } return false; };
        inline File_To_Document* file_by_path(std::string path) {for(int i = 0;i<static_cast<int>(files().size());i++) {if(path == files()[i].path()) { return &files()[i]; } } return 0; };

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::vector<File_To_Document>& files() {return a_files;};
        inline std::vector<Macro>& macros() {return a_macros;};

        // Analyse the project
        void analyse();
        // Analyse a file of the project
        bool analyse_source_file(std::string file_path);
        // Format a file like it was compiled soon
        std::string format_file_as_compiler(std::string file_path, bool keep_comments = true);
        // Format a file to use it from an include
        std::string format_file_to_include_in_file(std::string content_str, std::string included_path, std::string includer_path);

        // Save all the project in the asked path
        bool save_all(std::string path);
        // Writes and returns a file of the project
        std::string write(std::string file);
    private:
        // Vector of all the files in the project
        std::vector<File_To_Document> a_files = std::vector<File_To_Document>();
        // Vector of all the defined macro
        std::vector<Macro> a_macros = std::vector<Macro>();

        // Compiler's includes path
        std::string a_compiler_includes_path = "C:\\msys64\\ucrt64\\include\\";
        // Description of the project
        std::string a_description = "";
        // Name of the project
        std::string a_name = "";
        // Path of the project
        std::string a_path = "";
    };
}

#endif // SCLS_DOCUMENTALIST_PROJECT
