/**
 * Created by Simon on 28.11.2020.
 */

#include "program.h"

LRESULT CALLBACK create_program(_Out_ LPPROGRAM* pp_program) {
    LPPROGRAM program = (LPPROGRAM) malloc(1 * sizeof(struct _PROGRAM));
    if (program == NULL) {
        LOG_ERROR("Es konnte kein Speicher für eine _PROGRAM Struktur allokiert werden!");
        return LR_POINTER_INIT;
    }

    memset(program, 0, sizeof(struct _PROGRAM));

    program->_program_id = glCreateProgram();

    INT32 log_length;
    glGetProgramiv(program->_program_id, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 1) {
        LPSTR log_message = (LPSTR) malloc(log_length * sizeof(CHAR));
        glGetProgramInfoLog(program->_program_id, log_length, &log_length, log_message);

        fprintf(stderr, "[ERROR]: Programm konnte nicht erstellt werden: %s!\n", log_message);
        FREE_MEMORY(log_message);
        FREE_MEMORY(program);

        return LR_OPENGL_CREATE_FAILED;
    }
    
    CHANGE_OWNER(pp_program, program);
    return LR_SUCCESS;
}

LRESULT attach_shader_to_program(_In_ LPPROGRAM const         p_program,
                                 _In_ const enum _SHADER_TYPE shader_type,
                                 _In_ LPCSTR const            p_file_path) {
    if (p_program != NULL && p_file_path != NULL) {
        if (p_program->_linked == TRUE) {
            return LR_PROGRAM_LINKED;
        }

        UINT32 current_shader = 0;
        
        switch (shader_type) {
            case SHADER_TYPE_VERTEX:
                p_program->_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
                current_shader = p_program->_vertex_shader_id;
                break;
            case SHADER_TYPE_FRAGMENT:
                p_program->_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
                current_shader = p_program->_fragment_shader_id;
                break;
            case SHADER_TYPE_GEOMETRY:
                p_program->_geometry_shader_id = glCreateShader(GL_GEOMETRY_SHADER);
                current_shader = p_program->_geometry_shader_id;
                break;
        }

        if (current_shader == 0) {
            return LR_OPENGL_CREATE_FAILED;
        }

        LPCSTR shader_source = NULL;
        if (FAILED(read_file(p_file_path, &shader_source))) {
            return LR_FAILED;
        }
        
        glShaderSource(current_shader, 1, &shader_source, NULL);
        glCompileShader(current_shader);
        
        INT32 log_length;
        glGetShaderiv(current_shader, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 1) {
            LPSTR log_message = (LPSTR) malloc(log_length * sizeof(CHAR));
            glGetShaderInfoLog(current_shader, log_length, &log_length, log_message);

            fprintf(stderr, "[ERROR]: Shader konnte nicht erstellt werden: %s!\n", log_message);
            FREE_MEMORY(log_message);

            return LR_OPENGL_CREATE_FAILED;
        }

        glAttachShader(p_program->_program_id, current_shader);
                
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT set_program_vertex_attrib(_In_ const UINT8     attrib_location,
                                  _In_ LPCBUFFER const p_buffer) {
    if (p_buffer != NULL) {
        glBindBuffer(GL_ARRAY_BUFFER, p_buffer->_buffer_id);
        glEnableVertexAttribArray(attrib_location);
        glVertexAttribPointer(attrib_location, p_buffer->_stride, GL_FLOAT, GL_FALSE, p_buffer->_stride * sizeof(FLOAT), NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT set_program_uniform(_In_ LPCPROGRAM const p_program,
                            _In_ LPCSTR const     p_uniform_name,
                            _In_ LPFLOAT const    p_uniform_value) {
    if (p_program != NULL) {
        const INT32 uniform_location = glGetUniformLocation(p_program->_program_id, p_uniform_name);
        glUniformMatrix4fv(uniform_location, 1, GL_FALSE, p_uniform_value);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT set_texture(_In_        LPCSPRITE const p_sprite,
                    _InOut_opt_ LPUINT32 const  p_texture_id) {
    INT32 is_enabled;
    glGetIntegerv(GL_TEXTURE_2D, &is_enabled);
    if (is_enabled == FALSE) {
        glEnable(GL_TEXTURE_2D);
    }

    if (p_sprite == NULL) {
        glBindTexture(GL_TEXTURE_2D, *p_texture_id);
    } else {
        glGenTextures(1, p_texture_id);
        glBindTexture(GL_TEXTURE_2D, *p_texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        ALLEGRO_LOCKED_REGION* face = al_lock_bitmap(p_sprite->_texture, ALLEGRO_PIXEL_FORMAT_RGBA_8888, ALLEGRO_LOCK_READONLY);

        glPixelStorei(GL_UNPACK_ALIGNMENT, face->pixel_size);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (INT32) p_sprite->_width, (INT32) p_sprite->_height, 0, GL_RGBA, GL_UNSIGNED_INT, face->data);

        al_unlock_bitmap(p_sprite->_texture);
    }
    return LR_SUCCESS;
}

LRESULT activate_program(_In_ LPPROGRAM const p_program) {
    if (p_program != NULL) {
        if (p_program->_linked == FALSE) {
            glLinkProgram(p_program->_program_id);
            p_program->_linked = TRUE;
        }
        
        glUseProgram(p_program->_program_id);

        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT deactivate_program(VOID) {
    UINT8 i;
    INT32 is_enabled;
    for (i = 0; i < 10; i++) {		
        glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &is_enabled);
        if (is_enabled == TRUE) {
            glDisableVertexAttribArray(i);
        }
    }

    glGetIntegerv(GL_TEXTURE_2D, &is_enabled);
    if (is_enabled == TRUE) {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
    
    glUseProgram(0);
    return LR_SUCCESS;
}

LRESULT destroy_program(_InOut_opt_ LPPROGRAM p_program) {
    if (p_program != NULL) {
        if (p_program->_vertex_shader_id != 0) {
            glDeleteShader(p_program->_vertex_shader_id);
        }

        if (p_program->_fragment_shader_id != 0) {
            glDeleteShader(p_program->_fragment_shader_id);
        }

        if (p_program->_geometry_shader_id != 0) {
            glDeleteShader(p_program->_geometry_shader_id);
        }
        
        glDeleteProgram(p_program->_program_id);
        FREE_MEMORY(p_program);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}
