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

#include <scls_foundation.h>

#define VARIABLE_START std::string("<*-")
#define VARIABLE_END std::string("-*>")

// Use of the "scls" namespace to be more easily usable
namespace scls {

    // Returns a string cutted by ignoring quote
    std::vector<std::string> cut_string_out_quotes(std::string string, std::string cut, bool erase_blank = false, bool erase_last_if_blank = true);

    struct Text_Pattern_Variable {
        // Struct representing a variable in a text pattern
        // Content if the variable
        std::string content = "";
        // Start of a line if a break of line occurs
        std::string line_start = "";
        // Name of the variable
        std::string name = "";
    };

    // Know easily if a std::vector<Text_Pattern_Variable> contains a variable by name or not
    inline bool _contains_pattern_variable_by_name(const std::vector<Text_Pattern_Variable>& to_test, std::string variable_name) {
        for(int i = 0;i<static_cast<int>(to_test.size());i++) {
            if(to_test[i].name == variable_name) return true;
        }
        return false;
    };

    class Text_Pattern {
        // Class representing a pattern of a text in a SCLS Documentalist project
    public:
        // Most basic Text_Pattern constructor
        Text_Pattern(std::string name, std::string base_text, Text_Pattern* parent = 0);
        // Text_Pattern destructor
        ~Text_Pattern();

        // Return the entire text of the pattern
        std::string text() const;
        // Create a new children to the pattern
        Text_Pattern* new_pattern(std::string name, std::string base_text);

        // Getters and setters (ONLY WITHOUT ATTRIBUTES)
        inline void add_child(Text_Pattern* child) {
            if(!contains_children_by_name(child->name())) { a_children.push_back(child); return; }
            print("Warning", "SCLS Documentalist Text Pattern", "The text pattern \"" + name() + "\" where you want to add the child \"" + child->name() + "\" already has that child.");
        };
        inline bool contains_children(Text_Pattern* child) {
            for(int i = 0;i<static_cast<int>(a_children.size());i++) {
                if(a_children[i] == child) return true;
            }
            return false;
        };
        inline bool contains_children_by_name(std::string pattern_name) {
            for(int i = 0;i<static_cast<int>(a_children.size());i++) {
                if(a_children[i]->name() == pattern_name) return true;
            }
            return false;
        };
        inline bool contains_global_variable(std::string variable_name)  {return global_variable(variable_name) != "";};
        inline std::string global_variable(std::string variable_name) {for(std::map<std::string, std::string>::iterator it = a_global_variables.begin();it!=a_global_variables.end();it++){if(it->first == variable_name){return it->second;}}return "";};
        std::vector<Text_Pattern_Variable> needed_variables();

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::string base_text() const {return a_base_text;};
        inline std::string children_separation() const {return a_children_separation;};
        inline std::string default_line_start() const {return a_default_line_start;};
        inline std::string end_separation() const {return a_end_separation;};
        inline std::map<std::string, std::string>& global_variables() {return a_global_variables;};
        inline std::string name() const {return a_name;};
        inline void set_children_separation(std::string new_children_separation) {a_children_separation = new_children_separation;};
        inline void set_default_line_start(std::string new_default_line_start) {
            a_default_line_start = new_default_line_start;
            for(int i = 0;i<static_cast<int>(a_children.size());i++) a_children[i]->set_default_line_start(new_default_line_start);
        };
        inline void set_end_separation(std::string new_end_separation) {a_end_separation = new_end_separation;};
        inline void set_global_variable(std::string variable_name, std::string variable_content) { a_global_variables[variable_name] = variable_content; };
        inline void set_start_separation(std::string new_start_separation) {a_start_separation = new_start_separation;};
        inline std::string start_separation() const {return a_start_separation;};
        inline unsigned int text_position() const {return a_text_position;};
    private:
        // Base text
        std::string a_base_text = "";
        // Children of this children
        std::vector<Text_Pattern*> a_children = std::vector<Text_Pattern*>();
        // String of the separation of the children
        std::string a_children_separation = "";
        // Default line_start value of the pattern variable in the text
        std::string a_default_line_start = "";
        // String of the separation at the end of the pattern
        std::string a_end_separation = "";
        // Value of each defined global variables
        std::map<std::string, std::string> a_global_variables = std::map<std::string, std::string>();
        // Name of the pattern
        std::string a_name = "";
        // Parent of this piece
        Text_Pattern* const a_parent;
        // String of the separation at the start of the pattern
        std::string a_start_separation = "";
        // Position of the text in the hierarchy
        unsigned int a_text_position = 0;
    };

    class Text_Piece {
        // Class representing a text of pieces in a SCLS Documentalist project
    public:
        // Most basic Text_Piece constructor
        Text_Piece(std::string name, Text_Pattern& pattern);
        // Text_Piece destructor
        virtual ~Text_Piece();

        // Save the text in a file
        void save_as(std::string path);

        // Return the text "text_to_format" well formatted
        std::string text(std::string text_to_format);
        // Return the text well formatted
        std::string text();

        // Getters and setters (ONLY WITHOUT ATTRIBUTES)
        inline bool contains_variable_by_name(std::string variable_name) { return _contains_pattern_variable_by_name(*a_variables, variable_name);};
        inline void set_variable(std::string variable_name, std::string content) {
            if(!contains_variable_by_name(variable_name)) {
                print("Warning", "SCLS Documentalist Text Piece", "The text piece where you want to set a variable \"" + variable_name + "\" does not have the variable.");
                return;
            }

            variable(variable_name)->content = content;
        };

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::map<std::string, Text_Piece*>& children() {return a_children;};
        inline std::string name() const {return a_name;};
        inline Text_Pattern& pattern() const {return a_pattern;};
        inline Text_Pattern_Variable* variable(std::string variable_name) {
            for(int i = 0;i<static_cast<int>(variables().size());i++) {
                if(variables()[i].name == variable_name) return &variables()[i];
            }

            print("Warning", "SCLS Documentalist Text Piece", "The text piece where you want to get a variable \"" + variable_name + "\" does not have the variable.");
            return 0;
        };
        inline std::vector<Text_Pattern_Variable>& variables() {return *a_variables;};
    private:
        // Children of this text
        std::map<std::string, Text_Piece*> a_children = std::map<std::string, Text_Piece*>();
        // Name of the text piece
        std::string a_name = "";
        // Pattern linked to the text
        Text_Pattern& a_pattern;
        // Variable in the piece
        std::vector<Text_Pattern_Variable>* a_variables = 0;
    };
}

#endif
