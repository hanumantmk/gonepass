#ifndef __GONEPASS_H
#define __GONEPASS_H

#include <stdint.h>
#include <gtk/gtk.h>
#include <jansson.h>
#include <openssl/evp.h>

struct master_key {
    int level, key_len;
    char id[33];
    uint8_t key_data[1056 + EVP_MAX_BLOCK_LENGTH];
};

struct credentials_bag {
    char vault_path[PATH_MAX];
    struct master_key level3_key, level5_key;
    int credentials_loaded;
};

#define GONEPASS_APP_TYPE (gonepass_app_get_type())
#define GONEPASS_APP(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GONEPASS_APP_TYPE, GonepassApp))

typedef struct _GonepassApp GonepassApp;
typedef struct _GonepassAppClass GonepassAppClass;

#define GONEPASS_APP_WINDOW_TYPE (gonepass_app_window_get_type())
#define GONEPASS_APP_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GONEPASS_APP_WINDOW_TYPE, GonepassAppWindow))

typedef struct _GonepassAppWindow GonepassAppWindow;
typedef struct _GonepassAppWindowClass GonepassAppWindowClass;

GType gonepass_app_get_type(void);
GonepassApp * gonepass_app_new(void);

GType gonepass_app_window_get_type(void);
GonepassAppWindow * gonepass_app_window_new(GonepassApp * app);
int gonepass_app_window_credentials_loaded(GonepassAppWindow * win);

#define GONEPASS_UNLOCK_DIALOG_TYPE (gonepass_unlock_dialog_get_type ())
#define GONEPASS_UNLOCK_DIALOG(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GONEPASS_UNLOCK_DIALOG_TYPE, GonepassUnlockDialog))

typedef struct _GonepassUnlockDialog          GonepassUnlockDialog;
typedef struct _GonepassUnlockDialogClass     GonepassUnlockDialogClass;

GType                   gonepass_unlock_dialog_get_type     (void);
GonepassUnlockDialog        *gonepass_unlock_dialog_new          (GonepassAppWindow *win);
const gchar * gonepass_unlock_dialog_get_pass(GonepassUnlockDialog *dlg);
const gchar * gonepass_unlock_dialog_get_vault_path(GonepassUnlockDialog * dlg);

int decrypt_item(json_t * input, struct credentials_bag * bag, char ** output);
int load_credentials(GonepassAppWindow * win, struct credentials_bag * out);
void clear_credentials(struct credentials_bag * bag);

#endif
