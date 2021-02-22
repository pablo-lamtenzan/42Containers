
# pragma once

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

/// FT targeted tests filenames
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

/// STD targeted tests filenames
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

template <typename, typename>
struct are_same
{ enum { cond = false }; };

template <typename T>
struct are_same<T, T>
{ enum { cond = true }; };

# define ARRAY_SIZE(x) sizeof(x) / sizeof(*x)

/**
 * 	@param filename The output filename.
 * 	@param tests An array of pointer to function.
 * 	@param amount The amount of tests to launch == ARRAY_SIZE(tests).
 * 	@return Nothing.
 * 
 * 	@brief Launch the tests those are indexed in @p tests ,
 * 	@p amount times and write a log of thoses testes in @p filename .
 * 
 * 	NOTE: *tests must follow the signature: void (*const)(std::ofstream&)
*/
inline static void start_tests(const std::string& filename, void (*const tests[])(std::ofstream&), size_t amount)
{
	std::ofstream fd;

	fd.open(filename);

	for (size_t i = 0 ; i < amount ; i++)
		tests[i](fd);

	fd.close();
}