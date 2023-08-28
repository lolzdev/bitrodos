#include <mods.h>

static state_t *STATE;

void load_mods(state_t *state)
{
    STATE = state;
    state->render_hooks = (hook_node_t *) malloc(sizeof(hook_node_t)); 
    state->render_hooks->ref = LUA_NOREF;

    state->pre_init_hooks = (hook_node_t *) malloc(sizeof(hook_node_t)); 
    state->pre_init_hooks->ref = LUA_NOREF;

    state->cursor_hooks = (hook_node_t *) malloc(sizeof(hook_node_t)); 
    state->cursor_hooks->ref = LUA_NOREF;

    state->key_hooks = (hook_node_t *) malloc(sizeof(hook_node_t)); 
    state->key_hooks->ref = LUA_NOREF;

    state->tick_hooks = (hook_node_t *) malloc(sizeof(hook_node_t)); 
    state->tick_hooks->ref = LUA_NOREF;

    lua_State *L = luaL_newstate();
    state->L = L;

    luaL_openlibs(L);

    lua_newtable(L);
    luaL_setfuncs(L, module_graphics, 0);
    lua_setglobal(L, "graphics");

    lua_newtable(L);
    luaL_setfuncs(L, module_system, 0);
    lua_setglobal(L, "system");

    lua_newtable(L);
    luaL_setfuncs(L, module_log, 0);
    lua_setglobal(L, "log");

    lua_newtable(L);
    luaL_setfuncs(L, module_input, 0);
    lua_setglobal(L, "input");

    lua_register(L, "require", l_require);

    luaL_newmetatable(L, "Vec3");
    luaL_setfuncs(L, vec3_m, 0);
    lua_register(L, "Vec3", l_vec3);

    luaL_newmetatable(L, "Camera");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    luaL_setfuncs(L, camera_m, 0);
    lua_register(L, "Camera", l_camera);

    if (luaL_dofile(L, "lua/keys.lua")) {
        error("error while loading core library: %s", lua_tostring(L, -1));
    }

    if (luaL_dofile(L, "lua/misc.lua")) {
        error("error while loading core library: %s", lua_tostring(L, -1));
    }

    load_textures(state);

    struct dirent *entry = NULL;
    DIR *dp = NULL;
    
    dp = opendir("mods");
    if (dp != NULL) {
        while ((entry = readdir(dp))) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                load_mod(entry->d_name, L);
        }
    }

    closedir(dp);

    info("Loaded %d textures", state->texture_count);
}

void load_mod(char *name, lua_State *L)
{
    info("Loading mod %s", name);

    size_t path_len = strlen(name) + 19;
    char *path = (char *) malloc(path_len);
    sprintf(path, "mods/%s/lua/init.lua", name);

    if (luaL_dofile(L, path)) {
        error("error while loading mod %s: %s", name, lua_tostring(L, -1));
    }

    free(path);
}

int l_add_hook(lua_State *L)
{
    const char *type = lua_tostring(L, 1);
    if (!type) return luaL_error(L, "expected type `string` as parameter #1");

    luaL_checktype(L, 2, LUA_TFUNCTION);
    lua_pushvalue(L, 2);
    int callback = luaL_ref(L, LUA_REGISTRYINDEX);
    if (callback == LUA_NOREF || callback == LUA_REFNIL) return luaL_error(L, "expected type `function` as parameter #2");


    if (strcmp(type, "render") == 0) {
        hook_node_t *head = STATE->render_hooks;
        hook_node_t *prev = head;
        while(1) {
            if (!head) {
                head = (hook_node_t *) malloc(sizeof(hook_node_t));
                head->ref = callback;
                head->next = NULL;
                prev->next = head;
                break;
            }

            prev = head;
            head = head->next;
        }
    } else if (strcmp(type, "pre_init") == 0) {
        hook_node_t *head = STATE->pre_init_hooks;
        hook_node_t *prev = head;
        while(1) {
            if (!head) {
                head = (hook_node_t *) malloc(sizeof(hook_node_t));
                head->ref = callback;
                head->next = NULL;
                prev->next = head;
                break;
            }

            prev = head;
            head = head->next;
        }
    } else if (strcmp(type, "cursor") == 0) {
        hook_node_t *head = STATE->cursor_hooks;
        hook_node_t *prev = head;
        while(1) {
            if (!head) {
                head = (hook_node_t *) malloc(sizeof(hook_node_t));
                head->ref = callback;
                head->next = NULL;
                prev->next = head;
                break;
            }

            prev = head;
            head = head->next;
        }
    } else if (strcmp(type, "key") == 0) {
        hook_node_t *head = STATE->key_hooks;
        hook_node_t *prev = head;
        while(1) {
            if (!head) {
                head = (hook_node_t *) malloc(sizeof(hook_node_t));
                head->ref = callback;
                head->next = NULL;
                prev->next = head;
                break;
            }

            prev = head;
            head = head->next;
        }
    } else if (strcmp(type, "tick") == 0) {
        hook_node_t *head = STATE->tick_hooks;
        hook_node_t *prev = head;
        while(1) {
            if (!head) {
                head = (hook_node_t *) malloc(sizeof(hook_node_t));
                head->ref = callback;
                head->next = NULL;
                prev->next = head;
                break;
            }

            prev = head;
            head = head->next;
        }
    } else if (strcmp(type, "resize") == 0) {
        hook_node_t *head = STATE->resize_hooks;
        hook_node_t *prev = head;
        while(1) {
            if (!head) {
                head = (hook_node_t *) malloc(sizeof(hook_node_t));
                head->ref = callback;
                head->next = NULL;
                prev->next = head;
                break;
            }

            prev = head;
            head = head->next;
        }
    } else return luaL_error(L, "invalid hook type");

    return 0;
}

int l_require(lua_State *L)
{
    const char *namespace = lua_tostring(L, 1);
    if (!namespace) return luaL_error(L, "expected type `string` as parameter #1");


    const char *script = lua_tostring(L, 2);
    if (!script) return luaL_error(L, "expected type `string` as parameter #2");

    size_t path_len = strlen(namespace) + strlen(script) + 15;
    char *path = (char *) malloc(path_len);
    sprintf(path, "mods/%s/lua/%s.lua", namespace, script);

    if (luaL_dofile(L, path)) {
        error("error while loading mod %s: %s", namespace, lua_tostring(L, -1));
    }

    return 0;
}
