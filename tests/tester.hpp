
# pragma once

# include "vector_tests.hpp"
# include "list_tests.hpp"
# include "map_tests.hpp"
# include "stack_tests.hpp"
# include "queue_tests.hpp"
# include "deque_tests.hpp"
# include "multimap_tests.hpp"
# include "set_tests.hpp"
# include "multiset_tests.hpp"


# define TEST_DIR "__TESTER__/"

/*
* TEST DIR can be commented and the log will be created in the
* test dirrectory (the dirrectory where the tester code is implented).
*/
# ifndef TEST_DIR
#  define TEST_DIR ""
# endif

/*
* Each filename can be edited witout change it default value
* re-defining it.
*/

/// FT linear shared filenames
# ifndef FT_VECTOR_FILENAME_SHARED
#  define FT_VECTOR_FILENAME_SHARED "ft_shared_vector_test"
# endif
# ifndef FT_LIST_FILENAME_SHARED
#  define FT_LIST_FILENAME_SHARED "ft_shared_list_test"
# endif
# ifndef FT_DEQUE_FILENAME_SHARED
#  define FT_DEQUE_FILENAME_SHARED "ft_shared_deque_test"
# endif

/// STD linear shared filenames
# ifndef STD_VECTOR_FILENAME_SHARED
#  define STD_VECTOR_FILENAME_SHARED "std_shared_vector_test"
# endif
# ifndef STD_LIST_FILENAME_SHARED
#  define STD_LIST_FILENAME_SHARED "std_shared_list_test"
# endif
# ifndef STD_DEQUE_FILENAME_SHARED
#  define STD_DEQUE_FILENAME_SHARED "std_shared_deque_test"
# endif

/// FT tree shared filenames
# ifndef FT_MAP_FILENAME_SHARED
#  define FT_MAP_FILENAME_SHARED "ft_shared_map_test"
# endif
# ifndef FT_MULTIMAP_FILENAME_SHARED
#  define FT_MULTIMAP_FILENAME_SHARED "ft_shared_multimap_test"
# endif
# ifndef FT_SET_FILENAME_SHARED
#  define FT_SET_FILENAME_SHARED "ft_shared_set_test"
# endif
# ifndef FT_MULTISET_FILENAME_SHARED
#  define FT_MULTISET_FILENAME_SHARED "ft_shared_multiset_test"
# endif

/// STD tree shared filenames
# ifndef STD_MAP_FILENAME_SHARED
#  define STD_MAP_FILENAME_SHARED "std_shared_map_test"
# endif
# ifndef STD_MULTIMAP_FILENAME_SHARED
#  define STD_MULTIMAP_FILENAME_SHARED "std_shared_multimap_test"
# endif
# ifndef STD_SET_FILENAME_SHARED
#  define STD_SET_FILENAME_SHARED "std_shared_set_test"
# endif
# ifndef STD_MULTISET_FILENAME_SHARED
#  define STD_MULTISET_FILENAME_SHARED "std_shared_multiset_test"
# endif

/// FT targeted test filenames
# ifndef FT_VECTOR_FILENAME
#  define FT_VECTOR_FILENAME "ft_vector_test"
# endif
# ifndef FT_LIST_FILENAME
#  define FT_LIST_FILENAME "ft_list_test"
# endif
# ifndef FT_MAP_FILENAME
#  define FT_MAP_FILENAME "ft_map_test"
# endif
# ifndef FT_STACK_FILENAME
#  define FT_STACK_FILENAME "ft_stack_test"
# endif
# ifndef FT_QUEUE_FILENAME
#  define FT_QUEUE_FILENAME "ft_queue_test"
# endif
# ifndef FT_DEQUE_FILENAME
#  define FT_DEQUE_FILENAME "ft_deque_test"
# endif
# ifndef FT_MULTIMAP_FILENAME
#  define FT_MULTIMAP_FILENAME "ft_multimap_test"
# endif
# ifndef FT_SET_FILENAME
#  define FT_SET_FILENAME "ft_set_test"
# endif
# ifndef FT_MULTISET_FILENAME
#  define FT_MULTISET_FILENAME "ft_multiset_test"
# endif

/// STD targeted test filenames
# ifndef STD_VECTOR_FILENAME
#  define STD_VECTOR_FILENAME "std_vector_test"
# endif
# ifndef STD_LIST_FILENAME
#  define STD_LIST_FILENAME "std_list_test"
# endif
# ifndef STD_MAP_FILENAME
#  define STD_MAP_FILENAME "std_map_test"
# endif
# ifndef STD_STACK_FILENAME
#  define STD_STACK_FILENAME "std_stack_test"
# endif
# ifndef STD_QUEUE_FILENAME
#  define STD_QUEUE_FILENAME "std_queue_test"
# endif
# ifndef STD_DEQUE_FILENAME
#  define STD_DEQUE_FILENAME "std_deque_test"
# endif
# ifndef STD_MULTIMAP_FILENAME
#  define STD_MULTIMAP_FILENAME "std_multimap_test"
# endif
# ifndef STD_SET_FILENAME
#  define STD_SET_FILENAME "std_set_test"
# endif
# ifndef STD_MULTISET_FILENAME
#  define STD_MULTISET_FILENAME "std_multiset_test"
# endif