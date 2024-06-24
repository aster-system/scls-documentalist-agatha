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
    // Analyse a pattern variable
    Pattern_Variable analyse_pattern_variable(std::string content) {
        // The part is a SCLS variable
        Pattern_Variable new_variable;
        new_variable.content = content;

        // Analyse the variable
        bool global = false;
        std::vector<std::string> cutted_variable = cut_string(content, " ");
        for(int i = 1;i<static_cast<int>(cutted_variable.size());i++) {
            if(cutted_variable[i] == "global") {
                // The variable is global
                global = true;
            }
            else if(i == 1) {
                // The name of the variable
                new_variable.name = cutted_variable[i];
            }
        }

        new_variable.global = global;
        return new_variable;
    }

    // Most basic _Text_Pattern_Core constructor
    Text_Pattern::Text_Pattern(String name, String base_text) : a_name(name), a_base_text(base_text) {

    }

    // Parse the text in the pattern
    void Text_Pattern::parse_pattern() {
        // Cut the text
        global_variables().clear(); variables().clear();
        std::vector<_Text_Balise_Part> cutted = base_text().formatted_as_plain_text().cut_by_balise();

        // Analyse each balises
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].content.size() > 0 && cutted[i].content[0] == '<') {
                // The part is a balise
                std::string current_balise = formatted_balise(cutted[i].content);
                std::string current_balise_name = balise_name(current_balise);
                // Remove the < and >
                current_balise = current_balise.substr(1, current_balise.size() - 2);
                if(current_balise_name == "scls_var") {
                    // The part is a SCLS variable
                    std::shared_ptr<Pattern_Variable> new_variable = std::make_shared<Pattern_Variable>(analyse_pattern_variable(current_balise));
                    variables().push_back(new_variable);
                    if(new_variable.get()->global) global_variables().push_back(new_variable);
                }
            }
        }
    }

    // Text_Pattern destructor
    Text_Pattern::~Text_Pattern() {

    }
}

#endif
