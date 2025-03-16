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
// headers/scls_documentalist_core.h description
//
// This file contains the core of SCLS Documentalist.
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

#ifndef SCLS_DOCUMENTALIST_CORE
#define SCLS_DOCUMENTALIST_CORE

// "scls_foundation.h" -> File containing the core of SCLS.
#ifdef __ASTER_DEV
#include "../../scls-foundation-leonhard/scls_foundation.h"
#else
#include <scls_foundation.h>
#endif // __ASTER_DEV
#include <algorithm>

// Keyword to define a variable in a balise
#ifndef SCLS_DOCUMENTALIST_VARIABLE_KEYWORD
#define SCLS_DOCUMENTALIST_VARIABLE_KEYWORD "var"
#endif // SCLS_DOCUMENTALIST_VARIABLE_KEYWORD

#define SCLS_DOCUMENTALIST_ERROR_CUTTER std::string("=")
#define SCLS_DOCUMENTALIST_FORCED_USER_DEFINED_VARIABLE_ERROR std::string("-_\"{<;>" )

// Use of the "scls" namespace to be more easily usable
namespace scls {

    struct Pattern_Variable {
        // Struct representing a variable in a text pattern
        // Content if the variable has a content
        std::string content = "";
        // If the variable is global or not
        bool global = false;
        // Start of a line if a break of line occurs
        std::string line_start = "";
        // If the variable is listed or not
        virtual bool listed() const {return false;};
        // Name of the variable
        std::string name = "";
        // Parent variable of this variable
        std::shared_ptr<Pattern_Variable> parent_variable;

        // If the variable is the path to the root or not
        bool path_to_root = false;
    };

    struct Pattern_Variable_List : public Pattern_Variable {
        // Struct representing a list of pattern variables in a text pattern
        // If the variable is listed or not
        bool listed() const override {return true;};
        // Returns a variable list by its name
        inline Pattern_Variable_List* variable_list_by_name(std::string variable_name) const {
            for(int i = 0;i<static_cast<int>(variables.size());i++) {
                if(variables.at(i).get()->name == variable_name && variables.at(i).get()->listed()) return reinterpret_cast<Pattern_Variable_List*>(variables.at(i).get());
            }
            return 0;
        };

        // Global variables loaded
        std::vector<std::shared_ptr<Pattern_Variable>> global_variables;
        // Variables loaded
        std::vector<std::shared_ptr<Pattern_Variable>> variables;
    };

    // Contains if a vector of std::shared_ptr<Pattern_Variable> contains a certain Pattern_Variable
    bool __contains_variable(std::vector<std::shared_ptr<Pattern_Variable>>& variables, std::shared_ptr<Pattern_Variable> variable);
    bool __contains_variable(std::vector<Pattern_Variable>& to_test, std::string variable_name);

    // Analyse a pattern variable
    std::shared_ptr<Pattern_Variable> __analyse_pattern_variable(std::string content, std::vector<std::shared_ptr<Pattern_Variable_List>>* lists);

    // Parse a pattern with pre-defined datas
    void __parse_pattern(String used_text, std::shared_ptr<Pattern_Variable> parent_variable, std::vector<std::shared_ptr<Pattern_Variable>>& used_global_variables, std::vector<std::shared_ptr<Pattern_Variable>>& used_global_variables_main, std::vector<std::shared_ptr<Pattern_Variable>>& used_variables, bool first_analyse = true);

    class Text_Pattern {
        // Class representing a complete pattern of a text in a SCLS Documentalist project
    public:
        // Most basic Text_Pattern constructor
        Text_Pattern(String name, String base_text);
        // Text_Pattern destructor
        virtual ~Text_Pattern();

        // Parse the text in the pattern
        void parse_pattern(){__parse_pattern(base_text(), std::shared_ptr<Pattern_Variable>(), a_global_variables, a_global_variables, a_variables);};
        void parse_pattern_variable_list(std::shared_ptr<Pattern_Variable_List> variable) {__parse_pattern(variable.get()->content, std::shared_ptr<Pattern_Variable>(), variable.get()->global_variables, a_global_variables, variable.get()->variables);};

        // Returns a variable by its name
        inline std::shared_ptr<Pattern_Variable> variable_by_name(std::string variable_name) const {for(int i = 0;i<static_cast<int>(a_variables.size());i++) {if(a_variables.at(i).get()->name == variable_name) return a_variables.at(i);}return std::shared_ptr<Pattern_Variable>();};
        inline std::shared_ptr<Pattern_Variable> variable_in_list_by_name(std::string list_name, std::string variable_name) const {Pattern_Variable_List* used_list = variable_list_by_name(list_name); if(used_list == 0) return std::shared_ptr<Pattern_Variable>();for(int i = 0;i<static_cast<int>(used_list->variables.size());i++) {if(used_list->variables.at(i).get()->name == variable_name) return used_list->variables.at(i);} return std::shared_ptr<Pattern_Variable>();};
        inline Pattern_Variable_List* variable_list_by_name(std::string variable_name) const {
            for(int i = 0;i<static_cast<int>(a_variables.size());i++) {
                if(a_variables.at(i).get()->name == variable_name && a_variables.at(i).get()->listed()) return reinterpret_cast<Pattern_Variable_List*>(a_variables.at(i).get());
            }
            return 0;
        };

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline String base_text() const {return a_base_text;};
        inline std::vector<std::shared_ptr<Pattern_Variable>>& global_variables() {return a_global_variables;};
        inline String name() const {return a_name;};
        inline void set_base_text(String new_base_test) {a_base_text = new_base_test;};
        inline std::vector<std::shared_ptr<Pattern_Variable>>& variables() {return a_variables;};
    private:

        // Base text
        String a_base_text;
        // Name of the pattern
        String a_name;

        // Global variables loaded
        std::vector<std::shared_ptr<Pattern_Variable>> a_global_variables;
        // Variables loaded
        std::vector<std::shared_ptr<Pattern_Variable>> a_variables;
    };
}

#endif
