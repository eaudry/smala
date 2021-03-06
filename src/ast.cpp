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

#include "ast.h"

using namespace Smala;

Ast::Ast () :
    m_node_list (), m_is_main (false), m_in_preamble (true)
{

}

Ast::~Ast ()
{

}

bool
Ast::is_main () const
{
  return m_is_main;
}

void
Ast::set_is_main (bool val)
{
  m_is_main = val;
}

void
Ast::clear ()
{
  m_node_list.clear ();
  m_native_list.clear ();
  m_define_nodes.clear ();
  m_smala_native.clear ();
  m_preamble.clear ();
}

void
Ast::add_define_node (Node *node)
{
  m_define_nodes.push_back (node);
}

void
Ast::add_node (Node *node)
{
  m_node_list.push_back (node);
}

void
Ast::add_use (const std::string &val)
{
  m_preamble.add_use (val);
}

void
Ast::add_import (const std::string &import)
{
  m_preamble.add_import (import);
}

void
Ast::add_native_action (const std::string &action_name, const std::string &param_name, const std::string &code)
{
  NativeActionNode *node = new NativeActionNode (action_name, param_name, code);
  m_native_list.push_back (node);
  if (m_in_preamble)
    m_preamble.add_node (node);
  else
    add_node (node);
}

void
Ast::add_native_code (const std::string &code)
{
  NativeCodeNode *node = new NativeCodeNode (code);
  if (m_in_preamble)
    m_preamble.add_node (node);
  else
    add_node (node);
}

void
Ast::add_native_java (const std::string &code)
{
  NativeCodeNode *node = new NativeCodeNode (code);
  node->set_node_type (NATIVE_JAVA);
  m_preamble.add_java_code_node (node);
}

const std::vector<Node*>&
Ast::node_list () const
{
  return m_node_list;
}

const std::vector<NativeActionNode*>
Ast::native_list () const
{
  return m_native_list;
}

const std::vector<Node*>
Ast::define_node_list () const
{
  return m_define_nodes;
}

const Preamble&
Ast::preamble () const
{
  return m_preamble;
}

void
Ast::end_preamble ()
{
  m_in_preamble = false;
}
