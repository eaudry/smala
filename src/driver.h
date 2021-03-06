/*
 *  djnn Smala compiler
 *
 *  The copyright holders for the contents of this file are:
 *      Ecole Nationale de l'Aviation Civile, France (2018)
 *  See file "license.terms" for the rights and conditions
 *  defined by copyright holders.
 *
 *
 *  Contributors:
 *      Mathieu Magnaudet <mathieu.magnaudet@enac.fr>
 *
 */

#pragma once

#include <vector>
#include <istream>

#include "error_location.h"
#include "scanner.h"
#include "ast.h"
#include "parser.hpp"

namespace Smala {

class Node;
class Preamble;

class Driver {
public:
    Driver ();
    ~Driver ();
    int parse();
    void set_stream (std::istream *is, const std::string& filename);
    void clear();
    void add_node (Node *node);
    void add_use (const std::string &val);
    void add_import (const std::string &val);
    void add_native_action (const std::string &action_name, const std::string &parm_name, const std::string &code);
    void add_native_code (const std::string &code);
    void add_native_java (const std::string &code);
    void add_define_node (Node *node);
    void set_is_main (bool val);
    void set_error ();
    void end_preamble ();
    const Ast& ast ();
    smala::ErrorLocation* location () const;

    friend class Parser;
    friend class Scanner;
    
private:
    void increaseLocation (const char*, int len);
    Scanner m_scanner;
    Parser m_parser;
    unsigned int m_line, m_pos;
    std::string m_file;
    Ast m_ast;
    int m_error;
};

}
