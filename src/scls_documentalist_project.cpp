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

        // Get each files
        std::vector<std::string> sub_files = directory_content(path(), true);
    }

    // Analyse a file of the project
    bool Project::analyse_source_file(std::string file_path) {
        std::string content_str = read_file(file_path);
        std::vector<std::string> content = cut_string(content_str, "\n", true, true);

        for(int i = 0;i<static_cast<int>(content.size());i++) {
            std::string line = content[i];

            // Ignore the comments and the empty lines
            line = remove_first_and_last_space(line);
            if(line.size() <= 0 || line == "") { continue; }

            // Check if its a preprocessing directive
            if(line[0] == '#') {
                const std::string base_line = line;
                line = remove_first_and_last_space(line.substr(1, line.size() - 1));

                int pos = 0; while(line[pos]!=' '&&line[pos]!='\"'&&line[pos]!='<')pos++;
                int offset = 0; while(line[pos + offset]==' ') offset++;

                // Get the type
                std::string type_str = line.substr(0, pos);
                Preprocessor_Directive_Types type = string_to_preprocessor_directive_type(type_str);
                if(type == Preprocessor_Directive_Types::Unknow) {
                    print("Error", "SCLS Documentalist file \"" + file_path + "\"", "The preprocessing directive \"" + type_str + "\" is unknow at line " + std::to_string(i + 1) + ".");
                    return "";
                }
                else if(type == Preprocessor_Directive_Types::Include) {
                    // If a file is included
                    std::string included = remove_first_and_last_space(line.substr(type_str.size() + offset, line.size() - (type_str.size() + offset)));
                    bool is_system = true;

                    // Format the included file
                    if(included[0] == '\"' && included[included.size() - 1] == '\"') {
                        is_system = false;
                    }
                    else if(included[0] == '<' && included[included.size() - 1] == '>') {
                        is_system = true;
                    }
                    else {
                        print("Error", "SCLS Documentalist project \"" + name() + "\" file \"" + file_path + "\"", "The included file \"" + included + "\" is badly syntaxed at line " + std::to_string(i + 1) + ".");
                        return "";
                    }
                    included = included.substr(1, included.size() - 2);

                    std::cout << "Q " << included << " " << is_system << std::endl;
                }
                line = base_line;
            }
        }

        return true;
    }

    // Format a file like it was compiled soon
    std::string Project::format_file_as_compiler(std::string file_path, bool keep_comments) {
        std::string parent_path = file_path.substr(0, file_path.size() - (file_name(file_path, true).size()));
        std::string content_str = remove_comments(read_file(file_path));
        std::vector<std::string> content = cut_string(content_str, "\n", true, true);
        std::vector<std::string> final_content = std::vector<std::string>();

        // If preprocessor ask to block a part
        unsigned int preprocessor_block = 0;

        for(int i = 0;i<static_cast<int>(content.size());i++) {
            std::string line = content[i];

            // Ignore the comments and the empty lines
            line = remove_first_and_last_space(line);
            if(line.size() <= 0 || line == "") { continue; }

            // Check if its a preprocessing directive
            if(line[0] == '#') {
                const std::string base_line = line;
                line = remove_first_and_last_space(line.substr(1, line.size() - 1));

                int pos = 0; while(line[pos]!=' '&&line[pos]!='\"'&&line[pos]!='<')pos++;
                int offset = 0; while(line[pos + offset]==' ') offset++;

                // Get the type
                std::string type_str = line.substr(0, pos);
                Preprocessor_Directive_Types type = string_to_preprocessor_directive_type(type_str);
                if(type == Preprocessor_Directive_Types::Unknow) {
                    print("Error", "SCLS Documentalist file \"" + file_path + "\"", "The preprocessing directive \"" + type_str + "\" is unknow at line " + std::to_string(i + 1) + ".");
                    return "";
                }
                else if(type == Preprocessor_Directive_Types::Include) { // If a file is included
                    std::string included = remove_first_and_last_space(line.substr(type_str.size() + offset, line.size() - (type_str.size() + offset)));
                    // Local file
                    std::string content_str = "";

                    // Format the included file
                    if(included[0] == '\"' && included[included.size() - 1] == '\"') {
                        included = format_path(included.substr(1, included.size() - 2));
                        if(!std::filesystem::exists(included)) included = format_path(parent_path + included);
                        if(!std::filesystem::exists(included)) {
                            print("Error", "SCLS Documentalist project file \"" + file_path + "\"", "The included file \"" + included + "\" does not exist at line " + std::to_string(i + 1) + ".");
                            return "";
                        }
                        content_str = format_file_as_compiler(included, false);
                    }
                    else if(included[0] == '<' && included[included.size() - 1] == '>') { continue;
                        included = included.substr(1, included.size() - 2);
                        std::string full_included = included; if(!contains(included, ".")) full_included += ".h";
                        if(std::filesystem::exists(compiler_includes_path() + full_included)) {
                                included = compiler_includes_path() + full_included;
                        }
                        else {
                            included = compiler_includes_path() + "c++\\13.1.0\\" + included;
                        }
                        content_str = format_file_as_compiler(included, false);
                    }
                    else {
                        print("Error", "SCLS Documentalist project \"" + name() + "\" file \"" + file_path + "\"", "The included file \"" + included + "\" is badly syntaxed at line " + std::to_string(i + 1) + ".");
                        return "";
                    }

                    std::vector<std::string> cutted_content = cut_string(content_str, "\n");
                    std::vector<std::string> final_lines = std::vector<std::string>();
                    for(int j = 0;j<i;j++) {
                        final_lines.push_back(content[j]);
                    }
                    for(int j = 0;j<static_cast<int>(cutted_content.size());j++) {
                        final_lines.push_back(cutted_content[j]);
                    }
                    for(int j = i + 1;j<(static_cast<int>(content.size()));j++) {
                        final_lines.push_back(content[j]);
                    }
                    content.clear();
                    content = final_lines;
                    final_content.clear();
                    i = -1;
                    macros().clear();
                    preprocessor_block = 0;
                    continue;
                }
                line = base_line;
            }
            // If preprocessor block, continue
            if(preprocessor_block > 0) continue;

            final_content.push_back(line);
        }

        return join_string(final_content, "\n");
    }

    // Format at file to use it from an include
    std::string Project::format_file_to_include_in_file(std::string content_str, std::string included_path, std::string includer_path) {
        std::vector<std::string> content = cut_string(content_str, "\n", true, true);
        std::vector<std::string> final_content = std::vector<std::string>();

        for(int i = 0;i<static_cast<int>(content.size());i++) {
            std::string line = content[i];

            // Ignore the comments and the empty lines
            line = line.substr(0, line.size() - 1);
            if(line == "" || line.substr(0, 2) == "//") continue;

            while(line[0] == ' ') line = line.substr(1, line.size() - 1);

            // Check if its a preprocessing directive
            if(line[0] == '#') {
                line = line.substr(1, line.size() - 1);
                std::vector<std::string> cutted = cut_string(line, " ");

                // Get the type
                Preprocessor_Directive_Types type = string_to_preprocessor_directive_type(cutted[0]);

                // If a file is included
                if(type == Preprocessor_Directive_Types::Include) {
                    std::string included = line.substr(cutted[0].size() + 1, line.size() - (cutted[0].size() + 1));
                    // Local file
                    if(included[0] == '\"' && included[included.size() - 1] == '\"') {
                        included = included.substr(1, included.size() - 2);
                        std::string way = go_from_path_to_path(includer_path, included_path);
                        included = way + included;
                        line = "#include \"" + included + "\"";
                    }
                    else line = "#include " + included;
                }
            }

            final_content.push_back(line);
        }
        return join_string(final_content, "\n");
    }

    // Save all the project in the asked path
    bool Project::save_all(std::string save_path) {
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
