# Picks the first target name that actually exists out of several candidates
# (different SDL2 releases/build modes create different alias names).
function(doengine_resolve_target OUT_VAR)
    foreach(_cand ${ARGN})
        if(TARGET ${_cand})
            set(${OUT_VAR} ${_cand} PARENT_SCOPE)
            return()
        endif()
    endforeach()
    message(FATAL_ERROR "DOEngine: none of these targets exist: ${ARGN}")
endfunction()
