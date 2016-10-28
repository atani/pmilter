#ifndef PMILTER_H
#define PMILTER_H

#include "mruby.h"

#include "libmilter/mfapi.h"
#include "libmilter/mfdef.h"

#define PMILTER_NAME "pmilter"
#define PMILTER_VERSION_STR "0.0.1"
#define PMILTER_VERSION 0000001

#ifndef bool
#define bool int
#define TRUE 1
#define FALSE 0
#endif /* ! bool */

#define PMILTER_CONF_UNSET NULL
#define PMILTER_UNDEFINED -2
#define PMILTER_ERROR -1
#define PMILTER_OK 0

typedef struct connection_rec_t {

  char *ipaddr;
  const _SOCK_ADDR *hostaddr;

} connection_rec;

typedef struct command_rec_t {

  connection_rec *conn;
  char *connect_daemon;
  char *envelope_from;
  char *envelope_to;
  int receive_time;

} command_rec;

typedef struct pmilter_config_t {

  const char *mruby_connect_handler_path;

} pmilter_config;

typedef enum code_type_t { PMILTER_MRB_CODE_TYPE_FILE, PMILTER_MRB_CODE_TYPE_STRING } code_type;

typedef struct pmilter_mrb_code_t {

  union code {
    const char *file;
    const char *string;
  } code;
  code_type code_type;
  struct RProc *proc;
  mrbc_context *ctx;

} pmilter_mrb_code;

typedef struct pmilter_mrb_shared_state_t {

  mrb_state *mrb;

  /* commands of milter */
  command_rec *cmd;

  /* pmilter configuration */
  pmilter_config *config;

  /* return status of libmilter */
  int status;

  /* libmiler context */
  SMFICTX *ctx;
  /* mruby handler code */
  pmilter_mrb_code *mruby_connect_handler;
  pmilter_mrb_code *mruby_helo_handler;
  pmilter_mrb_code *mruby_envfrom_handler;
  pmilter_mrb_code *mruby_envrcpt_handler;
  pmilter_mrb_code *mruby_header_handler;
  pmilter_mrb_code *mruby_eoh_handler;
  pmilter_mrb_code *mruby_body_handler;
  pmilter_mrb_code *mruby_eom_handler;
  pmilter_mrb_code *mruby_abort_handler;
  pmilter_mrb_code *mruby_close_handler;
  pmilter_mrb_code *mruby_unknown_handler;
  pmilter_mrb_code *mruby_data_handler;

} pmilter_mrb_shared_state;

void pmilter_mrb_class_init(mrb_state *mrb);

#endif // NGX_STREAM_MRUBY_INIT_H
