add_library(data_structures STATIC)

target_sources(data_structures
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
            data_structures.cxx

            binary_tree.cxx
            doubly_linked_list.cxx
            inplace_vector.cxx
            linked_list.cxx
            rope.cxx
    )

target_compile_features(data_structures PUBLIC cxx_std_23)
