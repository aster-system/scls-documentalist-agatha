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

#define SCLS_DOCUMENTALIST_ERROR_CUTTER std::string("=")
#define SCLS_DOCUMENTALIST_FORCED_USER_DEFINED_VARIABLE_ERROR std::string("-_\"{<;>" )
#define VARIABLE_START std::string("<*-")
#define VARIABLE_END std::string("-*>")

// Use of the "scls" namespace to be more easily usable
namespace scls {

    // Return if a string contains an another string out of quotes
    bool contains_out_of_quotes(std::string str, std::string part);

    // Returns a string cutted by ignoring quote
    std::vector<std::string> cut_string_out_quotes(std::string string, std::string cut, bool erase_blank = false, bool erase_last_if_blank = true);

    // Unformat a SCLS Documentalist pattern settings
    std::string unformat_pattern_settings(std::string pattern_settings);

    struct Text_Pattern_Base_Variable {
        // Struct representing a variable in a text pattern
        // Content if the variable
        std::string content = "";
        // Start of a line if a break of line occurs
        std::string line_start = "";
        // Name of the variable
        std::string name = "";
    };

    // Know easily if a std::vector<Text_Pattern_Base_Variable> contains a variable by name or not
    inline bool _contains_pattern_variable_by_name(std::vector<Text_Pattern_Base_Variable>& to_test, std::string variable_name) {
        for(int i = 0;i<static_cast<int>(to_test.size());i++) {
            if(to_test[i].name == variable_name) return true;
        }
        return false;
    };

    class _Text_Pattern_Core {
        // Class representing a core of a pattern of a text in a SCLS Documentalist project
    public:
        // Most basic Text_Pattern constructor
        _Text_Pattern_Core(std::string name, std::string base_text, _Text_Pattern_Core* parent = 0);
        // Text_Pattern destructor
        virtual ~_Text_Pattern_Core();

        // Getters and setters (ONLY WITHOUT ATTRIBUTES)
        inline void add_child(_Text_Pattern_Core* child) {
            if(!contains_children_by_name(child->name())) { a_children.push_back(child); return; }
            print("Warning", "SCLS Documentalist Text Pattern", "The text pattern \"" + name() + "\" where you want to add the child \"" + child->name() + "\" already has that child.");
        };
        inline void add_forced_user_defined_variable(std::string variable_name) {
            if(!contains_forced_user_defined_variable(variable_name)) {
                a_forced_user_defined_variables.push_back(variable_name);
                return;
            }
            print("Warning", "SCLS Documentalist pattern \"" + name() + "\"", "The variable \"" + variable_name + "\" you want to set as forced user defined is already forced.");
            return;
        };
        inline _Text_Pattern_Core* _child(std::string pattern_name) {
            for(int i = 0;i<static_cast<int>(a_children.size());i++) {
                if(a_children[i]->name() == pattern_name) return a_children[i];
            }

            for(int i = 0;i<static_cast<int>(a_children.size());i++) {
                _Text_Pattern_Core* result = a_children[i]->_child(pattern_name);
                if(result != 0) return result;
            }
            return 0;
        }
        inline _Text_Pattern_Core* child(std::string pattern_name) {
            _Text_Pattern_Core* final_child = _child(pattern_name);
            if(final_child != 0) return final_child;

            scls::print("Warning", "SCLS Documentalist Pattern \"" + name() + "\"", "This pattern does not contains the child \"" + pattern_name + "\" you want to get.");
            return 0;
        }
        inline bool contains_children(_Text_Pattern_Core* child) {
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
        inline bool contains_global_variable(std::string variable_name)  {return global_variable(variable_name).size() > 0;};
        inline bool contains_forced_user_defined_variable(std::string variable_name, bool hierarchical_variables = false, bool hierarchical = false) {
            std::vector<std::string> to_analyse = forced_user_defined_variables(hierarchical_variables);
            for(int i = 0;i<static_cast<int>(to_analyse.size());i++) { if(to_analyse[i] == variable_name) return true;}
            if(hierarchical) {
                bool to_return = false;
                for(int i = 0;i<static_cast<int>(children().size()) && !to_return;i++) to_return = to_return || children()[i]->contains_forced_user_defined_variable(variable_name, hierarchical_variables, true);
                return to_return;
            }
            return false;
        }
        inline int forced_user_defined_variable_hierarchy(std::string variable_name) {
            std::vector<std::string> to_analyse = forced_user_defined_variables();
            for(int i = 0;i<static_cast<int>(to_analyse.size());i++) { if(to_analyse[i] == variable_name) return 0;}
            if(a_parent != 0) {
                int result = a_parent->forced_user_defined_variable_hierarchy(variable_name);
                if(result != -1) return result + 1;
            }
            return -1;
        }
        inline std::string global_variable(std::string variable_name) {for(std::map<std::string, std::string>::iterator it = a_global_variables.begin();it!=a_global_variables.end();it++){if(it->first == variable_name){return it->second;}}return "";};
        std::vector<Text_Pattern_Base_Variable> needed_variables();

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::string base_text() const {return a_base_text;};
        inline std::vector<_Text_Pattern_Core*>& children() {return a_children;};
        inline std::string children_separation() const {return a_children_separation;};
        inline std::string default_line_start() const {return a_default_line_start;};
        inline std::string end_separation() const {return a_end_separation;};
        inline std::vector<std::string> forced_user_defined_variables(bool hierarchical = false) {
            if(hierarchical) {
                std::vector<std::string> to_return = a_forced_user_defined_variables;
                if(a_parent != 0) {
                    std::vector<std::string> to_add = a_parent->forced_user_defined_variables(true);
                    for(int i = 0;i<static_cast<int>(to_add.size());i++) {
                        to_return.push_back(to_add[i]);
                    }
                }
                return to_return;
            }
            return a_forced_user_defined_variables;
        };
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
        std::vector<_Text_Pattern_Core*> a_children = std::vector<_Text_Pattern_Core*>();
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
        // List of the name of every needed variables
        std::vector<std::string> a_forced_user_defined_variables = std::vector<std::string>();
        // Parent of this piece
        _Text_Pattern_Core* const a_parent;
        // String of the separation at the start of the pattern
        std::string a_start_separation = "";
        // Position of the text in the hierarchy
        unsigned int a_text_position = 0;
    };

    class Text_Pattern_Handler {
        // Class representing a simple handler of a group of _Text_Pattern_Core
    public:
        // Most simple Text_Pattern_Handler constructor
        Text_Pattern_Handler(std::string name):a_name(name){};

        // Add a pattern to the group
        inline void add_pattern(_Text_Pattern_Core* pattern_to_test) {
            if(!contains_pattern(pattern_to_test)) a_patterns.push_back(pattern_to_test);
            else print("Warning", "Text_Pattern_Handler \"" + name() + "\"", "The pattern you want to add is already in the handler.");
        };
        // Returns if the handler contains a pattern
        inline bool contains_pattern(_Text_Pattern_Core* pattern_to_test){for(int i=0;i<static_cast<int>(patterns().size());i++){if(patterns()[i]==pattern_to_test){return true;}}return false;};

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::string name() {return a_name;};
        inline std::vector<_Text_Pattern_Core*>& patterns(){return a_patterns;};
    private:
        // Name of the handler
        std::string a_name = "";
        // List of each _Text_Pattern_Core
        std::vector<_Text_Pattern_Core*> a_patterns = std::vector<_Text_Pattern_Core*>();
    };

    class Text_Pattern : public _Text_Pattern_Core {
        // Class representing a complete pattern of a text in a SCLS Documentalist project
    public:
        // Most basic Text_Pattern constructor
        Text_Pattern(std::string name, std::string base_text, Text_Pattern* parent = 0);
        // Text_Pattern destructor
        virtual ~Text_Pattern();

        // Returns if the pattern contains a group or not
        inline bool contains_group(std::string group_name) {for(std::map<std::string, Text_Pattern_Handler*>::iterator it = groups().begin();it!=groups().end();it++){if(it->first == group_name){return true;}}return false;};
        // Returns a group in the pattern
        Text_Pattern_Handler* group(std::string group_name) {for(std::map<std::string, Text_Pattern_Handler*>::iterator it = groups().begin();it!=groups().end();it++){if(it->first == group_name){return it->second;}}return 0;};
        // Create a new children to the pattern
        Text_Pattern* new_pattern(std::string name, std::string base_text);

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::map<std::string, Text_Pattern_Handler*>& groups() {return a_groups;};
    private:
        // Sub groups in the pattern
        std::map<std::string, Text_Pattern_Handler*> a_groups = std::map<std::string, Text_Pattern_Handler*>();
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

        // Return the text well formatted
        std::string text_with_pattern(std::string id, std::vector<int> iterations);
        // Return the text well formatted
        std::string text_with_pattern(std::string id);
        // Return the text well formatted
        std::string text();

        // Getters and setters (ONLY WITHOUT ATTRIBUTES)
        inline Text_Pattern_Base_Variable* base_variable(std::string variable_name) {
            for(int i = 0;i<static_cast<int>(base_variables().size());i++) {
                if(base_variables()[i].name == variable_name)
                    return &(base_variables()[i]);
            }

            print("Warning", "SCLS Documentalist Text Piece \"" + name() + "\"", "This text piece where you want to get a base variable \"" + variable_name + "\" does not have the variable.");
            return 0;
        };
        inline bool contains_base_variable_by_name(std::string variable_name) {
            for(int i = 0;i<static_cast<int>(base_variables().size());i++) {
                if(base_variables()[i].name == variable_name) return true;
            }
            return false;
        };
        inline bool contains_patterns_iterations(std::string pattern_name) {
            for(std::map<std::string, unsigned int>::iterator it = patterns_iterations().begin();it!=patterns_iterations().end();it++) {
                if(it->first == pattern_name) return true;
            }
            return false;
        }
        inline bool contains_patterns_used(std::string pattern_name) {
            for(std::map<std::string, bool>::iterator it = patterns_used().begin();it!=patterns_used().end();it++) {
                if(it->first == pattern_name) return true;
            }
            return false;
        }
        inline bool contains_variable_by_name(std::string variable_name) {
            for(std::map<std::string, Text_Pattern_Base_Variable>::iterator it = variables().begin();it!=variables().end();it++) {
                if(it->first == variable_name) return true;
            }
            return false;
        };
        inline _Text_Pattern_Core* pattern(std::string pattern_name) {
            if(a_pattern.name() == pattern_name)return &a_pattern;
            _Text_Pattern_Core* to_return = a_pattern.child(pattern_name);

            if(to_return == 0) {
                print("Warning", "SCLS Documentalist Piece \"" + name() + "\"", "This piece does not contains the pattern \"" + pattern_name + "\".");
                return 0;
            }
            return a_pattern.child(pattern_name);
        };
        inline unsigned int pattern_iterations(std::string pattern_name) {
            for(std::map<std::string, unsigned int>::iterator it = patterns_iterations().begin();it!=patterns_iterations().end();it++) {
                if(it->first == pattern_name) return it->second;
            }
            return 1;
        };
        inline bool pattern_used(std::string pattern_name) {
            for(std::map<std::string, bool>::iterator it = patterns_used().begin();it!=patterns_used().end();it++) {
                if(it->first == pattern_name) return it->second;
            }
            return true;
        };
        inline void set_pattern_iterations_number(std::string pattern_name, unsigned int iterations_number) {
            a_patterns_iterations[pattern_name] = iterations_number;
        }
        inline void set_variable(std::string variable_name, std::string offset, std::string content) {
            if(!contains_base_variable_by_name(variable_name)) {
                print("Warning", "SCLS Documentalist Text Piece \"" + name() + "\"", "This text piece where you want to set a variable \"" + variable_name + "\" does not have the variable.");
                return;
            }

            std::string final_variable_name = variable_name;
            if(final_variable_name[final_variable_name.size() - 1] == ']') {
                final_variable_name = cut_string(variable_name, "[")[0];
            }
            final_variable_name += offset;

            if(!contains_variable_by_name(final_variable_name)) {
                Text_Pattern_Base_Variable* variable_to_copy = base_variable(variable_name);
                Text_Pattern_Base_Variable final_variable;
                final_variable.content = variable_to_copy->content;
                final_variable.line_start = variable_to_copy->line_start;
                final_variable.name = variable_to_copy->name;
                variables()[final_variable_name] = final_variable;
            }

            variables()[final_variable_name].content = content;
        };
        inline void set_variable(std::string variable_name, std::string content) {
            set_variable(variable_name, "[0]", content);
        };
        inline Text_Pattern_Base_Variable* variable(std::string variable_name) {
            for(std::map<std::string, Text_Pattern_Base_Variable>::iterator it = variables().begin();it!=variables().end();it++) {
                if(it->first == variable_name) return &(it->second);
            }

            print("Warning", "SCLS Documentalist Text Piece \"" + name() + "\"", "The text piece where you want to get a variable \"" + variable_name + "\" does not have the variable.");
            return 0;
        };
        inline Text_Pattern_Base_Variable* variable(std::string variable_name, bool print_error) {
            for(std::map<std::string, Text_Pattern_Base_Variable>::iterator it = variables().begin();it!=variables().end();it++) {
                if(it->first == variable_name) return &(it->second);
            }

            if(print_error)print("Warning", "SCLS Documentalist Text Piece \"" + name() + "\"", "The text piece where you want to get a variable \"" + variable_name + "\" does not have the variable.");
            return 0;
        };

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::vector<Text_Pattern_Base_Variable>& base_variables() {return a_base_variables;};
        inline std::map<std::string, Text_Piece*>& children() {return a_children;};
        inline std::string id() {return std::to_string(a_id);};
        inline std::string name() const {return a_name;};
        inline Text_Pattern& pattern() {return a_pattern;};
        inline std::map<std::string, unsigned int>& patterns_iterations() {return a_patterns_iterations;};
        inline std::map<std::string, bool>& patterns_used() {return a_patterns_used;};
        inline std::map<std::string, Text_Pattern_Base_Variable>& variables() {return a_variables;};
    private:
        // Base variable in the piece
        std::vector<Text_Pattern_Base_Variable> a_base_variables = std::vector<Text_Pattern_Base_Variable>();
        // Children of this text
        std::map<std::string, Text_Piece*> a_children = std::map<std::string, Text_Piece*>();
        // ID of the piece
        const unsigned int a_id = 0;
        // Name of the text piece
        std::string a_name = "";
        // Pattern linked to the text
        Text_Pattern& a_pattern;
        // Iteration characteristic of a pattern in the piece by name
        std::map<std::string, unsigned int> a_patterns_iterations = std::map<std::string, unsigned int>();
        // Used characteristic of a pattern in the piece by name
        std::map<std::string, bool> a_patterns_used = std::map<std::string, bool>();
        // Variable in the piece
        std::map<std::string, Text_Pattern_Base_Variable> a_variables = std::map<std::string, Text_Pattern_Base_Variable>();
    };
}

#endif
