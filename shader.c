/**
 * Created by Simon on 27.11.2020.
 */

#include "shader.h"

LRESULT create_shader(_In_  const enum _SHADER_TYPE shader_type,
                      _In_  LPCSTR const            p_shader_source,
                      _Out_ LPSHADER*               pp_shader) {
    if (p_shader_source != NULL) {
        LPSHADER shader = (LPSHADER) malloc(1 * sizeof(struct _SHADER));
        if (shader == NULL) {
            LOG_ERROR("Es konnte kein Speicher für eine _SHADER Struktur allokiert werden!");
            return LR_POINTER_INIT;
        }

        memset(shader, 0, sizeof(struct _SHADER));

        switch (shader_type) {
            case SHADER_TYPE_VERTEX:
                shader->_shader_id = glCreateShader(GL_VERTEX_SHADER);
                break;
            case SHADER_TYPE_FRAGMENT:
                shader->_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            case SHADER_TYPE_GEOMETRY:
                shader->_shader_id = glCreateShader(GL_GEOMETRY_SHADER);
                break;
        }

        glShaderSource(shader->_shader_id, 1, &p_shader_source, NULL);
        glCompileShader(shader->_shader_id);

        INT32 log_length;
        glGetShaderiv(shader->_shader_id, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 0) {
            LPSTR log_message = (LPSTR) malloc(log_length * sizeof(CHAR));
            glGetShaderInfoLog(shader->_shader_id, log_length, &log_length, log_message);
            
            fprintf(stderr, "[ERROR]: Shader konnte nicht erstellt werden: %s!\n", log_message);
            FREE_MEMORY(log_message);
            FREE_MEMORY(shader);

            return LR_OPENGL_CREATE_FAILED;
        }
        
        CHANGE_OWNER(pp_shader, shader);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT destroy_shader(_InOut_opt_ LPSHADER p_shader) {
    if (p_shader != NULL) {
        glDeleteShader(p_shader->_shader_id);
        FREE_MEMORY(p_shader);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}
