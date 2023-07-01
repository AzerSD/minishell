/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:17:07 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:17:07 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *fix_cmd(char *orig_cmd, int backquoted) {
    char *cmd = my_malloc(&shell.memory, strlen(orig_cmd + 1));
    if (!cmd) {
        fprintf(stderr, "error: insufficient memory to perform command substitution\n");
        return NULL;
    }
    strcpy(cmd, orig_cmd + (backquoted ? 1 : 2));
    return cmd;
}

void fix_backquoted_cmd(char *cmd, size_t cmdlen) {
    char *p1;
    char *p2;
    char *p3;

    if (cmd[cmdlen - 1] == '`')
        cmd[cmdlen - 1] = '\0';

    p1 = cmd;
    do {
        if (*p1 == '\\' && (p1[1] == '$' || p1[1] == '`' || p1[1] == '\\')) {
            p2 = p1;
            p3 = p1 + 1;
            while ((*p2++ = *p3++));
        }
    } while (*(++p1));
}

void remove_closing_brace(char *cmd, size_t cmdlen) {
    /* remove the last closing brace */
    if (cmd[cmdlen - 1] == ')')
        cmd[cmdlen - 1] = '\0';
}

char *extend_buffer(char *buf, size_t bufsz, int i) {
    char *buf2;

    buf2 = realloc(buf, bufsz + i + 1);
    if (!buf2) {
        free(buf);
        return NULL;
    }
    buf = buf2;

    return buf;
}

void remove_trailing_newlines(char *buf, size_t bufsz) {
    int i = bufsz - 1;
    while (buf[i] == '\n' || buf[i] == '\r') {
        buf[i] = '\0';
        i--;
    }
}

char *command_substitute(char *orig_cmd) {
    char b[1024];
    size_t bufsz = 0;
    char *buf = NULL;
    char *p = NULL;
    int i = 0;
    int backquoted = (*orig_cmd == '`');
    char *cmd;
    size_t cmdlen;
    FILE *fp = NULL;
    char *buf2;

    cmd = fix_cmd(orig_cmd, backquoted);
    if (!cmd) {
        return NULL;
    }

    cmdlen = strlen(cmd);
    if (backquoted) {
        fix_backquoted_cmd(cmd, cmdlen);
    } else {
        remove_closing_brace(cmd, cmdlen);
    }

    fp = popen(cmd, "r");
    if (!fp) {
        free(cmd);
        fprintf(stderr, "error: failed to open pipe: %s\n", strerror(errno));
        return NULL;
    }

    while ((i = fread(b, 1, 1024, fp))) {
        if (!buf) {
            buf = my_malloc(&shell.memory, i + 1);
            if (!buf) {
                goto fin;
            }
            p = buf;
        } else {
            buf = extend_buffer(buf, bufsz, i);
            if (!buf) {
                goto fin;
            }
            p = buf + bufsz;
        }
        bufsz += i;
        memcpy(p, b, i);
        p[i] = '\0';
    }

    if (!bufsz) {
        free(cmd);
        return NULL;
    }

    remove_trailing_newlines(buf, bufsz);

fin:
    pclose(fp);
    free(cmd);
    if (!buf)
        fprintf(stderr,
                "error: insufficient memory to perform command substitution\n");
    return buf;
}
