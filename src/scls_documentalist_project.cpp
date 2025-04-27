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

    // Apply all to a part of text
    std::string Pattern_Project::__apply_all(const std::string& base_pattern_content, __Replica_File_Variable_Element_Base& file, std::string internal_path, __Balise_Container* balising_system) {
        // Handle global variable
        std::string pattern_content = __apply_global_variables(base_pattern_content, file, balising_system);
        std::string to_return = "";

        // Handle built-in variables variable
        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(pattern_content);
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].balise_content.size() > 0) {
                // The part is a balise
                std::string current_balise_formated = formatted_balise(cutted[i].balise_content);
                std::string current_balise_name = balise_name(current_balise_formated);
                if(current_balise_name == "scls_var") {
                    // Remove the < and >
                    current_balise_formated = current_balise_formated.substr(1, current_balise_formated.size() - 2);
                    std::shared_ptr<Pattern_Variable> current_variable_shared_ptr = __analyse_pattern_variable(current_balise_formated, 0);
                    Pattern_Variable* current_variable = current_variable_shared_ptr.get();
                    if(current_variable->path_to_root) {to_return += path_to_root(internal_path);}
                    else if(current_variable->listed()) {
                        // Apply a list of variable
                        Replica_File_Variable_List* current_list = reinterpret_cast<Replica_File_Variable_List*>(file.variable_by_name(current_variable->name).get());
                        if(current_list == 0) continue;
                        // Get the needed content
                        int level = 1; i++;
                        std::string variable_content = "";
                        while(i<static_cast<int>(cutted.size())) {
                            if(cutted[i].balise_content.size() > 0) {
                                current_balise_formated = formatted_balise(cutted[i].balise_content);
                                current_balise_name = balise_name(current_balise_formated);
                                // Remove the < and >
                                current_balise_formated = current_balise_formated.substr(1, current_balise_formated.size() - 2);
                                if(current_balise_name == "scls_var") {
                                    if(current_balise_formated[0] == '/'){level--;}
                                    else{
                                        std::shared_ptr<Pattern_Variable> analyzed_variable_shared_ptr = __analyse_pattern_variable(current_balise_formated, 0);
                                        Pattern_Variable* analyzed_variable=analyzed_variable_shared_ptr.get();
                                        if(analyzed_variable->listed()){level++;}
                                    }
                                    if(level == 0) break;
                                }
                            }
                            variable_content += cutted[i].balise_content + cutted[i].content;
                            i++;
                        }

                        // Apply each element
                        for(int j = 0;j<static_cast<int>(current_list->elements.size());j++) {
                            to_return += __apply_all(variable_content, *current_list->elements[j].get(), internal_path, balising_system);
                        }
                    }
                    else {
                        // Apply a basic variable
                        std::shared_ptr<Replica_File_Variable> needed_variable = file.variable_by_name(current_variable->name);
                        if(needed_variable.get() != 0) {
                            std::string variable_content = balising_system->plain_text(needed_variable.get()->content);
                            to_return += variable_content;
                        }
                    }
                }
                else {
                    current_balise_formated = cutted[i].balise_content.substr(1, current_balise_formated.size() - 2);
                    to_return += "<" + __apply_all(current_balise_formated, file, internal_path, balising_system) + ">";
                }
            }
            else {
                to_return += cutted[i].content;
            }
        } return to_return;
    }

    // Apply the global variables to a part of text
    std::string Pattern_Project::__apply_global_variables(const std::string& part_of_text, __Replica_File_Variable_Element_Base& file, __Balise_Container* balising_system) {
        std::string to_return = "";

        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(part_of_text);
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].balise_content.size() > 0) {
                // The part is a balise
                std::string current_balise_formated = formatted_balise(cutted[i].balise_content);
                std::string current_balise_name = balise_name(current_balise_formated);
                if(current_balise_name == "scls_var") {
                    // Remove the < and >
                    current_balise_formated = current_balise_formated.substr(1, current_balise_formated.size() - 2);
                    std::shared_ptr<Pattern_Variable> current_variable_shared_ptr = __analyse_pattern_variable(current_balise_formated, 0);
                    Pattern_Variable* current_variable = current_variable_shared_ptr.get();
                    if(current_variable->global) {
                        // The variable is global
                        to_return += balising_system->plain_text(file.global_variables.get()->global_variable_value(current_variable->name));
                    }
                    else {
                        to_return += "<" + current_balise_formated + ">";
                    }
                }
                else {
                    to_return += cutted[i].balise_content;
                }
            }
            else {
                to_return += cutted[i].content;
            }
        }

        return to_return;
    }

    // Returns the content of a file
    std::string Pattern_Project::file_content(Replica_File& file, __Balise_Container* balising_system) {
        std::string to_return = "";
        if(!contains_pattern(file.pattern)) return to_return;
        std::string base_pattern_content = balising_system->plain_text(file.pattern->base_text().to_utf_8());

        // Handle global variable
        to_return = __apply_all(base_pattern_content, file, balising_system);
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
            if(cutted[i].balise_content.size() > 0) {
                if(cutted[i].balise_content[0] == '<') {
                    // The part of the text is a balise
                    std::string final_balise_name = balise_name(cutted[i].balise_content);
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
    std::shared_ptr<Text_Pattern>* Pattern_Project::new_pattern(std::string pattern_name, std::string base_text) {
        if(contains_pattern_by_name(pattern_name)) {
            scls::print("Warning", "SCLS Documentalist project \"" + name() + "\"", "The pattern \"" + pattern_name + "\" you want to add already exist in the project.");
            return 0;
        }

        std::shared_ptr<Text_Pattern> pattern = std::make_shared<Text_Pattern>(pattern_name, base_text);

        patterns().push_back(pattern);
        return &patterns()[patterns().size() - 1];
    }

    // Returns the path to the root of a path
    std::string Pattern_Project::path_to_root(std::string needed_path) {
        std::string current_path = "/base/" + needed_path;
        std::string to_add = replace(std::filesystem::relative("/base/", current_path).string(), "\\", "/");
        if(to_add.size() > 0) {
            if(to_add[0] != '.'){to_add = "." + to_add;} if(to_add[to_add.size() - 1] == '/') to_add = to_add.substr(0, to_add.size() - 1);
            while(to_add.size() > 0 && to_add[to_add.size() - 1] == '.'){to_add = to_add.substr(0, to_add.size() - 1);}
        }
        if(to_add == ""){to_add = "./";}
        return to_add;
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
        if(path[path.size() - 1] != '/') path += "/";

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

    // Pattern_Project destructor
    Pattern_Project::~Pattern_Project() {}

    // Most basic Replica_Project constructor
    Replica_Project::Replica_Project(std::string name, std::string path, const std::shared_ptr<Pattern_Project>& pattern) : a_name(name), a_path(path), a_pattern(pattern) {}

    // Add a replica file variable element to a replica file in the project
    void Replica_Project::__add_replica_file_variable_element(std::shared_ptr<Replica_File_Variable_Element> element, std::string main_path, std::string replica_file_variable_path, std::shared_ptr<Replica_File_Variable> parent) {
        std::string path = replica_file_variable_path;
        if(!std::filesystem::exists(path)) {
            path = main_path + "/" + replica_file_variable_path;
            if(!std::filesystem::exists(path)) return;
        }

        // Create the needed variables for the adding
        std::string variable_content = "";
        std::string variable_name = "";
        std::string variable_type = "";

        // Cut the variable file
        std::string content = read_file(path);
        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(content);
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].balise_content.size() > 0) {
                if(cutted[i].balise_content[0] == '<') {
                    // The part of the text is a balise
                    std::string final_balise_name = balise_name(cutted[i].balise_content);
                    if(final_balise_name == "name") {
                        // Get the name of the project
                        i++; if(i < static_cast<int>(cutted.size())) variable_name = cutted[i].content;
                    }
                    else if(final_balise_name == "content") {
                        // Get the files in the project
                        i++; if(i < static_cast<int>(cutted.size())) variable_content = cutted[i].content;
                    }
                    else if(final_balise_name == "type") {
                        // Get the files in the project
                        i++; if(i < static_cast<int>(cutted.size())) variable_type = cutted[i].content;
                    }
                }
            }
        }

        if(variable_name != "") {
            // Create the replica file
            std::shared_ptr<Replica_File_Variable> created_variable = element.get()->variable_by_name(variable_name);
            if(created_variable.get() != 0) {
                created_variable.get()->name = variable_name;
                created_variable.get()->parent_variable = parent;
                if(created_variable.get()->listed()) {
                    // The variable is a list
                    Replica_File_Variable_List* current_list = reinterpret_cast<Replica_File_Variable_List*>(created_variable.get());
                    std::vector<std::string> paths = cut_string(variable_content, ";");
                    for(int i = 0;i<static_cast<int>(paths.size());i++) {
                        std::shared_ptr<Replica_File_Variable_Element> new_element = std::make_shared<Replica_File_Variable_Element>();
                        new_element.get()->element_number = i;
                        new_element.get()->pattern_list = reinterpret_cast<Pattern_Variable_List*>(current_list->pattern_variable.get());
                        new_element.get()->parent_variable = created_variable;
                        new_element.get()->set_pattern(element.get()->pattern);
                        __load_replica_file_variable_element(new_element, main_path, paths[i], created_variable);
                        current_list->elements.push_back(new_element);
                    }
                } else {
                    path = variable_content;
                    if(!std::filesystem::exists(path)) {path = main_path + "/" + variable_content;}
                    if(std::filesystem::exists(path)) created_variable.get()->content = read_file(path);
                }
            }
        }
    }

    // Exports the project
    bool Replica_Project::export_project(std::string path, __Balise_Container* balising_system) {
        if(!std::filesystem::exists(path)) {
            scls::print("Warning", "SCLS Documentalist replica \"" + name() + "\" export", "The path \"" + path + "\" where you want to export the replica does not exist.");
            return false;
        }

        if(!std::filesystem::is_directory(path)) {
            scls::print("Warning", "SCLS Documentalist replica \"" + name() + "\" export", "The path \"" + path + "\" where you want to export the replica is not a directory.");
            return false;
        }

        // Create the directory
        path = export_path(path);
        if(!std::filesystem::exists(path)) std::filesystem::create_directory(path);

        // Export each files
        for(int i = 0;i<static_cast<int>(replica_files().size());i++) {
            std::shared_ptr<Replica_File> current_file = replica_files()[i];

            // Format the needed path
            std::string current_path = current_file.get()->internal_path;
            std::vector<std::string> path_cutted = cut_string(current_path, "/"); current_path = path;
            for(int i = 0;i<static_cast<int>(path_cutted.size()) - 1;i++) {
                current_path += path_cutted[i] + "/";
                if(!std::filesystem::exists(current_path)) std::filesystem::create_directory(current_path);
            }

            // Write the file
            current_path += path_cutted[path_cutted.size() - 1];
            if(current_file.get()->pattern == 0) write_in_file(current_path, balising_system->plain_text(current_file.get()->content_out_pattern));
            else write_in_file(current_path, attached_pattern()->file_content(*current_file.get(), balising_system));
        }

        return true;
    }

    // Load a global variable in the project from sda V 0.2
    void Replica_Project::load_global_variable_sda_0_2(std::string main_path, std::string file_path) {
        std::string path = file_path;
        if(!std::filesystem::exists(path)) {
            path = main_path + "/" + file_path;
            if(!std::filesystem::exists(path)) return;
        } std::string content = read_file(path);

        // Parse the file
        std::string variable_name = ""; int i = 0;
        while(i < static_cast<int>(content.size()) && content[i] != ';') {
            variable_name += content[i]; i++;
        }
        if(i < static_cast<int>(content.size())) i++;
        content = content.substr(i, content.size() - (i));
        if(variable_name != "") global_variables_values()[variable_name] = content;
    }

    // Load a replica file in the project from sda V 0.2
    void Replica_Project::load_replica_file_sda_0_2(std::string main_path, std::string file_path) {
        std::string path = file_path;
        if(!std::filesystem::exists(path)) {
            path = main_path + "/" + file_path;
            if(!std::filesystem::exists(path)) return;
        } std::string content = read_file(path);
        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(content);

        // Get the datas about the file
        std::string content_path = "";
        std::string internal_path = "";
        std::string pattern = "";
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].balise_content.size() > 0) {
                if(cutted[i].balise_content[0] == '<') {
                    // The part of the text is a balise
                    std::string final_balise_name = balise_name(cutted[i].balise_content);
                    if(final_balise_name == "internal_path") {
                        // Get the name of the project
                        i++; if(i < static_cast<int>(cutted.size())) internal_path = cutted[i].content;
                    }
                    else if(final_balise_name == "pattern") {
                        // Get the pattern of the file
                        i++; if(i < static_cast<int>(cutted.size())) pattern = cutted[i].content;
                    }
                    else if(final_balise_name == "content_path") {
                        // Get the path of the content of the file
                        i++; if(i < static_cast<int>(cutted.size())) content_path = cutted[i].content;
                    }
                }
            }
        }

        // Load the file
        std::string final_content = "";
        Text_Pattern* final_pattern = 0;
        std::shared_ptr<Replica_File> result;
        if(pattern != "") {
            // File with pattern
            final_pattern = attached_pattern()->pattern_by_name(pattern);
            result = new_replica_file(internal_path, final_pattern);
        }
        else if(content_path != std::string()) {
            if(!std::filesystem::exists(content_path)){content_path = main_path + std::string("/") + content_path;}
            if(std::filesystem::exists(content_path)) {
                // File without pattern
                final_content = read_file(content_path);
                result = new_replica_file(internal_path, 0);
                result.get()->content_out_pattern = final_content;
            }
        }
        // Load the needed variables
        __load_replica_file_variable_element(result, main_path, file_path, std::shared_ptr<Replica_File_Variable>());
    }

    // Load a replica file variable element in the project from sda V 0.2
    void Replica_Project::__load_replica_file_variable_element(std::shared_ptr<Replica_File_Variable_Element> element, std::string main_path, std::string file_path, std::shared_ptr<Replica_File_Variable> parent) {
        std::string path = file_path;
        if(!std::filesystem::exists(path)) {
            path = main_path + "/" + file_path;
            if(!std::filesystem::exists(path)) return;
        }
        std::string content = read_file(path);
        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(content);

        // Get the datas about the file
        std::string local_variables = "";
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].balise_content.size() > 0) {
                if(cutted[i].balise_content[0] == '<') {
                    // The part of the text is a balise
                    std::string final_balise_name = balise_name(cutted[i].balise_content);
                    if(final_balise_name == "local_variables") {
                        // Get the local variables of the file
                        i++; if(i < static_cast<int>(cutted.size())) {local_variables = cutted[i].content;}
                    }
                }
            }
        }

        // Create the variable
        std::vector<std::string> local_variables_path = cut_string(local_variables, ";");
        for(int i = 0;i<static_cast<int>(local_variables_path.size());i++) {
            std::string current_path = local_variables_path[i];
            if(current_path == "") continue;

            // Get the needed variable
            __add_replica_file_variable_element(element, main_path, current_path, parent);
        }
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
        std::vector<std::string> global_variables = std::vector<std::string>();
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].balise_content.size() > 0) {
                if(cutted[i].balise_content[0] == '<') {
                    // The part of the text is a balise
                    std::string final_balise_name = balise_name(cutted[i].balise_content);
                    if(final_balise_name == "name") {
                        // Get the name of the project
                        i++; if(i < static_cast<int>(cutted.size())) final_name = cutted[i].content;
                    }
                    else if(final_balise_name == "all_files") {
                        // Get the files in the project
                        i++; if(i < static_cast<int>(cutted.size())) files = cut_string(cutted[i].content, ";");
                    }
                    else if(final_balise_name == "all_global_variables") {
                        // Get the global variables of the project
                        i++; if(i < static_cast<int>(cutted.size())) global_variables = cut_string(cutted[i].content, ";");
                    }
                }
            }
        }

        Replica_Project* new_project = new Replica_Project(final_name, path, pattern);

        // Create each file
        for(int i = 0;i<static_cast<int>(files.size());i++) {
            new_project->load_replica_file_sda_0_2(path, files[i]);
        }

        // Create each global variables
        for(int i = 0;i<static_cast<int>(global_variables.size());i++) {
            new_project->load_global_variable_sda_0_2(path, global_variables[i]);
        }

        return new_project;
    }

    // Creates a new replica file in the project and returns it
    std::shared_ptr<Replica_File> Replica_Project::new_replica_file(std::string replica_file_path, scls::Text_Pattern* pattern) {
        // Create the file
        std::shared_ptr<Replica_File> new_file = std::make_shared<Replica_File>(a_global_variables_values);
        new_file.get()->internal_path = replica_file_path;
        new_file.get()->pattern = pattern;
        replica_files().push_back(new_file);

        return new_file;
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
            if(cutted[i].balise_content.size() > 0) {
                if(cutted[i].balise_content[0] == '<') {
                    // The part of the text is a balise
                    std::string final_balise_name = balise_name(cutted[i].balise_content);
                    if(final_balise_name == "pattern_path") {
                        // Get the path of pattern of the project
                        i++; if(i < static_cast<int>(cutted.size())){return cutted[i].content;} else {return std::string("");}
                    }
                }
            }
        } return std::string("");
    }

    // Returns the text to save a replica file
    std::string Replica_Project::save_replica_file_text_sda_0_2(Replica_File* replica_file, std::string path, unsigned int& total_file_number) {
        std::string to_return = "<internal_path>" + replica_file->internal_path;

        // Write the pattern part
        if(replica_file->pattern != 0) to_return += "<pattern>" + replica_file->pattern->name().to_std_string();
        else {
            std::string new_file_path = name() + std::to_string(total_file_number) + ".sdrf"; total_file_number++;
            to_return += "<content_path>" + new_file_path;
            __save_file(path, new_file_path, replica_file->content_out_pattern);
        }

        // Write the variable part
        to_return += save_replica_file_variable_element_text_sda_0_2(replica_file, path, total_file_number);

        return to_return;
    }

    // Returns the text to save a replica file element
    std::string Replica_Project::save_replica_file_variable_element_text_sda_0_2(__Replica_File_Variable_Element_Base* element, std::string path, unsigned int& total_file_number) {
        std::string to_return = "";

        // Write the variable part
        if(element->variables.size() > 0) {
            to_return += "<local_variables>";
            for(int i = 0;i<static_cast<int>(element->variables.size());i++) {
                std::string new_file_path = name() + std::to_string(total_file_number) + ".sdrf"; total_file_number++;
                to_return += new_file_path + ";";
                __save_file(path, new_file_path, save_replica_file_variable_text_sda_0_2(element->variables[i], path, total_file_number));
            }
            if(to_return[to_return.size() - 1] == ';') to_return = to_return.substr(0, to_return.size() - 1);
        }

        return to_return;
    }

    // Returns the text to save a replica file variable
    std::string Replica_Project::save_replica_file_variable_text_sda_0_2(Replica_File_Variable* replica_file_variable, std::string path, unsigned int& total_file_number) {
        std::string new_file_path = name() + std::to_string(total_file_number) + ".sdrf"; total_file_number++;
        std::string to_return = "<name>" + replica_file_variable->name + "<content>" + new_file_path;

        // Write the content of the variable
        __save_file(path, new_file_path, replica_file_variable->content);

        return to_return;
    }

    // Returns the text to save a replica file variable list
    std::string Replica_Project::save_replica_file_variable_list_text_sda_0_2(Replica_File_Variable_List* replica_file_variable, std::string path, unsigned int& total_file_number) {
        std::string new_file_path = name() + std::to_string(total_file_number) + ".sdrf"; total_file_number++;
        std::string to_return = "<name>" + replica_file_variable->name + "<type>list<content>";

        // Write the content of the variable
        __save_file(path, new_file_path, replica_file_variable->content);

        // Store element one by one
        for(int i = 0;i<static_cast<int>(replica_file_variable->elements.size());i++) {
            std::string content = save_replica_file_variable_element_text_sda_0_2(replica_file_variable->elements[i], path, total_file_number);
            std::string current_file_path = name() + std::to_string(total_file_number) + ".sdrf"; total_file_number++;
            __save_file(path, current_file_path, content);
            to_return += current_file_path + ";";
        } if(to_return[to_return.size() - 1] == ';') to_return = to_return.substr(0, to_return.size() - 1);

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

        if(path[path.size() - 1] != '/') path += "/";
        unsigned int total_file_number = 0;

        // Create each files
        std::string files_content = "";
        if(replica_files().size() > 0) {
            // Create each files
            files_content += "<all_files>";
            for(int i = 0;i<static_cast<int>(replica_files().size());i++) {
                files_content += name() + std::to_string(total_file_number) + ".sdrf";
                if(i != static_cast<int>(replica_files().size()) - 1) files_content += ";";
                std::string file_path = name() + std::to_string(total_file_number) + ".sdrf"; total_file_number++;
                __save_file(path, file_path, save_replica_file_text_sda_0_2(replica_files()[i].get(), path, total_file_number));
            }
        }

        // Create each global variables
        std::string global_variables_content = "";
        if(global_variables_values().size() > 0) {
            // Save the global variabless in the main file
            global_variables_content += "<all_global_variables>";
            for(int i = 0;i<static_cast<int>(global_variables_values().size());i++) {
                global_variables_content += name() + std::to_string(i + total_file_number) + ".sdrf";
                if(i != static_cast<int>(global_variables_values().size()) - 1) global_variables_content += ";";
            }

            // Create each files
            int i = 0;
            for(std::map<std::string, std::string>::iterator it = global_variables_values().begin();it!=global_variables_values().end();it++) {
                std::string file_path = name() + std::to_string(i + total_file_number) + ".sdrf";
                __save_file(path, file_path, it->first + ";" + it->second); i++;
            } total_file_number += global_variables_values().size();
        }

        // Create the .sdr file
        std::string config_file = "<name>" + name() + "<version>SDA 0.2<pattern_path>" + attached_pattern()->path() + files_content + global_variables_content;
        __save_file(path, name() + ".sdr", config_file);

        return true;
    }

    // Returns the sorted first path
    std::shared_ptr<std::vector<std::shared_ptr<Replica_File>>> Replica_Project::replica_files_first_sorted_by_path() {
        std::shared_ptr<std::vector<std::shared_ptr<Replica_File>>> to_return = std::make_shared<std::vector<std::shared_ptr<Replica_File>>>();
        std::shared_ptr<std::vector<std::shared_ptr<Replica_File>>> files = replica_files_sorted_by_path();
        std::vector<std::string> to_return_path = std::vector<std::string>();

        // Get each path
        for(int i = 0;i<static_cast<int>(files.get()->size());i++) {
            std::string& current_path = files.get()->at(i)->internal_path;
            std::vector<std::string> cutted = cut_path(current_path);
            bool contains = false;
            for(int j = 0;j<static_cast<int>(to_return_path.size());j++) {if(to_return_path[j] == cutted[0]){contains = true;break;}}
            if(contains) {
                to_return.get()->push_back(files.get()->at(i));
                to_return_path.push_back(cutted[0]);
            }
        }

        // Function to indicate how to sort the paths
        struct { bool operator()(const std::shared_ptr<Replica_File>& a, const std::shared_ptr<Replica_File>& b) const { return a.get()->internal_path < b.get()->internal_path; } } sorter;
        std::sort(to_return.get()->begin(), to_return.get()->end(), sorter);
        return to_return;
    }

    // Returns the sorted replica files by path
    std::shared_ptr<std::vector<std::shared_ptr<Replica_File>>> Replica_Project::replica_files_sorted_by_path() {
        std::shared_ptr<std::vector<std::shared_ptr<Replica_File>>> to_return = std::make_shared<std::vector<std::shared_ptr<Replica_File>>>();
        for(int i = 0;i<static_cast<int>(a_replica_files.size());i++) { to_return.get()->push_back(a_replica_files[i]); }

        // Function to indicate how to sort the files
        struct {
            bool operator()(const std::shared_ptr<Replica_File>& a, const std::shared_ptr<Replica_File>& b) const { return a.get()->internal_path < b.get()->internal_path; }
        } sorter;
        std::sort(to_return.get()->begin(), to_return.get()->end(), sorter);
        return to_return;
    }
}
