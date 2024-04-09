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

    // Most basic Text_Pattern constructor
    Text_Pattern::Text_Pattern(std::string name, std::string base_text, Text_Pattern* parent): a_base_text(base_text), a_name(name), a_parent(parent) {
        if(parent != 0)parent->add_child(this);
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

    // Return the entire text of the pattern
    std::string Text_Pattern::text() const {
        std::string to_return = "";

        to_return += start_separation();
        if(text_position() == 0) to_return += base_text();

        for(unsigned int i = 0;i<static_cast<unsigned int>(a_children.size());i++) {
            Text_Pattern* child = a_children[i];

            to_return += child->text();
            if(i != a_children.size() - 1) to_return += children_separation();
            if(i + 1 == text_position()) to_return += base_text();
        }
        to_return += end_separation();

        return to_return;
    }

    // Returns the needed variable in the pattern
    std::vector<Text_Pattern_Variable> Text_Pattern::needed_variables() {
        std::vector<Text_Pattern_Variable> to_return = std::vector<Text_Pattern_Variable>();
        std::vector<std::string> cutted = cut_string(base_text(), VARIABLE_START);

        for(int i = 1;i<static_cast<int>(cutted.size());i++) {
            std::string variable_name = cut_string(cutted[i], VARIABLE_END)[0];

            if(!_contains_pattern_variable_by_name(to_return, variable_name)) {
                Text_Pattern_Variable variable;
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
            std::vector<Text_Pattern_Variable> children_variables = a_children[i]->needed_variables();

            for(int i = 0;i<static_cast<int>(children_variables.size());i++) {
                if(!_contains_pattern_variable_by_name(to_return, children_variables[i].name)) {
                    Text_Pattern_Variable variable;
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

    // Text_Pattern destructor
    Text_Pattern::~Text_Pattern() {
        for(int i = 0;i<static_cast<int>(a_children.size());i++) {
            delete a_children[i]; a_children[i] = 0;
        }
        a_children.clear();
    }

    // Most basic Text_Piece constructor
    Text_Piece::Text_Piece(std::string name, Text_Pattern& pattern): a_name(name), a_pattern(pattern) {
        a_variables = new std::vector<Text_Pattern_Variable>();
        std::vector<Text_Pattern_Variable> pattern_variable = pattern.needed_variables();
        for(int i = 0;i<static_cast<int>(pattern_variable.size());i++) {
            a_variables->push_back(pattern_variable[i]);
        }
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

    // Return the text "text_to_format" well formatted
    std::string Text_Piece::text(std::string text_to_format) {
        std::string to_return = "";
        std::vector<std::string> cutted = cut_string_out_quotes(text_to_format, VARIABLE_START);
        to_return += cutted[0];
        for(int i = 1;i<static_cast<int>(cutted.size());i++) {
            std::vector<std::string> local_cutted = cut_string_out_quotes(cutted[i], VARIABLE_END);
            if(local_cutted.size() < 2) {
                print("Warning", "SCLS Documentalist Text Piece", "The text piece \"" + name() + "\" where you want to get the text is badly syntaxed.");
                return text_to_format;
            }

            std::string variable_name = local_cutted[0];
            Text_Pattern_Variable* pattern_variable = variable(variable_name);
            variable_name = pattern_variable->content;
            if(pattern_variable->line_start != "") variable_name = replace(variable_name, "\n", "\n" + pattern_variable->line_start);

            to_return += variable_name;
            to_return += local_cutted[1];
        }

        if(!contains(to_return, VARIABLE_START)) return to_return;
        return text(to_return);
    }

    // Return the text well formatted
    std::string Text_Piece::text() {
        std::string to_return = "";
        std::string unformatted = pattern().text();

        if(!contains(unformatted, VARIABLE_START)) return unformatted;
        return text(unformatted);
    }

    // Text_Piece destructor
    Text_Piece::~Text_Piece() {
        if(a_variables != 0) {
            delete a_variables; a_variables = 0;
        }
    }
}

#endif
