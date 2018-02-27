#include "handlers.h"

#include "modest_find.h"
#include "modest_serialize.h"

#define DEFAULT_FIND_DELIMITER "|"

void
handle_emsg(state_t* state, ErlMessage* emsg)
{
  switch(emsg->type)
  {
    case ERL_REG_SEND:
    case ERL_SEND:
      handle_send(state, emsg);
      break;
    case ERL_LINK:
    case ERL_UNLINK:
      break;
    case ERL_EXIT:
      break;
  }

  // its our responsibility to free these pointers
  erl_free_compound(emsg->msg);
  erl_free_compound(emsg->to);
  erl_free_compound(emsg->from);
}

void
handle_send(state_t* state, ErlMessage* emsg)
{
  ETERM *find_pattern = erl_format("{find, Html, Selector}");
  ETERM *find_pattern_delimiter = erl_format("{find, Html, Selector, Delimiter}");
  ETERM *serialize_pattern = erl_format("{serialize, Html}");
  ETERM *response;

  if (erl_match(find_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(find_pattern, "Html");
    ETERM *selector = erl_var_content(find_pattern, "Selector");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);

    const char* result_string = modest_find(html_string, selector_string, DEFAULT_FIND_DELIMITER);

    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{find, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(selector);
  }
  else if (erl_match(find_pattern_delimiter, emsg->msg))
  {
    ETERM *html = erl_var_content(find_pattern_delimiter, "Html");
    ETERM *selector = erl_var_content(find_pattern_delimiter, "Selector");
    ETERM *delimiter = erl_var_content(find_pattern_delimiter, "Delimiter");
    char* html_string = (char*)ERL_BIN_PTR(html);
    char* selector_string = (char*)ERL_BIN_PTR(selector);
    char* delimiter_string = (char*)ERL_BIN_PTR(delimiter);

    const char* result_string = modest_find(html_string, selector_string, delimiter_string);

    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{find, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
    erl_free_term(selector);
    erl_free_term(delimiter);
  }
  else if (erl_match(serialize_pattern, emsg->msg))
  {
    ETERM *html = erl_var_content(serialize_pattern, "Html");
    char* html_string = (char*)ERL_BIN_PTR(html);
    const char* result_string = modest_serialize(html_string);
    ETERM* result_bin = erl_mk_binary(result_string, strlen(result_string));
    response = erl_format("{serialize, ~w}", result_bin);

    // free allocated resources
    erl_free_term(html);
  }
  else
  {
    response = err_term("unknown_call");
    return;
  }

  // send response
  erl_send(state->fd, emsg->from, response);

  // free allocated resources
  erl_free_compound(response);
  erl_free_term(find_pattern);
  erl_free_term(find_pattern_delimiter);
  erl_free_term(serialize_pattern);

  // free the free-list
  erl_eterm_release();

  return;
}