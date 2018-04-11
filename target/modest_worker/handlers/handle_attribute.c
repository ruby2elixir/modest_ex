#include "erl_interface.h"
#include "ei.h"

#include "modest_html.h"

char* select_and_get_attribute(html_workspace_t* w, const char* html, const char* selector, const char* key, const char* delimiter)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  const char* scope_name = "html";
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  int attributes_index = html_get_attribute(w, collection_index, key);

  html_vec_str_t* attributes = html_get_buffer(w, attributes_index);
  char* result = html_vec_join(attributes, delimiter);

  return result;
}

char* get_attribute(html_workspace_t* w, const char* html, const char* key, const char* delimiter)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  const char* selector = "*";
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  const char* scope_name = "html";
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  int attributes_index = html_get_attribute(w, collection_index, key);

  html_vec_str_t* attributes = html_get_buffer(w, attributes_index);
  char* result = html_vec_join(attributes, delimiter);

  return result;
}

char* select_and_set_attribute(html_workspace_t* w, const char* html, const char* selector, const char* key, const char* value, const char* scope_name)
{
  int tree_index = html_parse_tree(w, html, strlen(html));
  int selector_index = html_prepare_selector(w, selector, strlen(selector));
  int collection_index  = html_select(w, tree_index, scope_name, selector_index);

  int attributes_index = html_set_attribute(w, collection_index, key, value);

  int buffer_index = html_serialize_tree(w, tree_index, scope_name);
  html_vec_str_t* buffer = html_get_buffer(w, buffer_index);
  char* result = html_vec_join(buffer, "");

  return result;
}

ETERM* handle_attribute(ErlMessage* emsg)
{
  ETERM* response = NULL;
  ETERM* get_attribute_pattern = erl_format("{get_attribute, Html, Key, Delimiter}");
  ETERM* get_selected_attribute_pattern = erl_format("{get_attribute, Html, Selector, Key, Delimiter}");
  // ETERM *set_attribute_pattern = erl_format("{set_attribute, Html, Key, Value}");
  ETERM* set_selected_attribute_pattern = erl_format("{set_attribute, Html, Selector, Key, Value, Scope}");

  if (erl_match(get_selected_attribute_pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(get_selected_attribute_pattern, "Html");
    ETERM* selector_term = erl_var_content(get_selected_attribute_pattern, "Selector");
    ETERM* key_term = erl_var_content(get_selected_attribute_pattern, "Key");
    ETERM* delimiter_term = erl_var_content(get_selected_attribute_pattern, "Delimiter");
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* selector = (char*)ERL_BIN_PTR(selector_term);
    char* key = (char*)ERL_BIN_PTR(key_term);
    char* delimiter = (char*)ERL_BIN_PTR(delimiter_term);

    html_workspace_t* workspace = html_init();
    char* result = select_and_get_attribute(workspace, html, selector, key, delimiter);
    if(result != NULL) {
      ETERM* result_bin = erl_mk_binary(result, strlen(result));
      response = erl_format("{get_attribute, ~w}", result_bin);
      html_free(result);
    }
    else {
      response = erl_format("{error, ~w}", erl_mk_atom("Failed to get attribute"));
    }

    // free allocated resources
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(selector_term);
    erl_free_term(key_term);
    erl_free_term(delimiter_term);
  }
  else if (erl_match(get_attribute_pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(get_attribute_pattern, "Html");
    ETERM* key_term = erl_var_content(get_attribute_pattern, "Key");
    ETERM* delimiter_term = erl_var_content(get_attribute_pattern, "Delimiter");
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* key = (char*)ERL_BIN_PTR(key_term);
    char* delimiter = (char*)ERL_BIN_PTR(delimiter_term);

    html_workspace_t* workspace = html_init();
    char* result = get_attribute(workspace, html, key, delimiter);
    if(result != NULL) {
      ETERM* result_bin = erl_mk_binary(result, strlen(result));
      response = erl_format("{get_attribute, ~w}", result_bin);
      html_free(result);
    }
    else {
      response = erl_format("{error, ~w}", erl_mk_atom("Failed to get attribute"));
    }

    // free allocated resources
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(key_term);
    erl_free_term(delimiter_term);
  }
  else if (erl_match(set_selected_attribute_pattern, emsg->msg)) {
    ETERM* html_term = erl_var_content(set_selected_attribute_pattern, "Html");
    ETERM* selector_term = erl_var_content(set_selected_attribute_pattern, "Selector");
    ETERM* key_term = erl_var_content(set_selected_attribute_pattern, "Key");
    ETERM* value_term = erl_var_content(set_selected_attribute_pattern, "Value");
    ETERM* scope_term = erl_var_content(set_selected_attribute_pattern, "Scope");
    char* html = (char*)ERL_BIN_PTR(html_term);
    char* selector = (char*)ERL_BIN_PTR(selector_term);
    char* key = (char*)ERL_BIN_PTR(key_term);
    char* value = (char*)ERL_BIN_PTR(value_term);
    char* scope = (char*)ERL_BIN_PTR(scope_term);

    html_workspace_t* workspace = html_init();
    char* result = select_and_set_attribute(workspace, html, selector, key, value, scope);
    if(result != NULL) {
      ETERM* result_bin = erl_mk_binary(result, strlen(result));
      response = erl_format("{set_attribute, ~w}", result_bin);
      html_free(result);
    }
    else {
      response = erl_format("{error, ~w}", erl_mk_atom("Failed to set attribute"));
    }

    // free allocated resources
    html_destroy(workspace);
    erl_free_term(html_term);
    erl_free_term(selector_term);
    erl_free_term(key_term);
    erl_free_term(value_term);
    erl_free_term(scope_term);
  }

  erl_free_term(get_attribute_pattern);
  erl_free_term(get_selected_attribute_pattern);
  // erl_free_term(set_attribute_pattern);
  erl_free_term(set_selected_attribute_pattern);
  return response;
}