//******************
//
// scls_documentalist_test -> headers/scls_documentalist_project.h
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
// headers/scls_documentalist_project.h description
//
// This file contains the project system of SCLS Documentalist.
//
//******************
//
// Project system description
//
// In SCLS Documentalist, a project is a set of patterns.
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

#include "scls_documentalist_core.h"

// Define some stuff in a project
// Avoid the repetition of an header
#ifndef SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION
#define SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION std::string("avoid_header_repetition")
#endif // SCLS_DOCUMENTALIST_AVOID_HEADER_REPETITION
// Define the name of the variable of a part of code
#ifndef SCLS_DOCUMENTALIST_CODE_PART
#define SCLS_DOCUMENTALIST_CODE_PART std::string("code_part[][]")
#endif // SCLS_DOCUMENTALIST_CODE_PART_TITLE
// Define the name of the variable of the title of a part of code
#ifndef SCLS_DOCUMENTALIST_CODE_PART_TITLE
#define SCLS_DOCUMENTALIST_CODE_PART_TITLE std::string("code_part_title[][]")
#endif // SCLS_DOCUMENTALIST_CODE_PART_TITLE
// Define the description of an included file
#ifndef SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION
#define SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION std::string("include_description[]")
#endif // SCLS_DOCUMENTALIST_INCLUDE_DESCRIPTION
// Define the content of a macro
#ifndef SCLS_DOCUMENTALIST_MACRO_CONTENT
#define SCLS_DOCUMENTALIST_MACRO_CONTENT std::string("macro_content[]")
#endif // SCLS_DOCUMENTALIST_MACRO_CONTENT
// Define the description of a macro
#ifndef SCLS_DOCUMENTALIST_MACRO_DESCRIPTION
#define SCLS_DOCUMENTALIST_MACRO_DESCRIPTION std::string("macro_description[]")
#endif // SCLS_DOCUMENTALIST_MACRO_DESCRIPTION
// Define the name of a macro
#ifndef SCLS_DOCUMENTALIST_MACRO_NAME
#define SCLS_DOCUMENTALIST_MACRO_NAME std::string("macro_name[]")
#endif // SCLS_DOCUMENTALIST_MACRO_NAME
// Define the path of an included file
#ifndef SCLS_DOCUMENTALIST_INCLUDE_PATH
#define SCLS_DOCUMENTALIST_INCLUDE_PATH std::string("include_path[]")
#endif // SCLS_DOCUMENTALIST_INCLUDE_PATH
// Define the name of the variable of the description of a licence
#ifndef SCLS_DOCUMENTALIST_LICENCE_DESCRIPTION_VARIABLE
#define SCLS_DOCUMENTALIST_LICENCE_DESCRIPTION_VARIABLE std::string("licence_description")
#endif // SCLS_DOCUMENTALIST_LICENCE_DESCRIPTION_VARIABLE
// Define the name of the variable of the name of a licence
#ifndef SCLS_DOCUMENTALIST_LICENCE_NAME_VARIABLE
#define SCLS_DOCUMENTALIST_LICENCE_NAME_VARIABLE std::string("licence_name")
#endif // SCLS_DOCUMENTALIST_LICENCE_NAME_VARIABLE
// Define the name of the variable of the description of a project
#ifndef SCLS_DOCUMENTALIST_PROJECT_DESCRIPTION_VARIABLE
#define SCLS_DOCUMENTALIST_PROJECT_DESCRIPTION_VARIABLE std::string("project_description")
#endif // SCLS_DOCUMENTALIST_PROJECT_DESCRIPTION_VARIABLE
// Define the name of the variable of the name of a project
#ifndef SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE
#define SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE std::string("project_name")
#endif // SCLS_DOCUMENTALIST_PROJECT_NAME_VARIABLE
// Define the name of the variable of the title of a part of a project
#ifndef SCLS_DOCUMENTALIST_TITLE
#define SCLS_DOCUMENTALIST_TITLE std::string("part_title[]")
#endif // SCLS_DOCUMENTALIST_TITLE

// Use of the "scls" namespace to be more easily usable
namespace scls {

    //*********
    //
    // Files / variables handling
    //
    //*********

    struct License {
        // Struct representing the used license in a project, by default to GPL V3.0

        // Name of the license
        std::string name = "GPLv3";
        // Notice of the license
        std::string notice = "This file is part of *.\n\n* is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\n* is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\nSee the GNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License along with *. If not, see <https://www.gnu.org/licenses/>.";
    };

    struct Replica_File_Variable {
        // Struct representing a variable in a replica file
        // Content if the variable
        std::string content = "";
        // If the variable is listed or not
        virtual bool listed() const {return false;};
        // Name of the variable
        std::string name = "";
        // Pattern variable of this variable
        std::shared_ptr<Pattern_Variable> pattern_variable;

        // Datas about the pattern variable
        inline constexpr bool global() const {return pattern_variable.get()->global;};
    };

    class __Variables_Value_Container {
        // Class representing a container of variable
    public:
        // __Variables_Value_Container constructor
        __Variables_Value_Container(){};
        // __Variables_Value_Container destructor
        ~__Variables_Value_Container(){};

        // Returns a global variable
        inline std::string* global_variable(std::string variable) {
            for(std::map<std::string, std::string>::iterator it = a_global_variables.begin();it!=a_global_variables.end();it++) { if(it->first == variable) return &it->second; } return 0;
        };
        // Returns the value of a global variable, or ""
        inline std::string global_variable_value(std::string variable) {
            for(std::map<std::string, std::string>::iterator it = a_global_variables.begin();it!=a_global_variables.end();it++) { if(it->first == variable) return it->second; } return "";
        };
        // Change the value of a global variable
        inline void set_global_variable_value(std::string variable_name, std::string new_value) {a_global_variables[variable_name]=new_value;};

        // Getters and setters
        inline std::map<std::string, std::string>& global_variables() {return a_global_variables;};
    private:

        // Values of the global variable in the replica project
        std::map<std::string, std::string> a_global_variables = std::map<std::string, std::string>();
    };

    struct __Replica_File_Variable_Element_Base {
        // Struct representing an element of variable in a replica file
        // Number of the element
        unsigned int element_number = 0;
        // Parent variable of the element
        std::shared_ptr<Replica_File_Variable> parent_variable;
        // Pattern use by the file
        Text_Pattern* pattern = 0;
        // Pattern list of this element
        Pattern_Variable_List* pattern_list = 0;

        // Set the pattern and do the needed operation with
        void set_pattern(Text_Pattern* new_pattern) {
            pattern = new_pattern;
            variables.clear();
            // Create the needed variables
            std::vector<std::shared_ptr<Pattern_Variable>>& needed_variables = pattern_list->variables;
            for(int i = 0;i<static_cast<int>(needed_variables.size());i++) {
                __create_variable_by_pattern_variable(needed_variables[i]);
            }
        };

        // Create a variable from a pattern variable
        bool __can_variable_be_created(std::shared_ptr<Pattern_Variable> variable) {return !(variable.get() == 0 || variable.get()->global || variable.get()->path_to_root);};
        virtual std::shared_ptr<Replica_File_Variable> __create_variable_by_pattern_variable(std::shared_ptr<Pattern_Variable> variable) {
            if(!__can_variable_be_created(variable)) return std::shared_ptr<Replica_File_Variable>();
            std::shared_ptr<Replica_File_Variable> to_return = std::make_shared<Replica_File_Variable>();
            to_return.get()->content = variable.get()->content;
            to_return.get()->name = variable.get()->name;
            to_return.get()->pattern_variable = variable;
            variables.push_back(to_return);
            return to_return;
        }
        // Returns a variable in the file
        inline std::shared_ptr<Replica_File_Variable> variable_by_pattern_variable(std::shared_ptr<Pattern_Variable> variable) {
            for(int i = 0;i<static_cast<int>(variables.size());i++) {
                if(variables[i].get()->name == variable.get()->name) return variables[i];
            } return __create_variable_by_pattern_variable(variable);
        };
        inline std::shared_ptr<Replica_File_Variable> variable_by_name(std::string variable_name) {
            for(int i = 0;i<static_cast<int>(variables.size());i++) {
                if(variables[i].get()->name == variable_name) return variables[i];
            }

            // Create the variable if it does not exist
            if(pattern != 0) {
                if(parent_variable.get() != 0) {
                    return __create_variable_by_pattern_variable(pattern->variable_in_list_by_name(parent_variable.get()->name, variable_name));
                } return __create_variable_by_pattern_variable(pattern->variable_by_name(variable_name));
            }
            else {return std::shared_ptr<Replica_File_Variable>();}
        };
        // Values of the global variable in the replica project
        std::shared_ptr<__Variables_Value_Container> global_variables;
        // Defined variables for the file
        std::vector<std::shared_ptr<Replica_File_Variable>> variables = std::vector<std::shared_ptr<Replica_File_Variable>>();
    };

    struct Replica_File_Variable_List : public Replica_File_Variable {
        // Struct representing a list of variable in a replica file
        // List of elements in the list
        std::vector<std::shared_ptr<__Replica_File_Variable_Element_Base>> elements;
        // If the variable is listed or not
        bool listed() const override {return true;};
    };

    struct Replica_File_Variable_Element : public __Replica_File_Variable_Element_Base {
        // Struct representing an entire element of variable in a replica file
        // Create a variable from a pattern variable
        virtual std::shared_ptr<Replica_File_Variable> __create_variable_by_pattern_variable(std::shared_ptr<Pattern_Variable> variable) override {
            if(!__can_variable_be_created(variable)) return std::shared_ptr<Replica_File_Variable>();
            std::shared_ptr<Replica_File_Variable> to_return;
            std::shared_ptr<Replica_File_Variable_List> to_return_list;
            if(variable.get()->listed()) {
                to_return_list = std::make_shared<Replica_File_Variable_List>();
                to_return = to_return_list;
            }
            else {to_return = std::make_shared<Replica_File_Variable>();}
            to_return.get()->content = variable.get()->content;
            to_return.get()->name = variable.get()->name;
            to_return.get()->pattern_variable = variable;
            variables.push_back(to_return);
            return to_return;
        }
    };

    struct Replica_File: public Replica_File_Variable_Element {
        // Struct representing a file in a replica project
        // Constructor
        Replica_File(const std::shared_ptr<__Variables_Value_Container>& replica_project_global_variables) {global_variables=replica_project_global_variables;};

        // Content out of the pattern
        std::string content_out_pattern = "";
        // Internal path of the file
        std::string internal_path = "";
    };

    //*********
    //
    // Projects handling
    //
    //*********

    class Pattern_Project {
        // Class representing the entire project
    public:
        // Most basic Pattern_Project constructor
        Pattern_Project(std::string name, std::string path);
        // Pattern_Project destructor
        ~Pattern_Project();

        // Parse the entire project
        void parse_project();

        // Apply all to a part of text
        std::string __apply_all(const std::string& part_of_text, __Replica_File_Variable_Element_Base& file, std::string internal_path, _Balise_Container* balising_system);
        inline std::string __apply_all(const std::string& part_of_text, Replica_File& file, _Balise_Container* balising_system){return __apply_all(part_of_text, file, file.internal_path, balising_system);};
        // Apply the global variables to a part of text
        std::string __apply_global_variables(const std::string& part_of_text, __Replica_File_Variable_Element_Base& file, _Balise_Container* balising_system);
        // Returns the content of a file
        std::string file_content(Replica_File& file, _Balise_Container* balising_system);
        // Load a project unformatted from sda V0.1
        static Pattern_Project* load_sda_0_1(std::string path);
        // Save the project unformatted
        bool save_sda_0_1(std::string path);
        inline bool save_sda_0_1() {return save_sda_0_1(path_parent(a_path));};

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::string description() const {return a_description;};
        inline std::string directory() const {return path_parent(path());};
        inline std::string name() const {return a_name;};
        inline std::string path() const {return a_path;};
        inline void set_description(std::string new_project_description) {a_description = new_project_description;};
        inline void set_name(std::string new_project_name) {a_name = new_project_name;};

        // Create a pattern in the project
        std::shared_ptr<Text_Pattern>* new_pattern(std::string pattern_name, std::string base_text);

        // Getters and setters (ONLY WITHOUT ATTRIBUTES)
        inline bool contains_global_variable(std::string variable_name)  {return global_variable(variable_name) != 0;};
        inline bool contains_pattern(Text_Pattern* pattern) {for(int i = 0;i<static_cast<int>(patterns().size());i++){ if(patterns()[i].get() == pattern) return true; } return false; };
        inline bool contains_pattern_by_name(std::string pattern_name) {return pattern_by_name(pattern_name) != 0; };
        inline std::shared_ptr<Pattern_Variable>* global_variable(std::string variable_name) {for(int i = 0;i<static_cast<int>(a_global_variables.size());i++){if(a_global_variables[i].get()->name == variable_name){return &(a_global_variables[i]);}}return 0;};
        inline Text_Pattern* pattern_by_name(std::string pattern_name) {for(int i = 0;i<static_cast<int>(patterns().size());i++){ if(patterns()[i].get()->name() == pattern_name) return patterns()[i].get(); } return 0;};

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::vector<std::shared_ptr<Pattern_Variable>>& global_variables() {return a_global_variables;};
        inline std::vector<std::shared_ptr<Text_Pattern>>& patterns() {return a_patterns;};
    private:
        // Datas for Agatha
        // Value of each defined global variables
        std::vector<std::shared_ptr<Pattern_Variable>> a_global_variables = std::vector<std::shared_ptr<Pattern_Variable>>();
        // Each defined patterns
        std::vector<std::shared_ptr<Text_Pattern>> a_patterns = std::vector<std::shared_ptr<Text_Pattern>>();

        // Datas about the project
        // Description of the project
        std::string a_description = "";
        // Name of the project
        std::string a_name = "";
        // Path of the project
        std::string a_path = "";
    };

    class Replica_Project {
        // Class representing the entire project
    public:

        // Most basic Replica_Project constructor
        Replica_Project(std::string name, std::string path, const std::shared_ptr<Pattern_Project>& pattern);

        // Add a replica file variable element to a replica file in the project
        void __add_replica_file_variable_element(std::shared_ptr<Replica_File_Variable_Element> replica_file_variable_element, std::string replica_file_variable_path);
        // Exports the project
        bool export_project(std::string path, _Balise_Container* balising_system);
        // Returns a replica file by its path, or 0 if there is no this path
        Replica_File* replica_file_by_path(std::string replica_file_path) {
            for(int i = 0;i<static_cast<int>(replica_files().size());i++) {
                if(replica_files()[i].get()->internal_path == replica_file_path) return replica_files()[i].get();
            }
            return 0;
        };
        // Load a global variable in the project from sda V 0.2
        void load_global_variable_sda_0_2(std::string path);
        // Load a replica file in the project from sda V 0.2
        void load_replica_file_sda_0_2(std::string path);
        // Load a replica file variable element in the project from sda V 0.2
        void __load_replica_file_variable_element(std::shared_ptr<Replica_File_Variable_Element> element, std::string path);
        // Load the project from sda V 0.2
        static Replica_Project* load_sda_0_2(std::string path, const std::shared_ptr<Pattern_Project>& pattern);
        // Creates a new replica file in the project and returns it
        std::shared_ptr<Replica_File> new_replica_file(std::string replica_file_path, scls::Text_Pattern* pattern);
        // Remove a replica file from a project
        void remove_replica_file(Replica_File* file){for(int i=0;i<static_cast<int>(replica_files().size());i++){if(replica_files()[i].get() == file){replica_files().erase(replica_files().begin() + i);break;}}};
        inline void remove_replica_file(std::shared_ptr<Replica_File> file){remove_replica_file(file.get());};
        // Returns the path of the attached patter in a replica
        static std::string replica_attached_pattern_from_path_sda_0_2(std::string path);

        // Saves a file
        inline void __save_file(std::string file_path, std::string content) {write_in_file(file_path, to_utf_8(content));};
        // Returns the text to save a replica file
        std::string save_replica_file_text_sda_0_2(Replica_File* replica_file, std::string path, unsigned int& total_file_number);
        // Returns the text to save a replica file element
        std::string save_replica_file_variable_element_text_sda_0_2(__Replica_File_Variable_Element_Base* element, std::string path, unsigned int& total_file_number);
        inline std::string save_replica_file_variable_element_text_sda_0_2(std::shared_ptr<__Replica_File_Variable_Element_Base> element, std::string path, unsigned int& total_file_number){return save_replica_file_variable_element_text_sda_0_2(element.get(), path, total_file_number);};
        // Returns the text to save a replica file variable
        std::string save_replica_file_variable_text_sda_0_2(Replica_File_Variable* replica_file_variable, std::string path, unsigned int& total_file_number);
        inline std::string save_replica_file_variable_text_sda_0_2(std::shared_ptr<Replica_File_Variable> replica_file_variable, std::string path, unsigned int& total_file_number){
            if(replica_file_variable.get()->listed()) {
                Replica_File_Variable_List* current_list = reinterpret_cast<Replica_File_Variable_List*>(replica_file_variable.get());
                return save_replica_file_variable_list_text_sda_0_2(current_list, path, total_file_number);
            }
            return save_replica_file_variable_text_sda_0_2(replica_file_variable.get(), path, total_file_number);
        };
        // Returns the text to save a replica file variable list
        std::string save_replica_file_variable_list_text_sda_0_2(Replica_File_Variable_List* replica_file_variable, std::string path, unsigned int& total_file_number);
        // Save the project unformatted
        bool save_sda_0_2(std::string path);
        inline bool save_sda_0_2(){return save_sda_0_2(path());};

        // Returns the sorted first path
        std::shared_ptr<std::vector<std::shared_ptr<Replica_File>>> replica_files_first_sorted_by_path();
        // Returns the sorted replica files by path
        std::shared_ptr<std::vector<std::shared_ptr<Replica_File>>> replica_files_sorted_by_path();

        // Returns the path of the main file of the project
        inline std::string path_main_file() const {
            std::string to_return = path();
            if(to_return[to_return.size() - 1] != '/') to_return += "/";
            to_return += name() + ".sdr";
            return to_return;
        };

        // Getters and setters
        inline Pattern_Project* attached_pattern() const {return a_pattern.get();};
        inline std::shared_ptr<Pattern_Project> attached_pattern_shared_ptr() const {return a_pattern;};
        inline std::string global_variable_value(std::string variable_name) {return a_global_variables_values.get()->global_variable_value(variable_name);};
        inline std::vector<std::shared_ptr<Pattern_Variable>>& global_variables() {return a_pattern->global_variables();};
        inline std::shared_ptr<Pattern_Variable>* global_variable(std::string variable_name) {return a_pattern->global_variable(variable_name);};
        inline std::map<std::string, std::string>& global_variables_values() {return a_global_variables_values.get()->global_variables();};
        inline std::string path() const {return a_path;};
        inline std::string name() const {return a_name;};
        inline std::vector<std::shared_ptr<Replica_File>>& replica_files() {return a_replica_files;};
        inline void set_global_variable_value(std::string variable_name, std::string new_value) {if(global_variable(variable_name)!=0)a_global_variables_values.get()->set_global_variable_value(variable_name,new_value);};
    private:
        // Datas about the replica project
        // Description of the replica project
        std::string a_description = "";
        // Values of the global variable
        std::shared_ptr<__Variables_Value_Container> a_global_variables_values = std::make_shared<__Variables_Value_Container>();
        // Name of the replica project
        std::string a_name = "";
        // Path of the project
        std::string a_path = "";
        // Pattern attached to the project
        std::shared_ptr<Pattern_Project> a_pattern;
        // Value of each defined files
        std::vector<std::shared_ptr<Replica_File>> a_replica_files = std::vector<std::shared_ptr<Replica_File>>();
    };

    // Returns a pointer to a SCLS Format "Mary" formatted C++ project created with the new constructor
    // Pattern_Project* cpp_scls_format_project(std::string project_name = "cpp", std::string project_path = "");
}

#endif // SCLS_DOCUMENTALIST_PROJECT
