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

    // Number of the pieces created
    static unsigned int _piece_number;

    // Returns a string cutted by ignoring quote
    std::vector<std::string> cut_string_out_quotes(std::string string, std::string cut, bool erase_blank, bool erase_last_if_blank) {
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

    // Most basic _Text_Pattern_Core constructor
    _Text_Pattern_Core::_Text_Pattern_Core(std::string name, std::string base_text, _Text_Pattern_Core* parent): a_base_text(base_text), a_name(name), a_parent(parent) {
        if(parent != 0)parent->add_child(this);
    }

    /*// Return the entire text of the pattern
    std::string _Text_Pattern_Core::text(std::string id, std::string offset) const {
        std::string pattern_text = child->text(id, offset + to_add_offset);
        std::string result = "";
        std::vector<std::string> cutted = cut_string_out_quotes(pattern_text, VARIABLE_START);
        result += cutted[0];
        for(int i = 1;i<static_cast<int>(cutted.size());i++) {
            std::vector<std::string> local_cutted = cut_string_out_quotes(cutted[i], VARIABLE_END, true, false);
            if(local_cutted.size() < 2) {
                print("Warning", "SCLS Documentalist Text Piece", "The text pattern \"" + name() + "\" where you want to get the text is badly syntaxed.");
                return "";
            }

            std::string variable_name = local_cutted[0];
            if(variable_name.substr(variable_name.size() - 2, 2) == "[]") {
                variable_name = cut_string(variable_name, "[")[0];
                variable_name += offset + "[" + std::to_string(j) + "]";
            }
            variable_name = VARIABLE_START + variable_name + VARIABLE_END;
            result += variable_name;
            result += local_cutted[1];
        }
        to_return += result;
        if(i != a_children.size() - 1) to_return += children_separation();
    }
    if(i + 1 == text_position()) to_return += base_text();
    } //*/

    /*// Return the entire text of the pattern
    std::string _Text_Pattern_Core::text(std::string id) const {
        std::string to_return = "";

        to_return += start_separation();
        if(text_position() == 0) to_return += base_text();

        for(unsigned int i = 0;i<static_cast<unsigned int>(a_children.size());i++) {
            _Text_Pattern_Core* child = a_children[i];
            if(!child->used(id)) continue;

            unsigned int iterations = child->iteration_number(id);
            for(unsigned int j = 0;j<iterations;j++) {
                std::string to_add_offset = "[" + std::to_string(j) + "]";
                if(iterations <= 1) to_add_offset = "";
                std::string pattern_text = child->text(id, to_add_offset);
                std::string result = "";
                std::vector<std::string> cutted = cut_string_out_quotes(pattern_text, VARIABLE_START);
                result += cutted[0];
                for(int i = 1;i<static_cast<int>(cutted.size());i++) {
                    std::vector<std::string> local_cutted = cut_string_out_quotes(cutted[i], VARIABLE_END, true, false);
                    if(local_cutted.size() < 2) {
                        print("Warning", "SCLS Documentalist Text Piece", "The text pattern \"" + name() + "\" where you want to get the text is badly syntaxed.");
                        return "";
                    }

                    std::string variable_name = local_cutted[0];
                    if(variable_name.substr(variable_name.size() - 2, 2) == "[]") {
                        variable_name = cut_string(variable_name, "[")[0];
                        variable_name += to_add_offset;
                    }
                    variable_name = VARIABLE_START + variable_name + VARIABLE_END;
                    result += variable_name;
                    result += local_cutted[1];
                }
                to_return += result;
                if(i != a_children.size() - 1) to_return += children_separation();
            }
            if(i + 1 == text_position()) to_return += base_text();
        }
        to_return += end_separation();

        return to_return;
    } //*/

    // Returns the needed variable in the pattern
    std::vector<Text_Pattern_Base_Variable> _Text_Pattern_Core::needed_variables() {
        std::vector<Text_Pattern_Base_Variable> to_return = std::vector<Text_Pattern_Base_Variable>();
        std::vector<std::string> cutted = cut_string(base_text(), VARIABLE_START);

        for(int i = 1;i<static_cast<int>(cutted.size());i++) {
            std::string variable_name = cut_string(cutted[i], VARIABLE_END)[0];

            if(!_contains_pattern_variable_by_name(to_return, variable_name)) {
                Text_Pattern_Base_Variable variable;
                variable.line_start = default_line_start();
                variable.name = variable_name;

                if(contains_global_variable(variable_name)) {
                    variable.content = global_variable(variable_name);
                }

                to_return.push_back(variable);
            }
        }

        // Add children variables
        for(int i = 0;i<static_cast<int>(a_children.size());i++) {
            std::vector<Text_Pattern_Base_Variable> children_variables = a_children[i]->needed_variables();

            for(int i = 0;i<static_cast<int>(children_variables.size());i++) {
                if(!_contains_pattern_variable_by_name(to_return, children_variables[i].name)) {
                    Text_Pattern_Base_Variable variable;
                    variable.line_start = children_variables[i].line_start;
                    variable.name = children_variables[i].name;

                    if(contains_global_variable(children_variables[i].name)) {
                        variable.content = global_variable(children_variables[i].name);
                    }

                    to_return.push_back(variable);
                }
            }
        }

        return to_return;
    }

    // _Text_Pattern_Core destructor
    _Text_Pattern_Core::~_Text_Pattern_Core() {
        for(int i = 0;i<static_cast<int>(a_children.size());i++) {
            delete a_children[i]; a_children[i] = 0;
        }
        a_children.clear();
    }

    // Most basic _Text_Pattern_Core constructor
    Text_Pattern::Text_Pattern(std::string name, std::string base_text, Text_Pattern* parent) : _Text_Pattern_Core(name, base_text, reinterpret_cast<_Text_Pattern_Core*>(parent)) {

    }

    // Create a new children to the pattern
    Text_Pattern* Text_Pattern::new_pattern(std::string pattern_name, std::string base_text) {
        if(contains_children_by_name(pattern_name)) {
            print("Warning", "SCLS Documentalist Text Pattern", "The text pattern \"" + name() + "\" where you want to add a children \"" + pattern_name + "\" already has a children named like that.");
            return 0;
        }

        Text_Pattern* pattern = new Text_Pattern(pattern_name, base_text, this);
        pattern->set_default_line_start(default_line_start());
        return pattern;
    }

    // Text_Pattern destructor
    Text_Pattern::~Text_Pattern() {

    }

    // Most basic Text_Piece constructor
    Text_Piece::Text_Piece(std::string name, Text_Pattern& pattern): a_base_variables(pattern.needed_variables()), a_id(_piece_number), a_name(name), a_pattern(pattern) {
        _piece_number++;
    }

    // Save the text in a file
    void Text_Piece::save_as(std::string path) {
        std::filesystem::path save_path = std::filesystem::path(path);

        if(save_path.parent_path() != "" && !std::filesystem::exists(save_path.parent_path())) {
            print("Warning", "SCLS Documentalist Text Piece", "The text piece \"" + name() + "\" you want to save at the path \"" + path + "\" can't access to the path.");
            return;
        }

        write_in_file(path, text());
    }

    // Return the text well formatted
    std::string Text_Piece::text_with_pattern(std::string id) {
        std::string pattern_name = cut_string(id, "[")[0];
        std::string pattern_settings = id.substr(pattern_name.size(), id.size() - pattern_name.size());
        std::string to_return = "";

        // Handle piece-only characteristics
        if(!pattern_used(id)) return to_return;
        _Text_Pattern_Core* current_pattern = pattern(pattern_name);
        unsigned int iteration = 1;
        if(contains_patterns_iterations(id)) { iteration = pattern_iterations(id); }

        // Make the text
        for(unsigned int i = 0;i<iteration;i++) {
            // Create the current base text
            std::string current_base_text = current_pattern->base_text();
            // Handle the variables
            while(contains(current_base_text, VARIABLE_START)) {
                std::vector<std::string> cutted = cut_string(current_base_text, VARIABLE_START);
                current_base_text = "";

                current_base_text += cutted[0];
                for(int k = 1;k<static_cast<int>(cutted.size());k++) {
                    std::vector<std::string> sub_cutted = cut_string(cutted[k], VARIABLE_END);
                    if(sub_cutted.size() != 2) {
                        print("Warning", "SCLS Documentalist Text Piece " + name(), "The text of the pattern \"" + current_pattern->name() + "\n is badly syntaxed.");
                        return "";
                    }

                    // Handle the name of the variable
                    std::string variable_name = sub_cutted[0];
                    Text_Pattern_Base_Variable* current_variable = variable(variable_name, false);
                    if(current_variable == 0) {
                        current_variable = base_variable(variable_name);
                    }

                    // Change the text according to the variable
                    if(current_variable == 0) {
                        print("Warning", "SCLS Documentalist Text Piece " + name(), "The variable of the pattern \"" + current_pattern->name() + "\n does not exist in the piece.");
                    }
                    else {
                        variable_name = current_variable->content;
                            if(current_variable->line_start != "") variable_name = replace(variable_name, "\n", "\n" + current_variable->line_start);
                    }

                    current_base_text += variable_name;
                    current_base_text += sub_cutted[1];
                }
            }

            to_return += current_pattern->start_separation();
            if(current_pattern->text_position() == 0) to_return += current_base_text;

            // Get the text of the children of the pattern
            for(unsigned int j = 0;j<current_pattern->children().size();j++) {
                _Text_Pattern_Core* child = current_pattern->children()[j];
                std::string pattern_text = text_with_pattern(child->name());
                to_return += pattern_text;

                if(j != current_pattern->children().size() - 1) to_return += current_pattern->children_separation();

                if(current_pattern->text_position() == j + 1) {
                    if(j == current_pattern->children().size() - 1) to_return += current_pattern->children_separation();
                    to_return += current_base_text;
                    if(j != current_pattern->children().size() - 1) to_return += current_pattern->children_separation();
                }
            }

            to_return += current_pattern->end_separation();
        }

        return to_return;
    }

    // Return the text well formatted
    std::string Text_Piece::text() {
         std::string to_return = text_with_pattern(pattern().name());
        return to_return;
    }

    // Text_Piece destructor
    Text_Piece::~Text_Piece() {

    }
}

#endif
