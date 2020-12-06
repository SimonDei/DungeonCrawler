/**
 * Created by Simon on 27.11.2020.
 */

#include "file.h"

LRESULT CALLBACK read_file(_In_  LPCSTR const p_file_path,
                           _Out_ LPCSTR*      pp_file_content) {
    if (p_file_path != NULL) {
        FILE* text_file = fopen(p_file_path, "r");
        if (text_file == NULL) {
            return LR_FILE_NOT_FOUND;
        }

        fseek(text_file, 0, SEEK_END);
        const LONG file_size = ftell(text_file);
        fseek(text_file, 0, SEEK_SET);

        LPSTR content = (LPSTR) calloc(file_size, sizeof(CHAR));
        if (content == NULL) {
            fclose(text_file);
            text_file = NULL;
            return LR_POINTER_INIT;
        }
        
        fread(content, sizeof(CHAR), file_size, text_file);
        
        fclose(text_file);
        text_file = NULL;
        
        CHANGE_OWNER(pp_file_content, content);		
        return LR_SUCCESS;
    }	
    return LR_NULL_POINTER;
}
