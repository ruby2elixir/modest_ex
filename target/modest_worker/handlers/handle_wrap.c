#include "erl_interface.h"
#include "ei.h"
#include "eterm_vec.h"

#include "modest_html.h"

void select_and_wrap(html_workspace_t* w, const char* html, const char* selector, const char* new_html, const char* scope_name, vec_eterm_t* term_array)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  int new_tree_index = html_parse_tree(w, new_html, strlen(new_html));
  const char* new_scope_name = "body_children";
  int new_collection_index  = html_select_scope(w, new_tree_index, new_scope_name);

  html_wrap(w, collection_index, new_collection_index);

  int buffer_index = html_serialize_tree(w, collection_index, scope_name);
  html_vec_str_t* buffer = html_get_buffer(w, buffer_index);

  int i; char* val;
  html_vec_foreach(buffer, val, i) {
    eterm_vec_push(term_array, erl_mk_binary(val, strlen(val)));
  }
}

ETERM* handle_wrap(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* pattern = erl_format("{wrap, Html, Selector, NewHtml, Scope}");;

  if (erl_match(pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(pattern, "Html");
    ETERM* selector_term = erl_var_content(pattern, "Selector");
    ETERM* new_html_term = erl_var_content(pattern, "NewHtml");
    ETERM* scope_term = erl_var_content(pattern, "Scope");
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* selector = (char*)ERL_BIN_PTR(selector_term);
    char* new_html = (char*)ERL_BIN_PTR(new_html_term);
    char* scope = (char*)ERL_BIN_PTR(scope_term);

    html_workspace_t* workspace = html_init();
    vec_eterm_t term_array;
    eterm_vec_init(&term_array);
    select_and_wrap(workspace, html, selector, new_html, scope, &term_array);
    ETERM* term_list = eterm_vec_to_list(term_array);
    response = erl_format("{wrap, ~w}", term_list);

    // free allocated resources
    eterm_vec_destroy(&term_array);
    erl_free_term(term_list);
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(selector_term);
    erl_free_term(new_html_term);
    erl_free_term(scope_term);
  }

  erl_free_term(pattern);
  return response;
}