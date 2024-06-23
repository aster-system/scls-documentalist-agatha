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

    // Most basic Pattern_Project constructor
    Pattern_Project::Pattern_Project(std::string name, std::string path) : a_name(name), a_path(path) { }

    // Returns the content of a file
    std::string Pattern_Project::file_content(Replica_File& file) {
        std::string to_return = "";
        if(!contains_pattern(file.pattern)) return to_return;

        // Format the text
        std::string base_pattern_content = file.pattern->base_text().to_std_string();
        int level = 0;
        std::string pattern_content = "";
        for(int i = 0;i<static_cast<int>(base_pattern_content.size());i++) {
            if(base_pattern_content[i] == '<') level++;
            else if(base_pattern_content[i] == '>') level--;
            else if(level <= 0) pattern_content += base_pattern_content[i];
        }

        // Use the variable
        pattern_content = format_string_as_plain_text(pattern_content);
        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(pattern_content);

        to_return = pattern_content;

        return to_return;
    }

    // Load a project unformatted from sda V0.1
    Pattern_Project* Pattern_Project::load_sda_0_1(std::string path) {
        if(!std::filesystem::exists(path)) return 0;
        std::string content = read_file(path);
        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(content);

        // Get the datas about the project
        std::vector<std::string> files = std::vector<std::string>();
        std::string final_name = "";
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].content.size() > 0) {
                if(cutted[i].content[0] == '<') {
                    // The part of the text is a balise
                    std::string final_balise_name = balise_name(cutted[i].content);
                    if(final_balise_name == "name") {
                        // Get the name of the project
                        i++; if(i < static_cast<int>(cutted.size())) final_name = cutted[i].content;
                    }
                    else if(final_balise_name == "all_files") {
                        // Get each files in the project
                        i++; if(i < static_cast<int>(cutted.size())) files = cut_string(cutted[i].content, "?");
                    }
                }
            }
        }
        Pattern_Project* new_project = new Pattern_Project(final_name, path);

        // Load each files
        for(int i = 0;i<static_cast<int>(files.size());i++) {
            if(std::filesystem::exists(files[i])) {
                std::string file_content = read_file(files[i]);
                std::string current_file_name = file_name(files[i]);
                new_project->new_pattern(current_file_name, file_content);
            }
        }

        new_project->parse_project();
        return new_project;
    }

    // Parse the entire project
    void Pattern_Project::parse_project() {
        a_global_variables.clear();

        // Get each global variables
        for(int i = 0;i<static_cast<int>(patterns().size());i++) {
            patterns()[i].get()->parse_pattern();
            std::vector<std::shared_ptr<Pattern_Variable>>& current_global_variables = patterns()[i].get()->global_variables();

            // Analyse each variables
            for(int j = 0;j<static_cast<int>(current_global_variables.size());j++) {
                bool is_already_loaded = false;
                for(int k = 0;k<static_cast<int>(a_global_variables.size());k++) {
                    if(a_global_variables[k].get()->name == current_global_variables[j].get()->name) {
                        is_already_loaded = true;
                    }
                }

                if(!is_already_loaded) {
                    a_global_variables.push_back(current_global_variables[j]);
                }
            }
        }
    }

    // Create a pattern in the project
    Text_Pattern* Pattern_Project::new_pattern(std::string pattern_name, std::string base_text) {
        if(contains_pattern_by_name(pattern_name)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The pattern \"" + pattern_name + "\" you want to add already exist in the project.");
            return 0;
        }

        std::shared_ptr<Text_Pattern> pattern = std::make_shared<Text_Pattern>(pattern_name, base_text);

        patterns().push_back(pattern);
        return pattern.get();
    }

    // Save the project unformatted
    bool Pattern_Project::save_sda_0_1(std::string path) {
        if(!std::filesystem::exists(path)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The path \"" + path + "\" where you want to save the project does not exist.");
            return false;
        }

        if(!std::filesystem::is_directory(path)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The path \"" + path + "\" where you want to save the project is not a directory.");
            return false;
        }

        // Save each files
        std::string all_file_config = "";
        if(static_cast<int>(patterns().size()) > 0) {
            all_file_config = "<all_files>";
            for(int i = 0;i<static_cast<int>(patterns().size());i++) {
                std::string file_path = path + patterns()[i]->name().to_std_string() + ".sdapf";
                all_file_config += file_path + "?";
                scls::write_in_file(file_path, patterns()[i]->base_text());
            }
            all_file_config = all_file_config.substr(0, all_file_config.size() - 1);
        }

        // Create the .sda file
        std::string config_file = "<name>" + name() + "<version>SDA 0.1" + all_file_config;
        std::string config_file_path = path + name() + ".sda";
        write_in_file(config_file_path, config_file);

        return true;
    }

    /*// Returns a pointer to a SCLS Format "Mary" formatted C++ project created with the new constructor
    Pattern_Project* cpp_scls_format_project(std::string project_name, std::string project_path) {
        Pattern_Project* project = new Pattern_Project(project_name, project_path);

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

        std::string big_separation_pattern = "\n\n////////////////////////////////////////////////////////\n//****************************************************\n////////////////////////////////////////////////////////\n\n\n";
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
    }; //*/

    // Pattern_Project destructor
    Pattern_Project::~Pattern_Project() { }

    // Most basic Replica_Project constructor
    Replica_Project::Replica_Project(std::string name, const std::shared_ptr<Pattern_Project>& pattern) : a_name(name), a_pattern(pattern) {

    }

    // Add a replica file to the project
    Replica_File* Replica_Project::add_replica_file(std::string replica_file_path, scls::Text_Pattern* pattern) {
        if(replica_file_by_path(replica_file_path) != 0) return 0;

        // Create the file
        replica_files().push_back(Replica_File());
        Replica_File& new_replica = replica_files()[replica_files().size() - 1];
        new_replica.internal_path = replica_file_path;
        new_replica.pattern = pattern;

        return &new_replica;
    }

    // Exports the project
    bool Replica_Project::export_project(std::string path) {
        if(!std::filesystem::exists(path)) {
            scls::print("Warning", "SCLS Documentalist replica \"" + name() + "\" export", "The path \"" + path + "\" where you want to export the replica does not exist.");
            return false;
        }

        if(!std::filesystem::is_directory(path)) {
            scls::print("Warning", "SCLS Documentalist replica \"" + name() + "\" export", "The path \"" + path + "\" where you want to export the replica is not a directory.");
            return false;
        }

        // Create the directory
        if(path[path.size() - 1] != '/') path += "/";
        path += name() + "_export/";
        if(!std::filesystem::exists(path)) std::filesystem::create_directory(path);

        // Export each files
        for(int i = 0;i<static_cast<int>(replica_files().size());i++) {
            Replica_File& current_file = replica_files()[i];

            // Format the needed path
            std::string current_path = current_file.internal_path;
            std::vector<std::string> path_cutted = cut_string(current_path, "/"); current_path = path;
            for(int i = 0;i<static_cast<int>(path_cutted.size()) - 1;i++) {
                current_path += path_cutted[i] + "/";
                if(!std::filesystem::exists(current_path)) std::filesystem::create_directory(current_path);
            }

            // Write the file
            current_path += path_cutted[path_cutted.size() - 1];
            write_in_file(current_path, attached_pattern()->file_content(current_file));
        }

        return true;
    }

    // Load a replica file in the project from sda V 0.2
    void Replica_Project::load_replica_file_sda_0_2(std::string path) {
        if(!std::filesystem::exists(path)) return;
        std::string content = read_file(path);
        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(content);

        // Get the datas about the file
        std::string internal_path = "";
        std::string pattern = "";
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].content.size() > 0) {
                if(cutted[i].content[0] == '<') {
                    // The part of the text is a balise
                    std::string final_balise_name = balise_name(cutted[i].content);
                    if(final_balise_name == "internal_path") {
                        // Get the name of the project
                        i++; if(i < static_cast<int>(cutted.size())) internal_path = cutted[i].content;
                    }
                    else if(final_balise_name == "pattern") {
                        // Get the pattern of the project
                        i++; if(i < static_cast<int>(cutted.size())) pattern = cutted[i].content;
                    }
                }
            }
        }

        // Load the file
        Text_Pattern* final_pattern = attached_pattern()->pattern_by_name(pattern);
        if(final_pattern == 0) return;
        add_replica_file(internal_path, final_pattern);
    }

    // Load the project from sda V 0.2
    Replica_Project* Replica_Project::load_sda_0_2(std::string path, const std::shared_ptr<Pattern_Project>& pattern) {
        if(!std::filesystem::exists(path)) return 0;
        std::string content = read_file(path);
        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(content);
        path = path_parent(path);

        // Get the datas about the project
        std::vector<std::string> files = std::vector<std::string>();
        std::string final_name = "";
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].content.size() > 0) {
                if(cutted[i].content[0] == '<') {
                    // The part of the text is a balise
                    std::string final_balise_name = balise_name(cutted[i].content);
                    if(final_balise_name == "name") {
                        // Get the name of the project
                        i++; if(i < static_cast<int>(cutted.size())) final_name = cutted[i].content;
                    }
                    else if(final_balise_name == "all_files") {
                        // Get the name of the project
                        i++; if(i < static_cast<int>(cutted.size())) files = cut_string(cutted[i].content, ";");
                    }
                }
            }
        }

        Replica_Project* new_project = new Replica_Project(final_name, pattern);

        // Create each file
        for(int i = 0;i<static_cast<int>(files.size());i++) {
            new_project->load_replica_file_sda_0_2(path + "/" + files[i]);
        }

        return new_project;
    }

    // Returns the path of the attached patter in a replica
    std::string Replica_Project::replica_attached_pattern_from_path_sda_0_2(std::string path) {
        if(!std::filesystem::exists(path)) return 0;
        std::string content = read_file(path);
        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(content);

        // Get the datas about the project
        std::vector<std::string> files = std::vector<std::string>();
        std::string final_name = "";
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].content.size() > 0) {
                if(cutted[i].content[0] == '<') {
                    // The part of the text is a balise
                    std::string final_balise_name = balise_name(cutted[i].content);
                    if(final_balise_name == "pattern_path") {
                        // Get the path of pattern of the project
                        i++; if(i < static_cast<int>(cutted.size())) return cutted[i].content; else return "";
                    }
                }
            }
        }

        return "";
    }

    // Returns the text to save a replica file
    std::string Replica_Project::save_replica_file_text_sda_0_2(Replica_File& replica_file) {
        std::string to_return = "<internal_path>" + replica_file.internal_path;
        to_return += "<pattern>" + replica_file.pattern->name().to_std_string();
        return to_return;
    }

    // Save the project unformatted
    bool Replica_Project::save_sda_0_2(std::string path) {
        if(!std::filesystem::exists(path)) {
            scls::print("Warning", "SCLS Documentalist replica project \"" + name() + "\"", "The path \"" + path + "\" where you want to save the project does not exist.");
            return false;
        }

        if(!std::filesystem::is_directory(path)) {
            scls::print("Warning", "SCLS Documentalist replica project \"" + name() + "\"", "The path \"" + path + "\" where you want to save the project is not a directory.");
            return false;
        }

        // Create each files
        std::string files_content = "";
        if(replica_files().size() > 0) {
            // Save the files in the main file
            files_content += "<all_files>";
            for(int i = 0;i<static_cast<int>(replica_files().size());i++) {
                files_content += name() + std::to_string(i) + ".sdrf";
                if(i != static_cast<int>(replica_files().size()) - 1) files_content += ";";
            }

            // Create each files
            for(int i = 0;i<static_cast<int>(replica_files().size());i++) {
                std::string file_path = path + name() + std::to_string(i) + ".sdrf";
                write_in_file(file_path, save_replica_file_text_sda_0_2(replica_files()[i]));
            }
        }

        // Create the .sdr file
        std::string config_file = "<name>" + name() + "<version>SDA 0.2<pattern_path>" + attached_pattern()->path() + files_content;
        std::string config_file_path = path + name() + ".sdr";
        write_in_file(config_file_path, config_file);

        return true;
    }
}
