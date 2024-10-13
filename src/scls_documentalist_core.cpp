//******************
//
// scls_documentalist_test -> headers/scls_documentalist_core.h
//
//******************
//
// scls_documentalist_core description
//
// SCLS Documentalist "Agatha" is a part of the Aster System SCLS project.
// This part is made to easily document C++ files.
// It is made for SCLS, but you can still use it in your project. However, it may be a little less adapted.
// This part is named after one of the most famous author, Agatha Christie.
//
//******************
//
// headers/scls_documentalist_core.cpp description
//
// This file contains the source code of headers/scls_documentalist_core.h.
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

#include "../headers/scls_documentalist_core.h"

// Use of the "scls" namespace to be more easily usable
namespace scls {

    // Contains if a vector of std::shared_ptr<Pattern_Variable> contains a certain Pattern_Variable
    bool __contains_variable(std::vector<std::shared_ptr<Pattern_Variable>>& variables, std::shared_ptr<Pattern_Variable> variable) {
        for(int i = 0;i<static_cast<int>(variables.size());i++) {
            if(variables[i].get() == variable.get()) return true;
        }
        return false;
    }
    bool __contains_variable(std::vector<Pattern_Variable>& to_test, std::string variable_name) {
        for(int i = 0;i<static_cast<int>(to_test.size());i++) {
            if(to_test[i].name == variable_name) return true;
        }
        return false;
    };

    // Analyse a pattern variable
    std::shared_ptr<Pattern_Variable> __analyse_pattern_variable(std::string content, std::vector<std::shared_ptr<Pattern_Variable_List>>* lists) {
        // Analyse the variable
        bool global = false;
        bool listed = false;
        std::string name = "";
        bool path_to_root = false;
        std::vector<std::string> variable_attributes = cut_balise_by_attributes(content);
        for(int i = 0;i<static_cast<int>(variable_attributes.size());i++) {
            if(variable_attributes[i] == "global") {
                // The variable is global
                global = true;
            }
            else if(variable_attributes[i] == "path_to_root") {
                // The variable should be the path to the root
                path_to_root = true;
            }
            else if(i == 0) {
                // The name of the variable
                name = variable_attributes[i];
                if(name.size() > 2 && name[name.size() - 2] == '[' && name[name.size() - 1] == ']') listed = true;
            }
        }

        // Create the variable
        std::shared_ptr<Pattern_Variable> new_variable;
        std::shared_ptr<Pattern_Variable_List> new_variable_list;
        if(listed) {
            new_variable_list = std::make_shared<Pattern_Variable_List>();
            new_variable = new_variable_list;
            if(lists != 0) lists->push_back(new_variable_list);
        } else {
            new_variable = std::make_shared<Pattern_Variable>();
        }
        // Configure the variable
        new_variable.get()->content = content;
        new_variable.get()->global = global;
        new_variable.get()->name = name;
        new_variable.get()->path_to_root = path_to_root;
        return new_variable;
    }

    // Parse a pattern with pre-defined datas
    void __parse_pattern(String used_text, std::shared_ptr<Pattern_Variable> parent_variable, std::vector<std::shared_ptr<Pattern_Variable>>& used_global_variables, std::vector<std::shared_ptr<Pattern_Variable>>& used_global_variables_main, std::vector<std::shared_ptr<Pattern_Variable>>& used_variables, bool first_analyse) {
        // Cut the text
        if(first_analyse){used_global_variables.clear(); used_variables.clear();}
        std::vector<_Text_Balise_Part> cutted = used_text.formatted_as_plain_text().cut_by_balise();

        // Analyse each balises
        std::vector<std::shared_ptr<Pattern_Variable_List>> variable_lists;
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].content.size() > 0 && cutted[i].content[0] == '<') {
                // The part is a balise
                std::string current_balise = formatted_balise(cutted[i].content);
                std::string current_balise_name = balise_name(current_balise);
                // Remove the < and >
                current_balise = current_balise.substr(1, current_balise.size() - 2);
                if(current_balise_name == "scls_var" && current_balise[0] != '/') {
                    // The part is a SCLS variable
                    std::shared_ptr<Pattern_Variable> new_variable = __analyse_pattern_variable(current_balise, &variable_lists);

                    // The variable needs a content
                    std::string variable_content = "";
                    if(new_variable.get()->listed()) {
                        int level = 1; i++;
                        while(i<static_cast<int>(cutted.size())) {
                            if(cutted[i].content.size() > 0 && cutted[i].content[0] == '<') {
                                current_balise = formatted_balise(cutted[i].content);
                                current_balise_name = balise_name(current_balise);
                                // Remove the < and >
                                current_balise = current_balise.substr(1, current_balise.size() - 2);
                                if(current_balise_name == "scls_var") {
                                    if(current_balise[0] == '/') level--;
                                    if(level == 0) break;
                                }
                            }
                            variable_content += cutted[i].content;
                            i++;
                        }
                        new_variable.get()->content = variable_content;
                    }

                    // Add the variable
                    new_variable.get()->parent_variable = parent_variable;
                    if(new_variable.get()->global) {
                        if(!__contains_variable(used_global_variables_main, new_variable)) {
                            used_variables.push_back(new_variable);
                            used_global_variables.push_back(new_variable);
                            if(&used_global_variables != &used_global_variables_main) used_global_variables_main.push_back(new_variable);
                        }
                    }
                    else { used_variables.push_back(new_variable); }
                } else {__parse_pattern(current_balise, parent_variable, used_global_variables, used_global_variables_main, used_variables, false);}
            }
        }

        if(first_analyse) {
            // Analyse each sub-lists
            for(int i = 0;i<static_cast<int>(variable_lists.size());i++) {
                std::shared_ptr<Pattern_Variable_List> variable = variable_lists[i];
                __parse_pattern(variable.get()->content, variable, variable.get()->global_variables, used_global_variables, variable.get()->variables);
            }
        }
    }

    // Most basic _Text_Pattern_Core constructor
    Text_Pattern::Text_Pattern(String name, String base_text) : a_name(name), a_base_text(base_text) {}

    // Text_Pattern destructor
    Text_Pattern::~Text_Pattern() {}
}

#endif
