/**
 * Created by Simon on 30.11.2020.
 */

#include "buffer.h"

LRESULT CALLBACK create_buffer(_Out_ LPBUFFER* pp_buffer) {
    LPBUFFER buffer = (LPBUFFER) malloc(1 * sizeof(struct _BUFFER));
    if (buffer == NULL) {
        return LR_POINTER_INIT;
    }

    memset(buffer, 0, sizeof(struct _BUFFER));

    glGenBuffers(1, &buffer->_buffer_id);

    CHANGE_OWNER(pp_buffer, buffer);
    return LR_SUCCESS;
}

LRESULT fill_buffer(_In_ LPBUFFER const p_buffer,
                    _In_ LPFLOAT const  p_data,
                    _In_ const UINT8    stride,
                    _In_ const UINT32   size) {
    if (p_data != NULL) {
        p_buffer->_stride = stride;

        glBindBuffer(GL_ARRAY_BUFFER, p_buffer->_buffer_id);
        glBufferData(GL_ARRAY_BUFFER, size, p_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}

LRESULT destroy_buffer(_InOut_opt_ LPBUFFER p_buffer) {
    if (p_buffer != NULL) {
        glDeleteBuffers(1, &p_buffer->_buffer_id);
        FREE_MEMORY(p_buffer);
        return LR_SUCCESS;
    }
    return LR_NULL_POINTER;
}
