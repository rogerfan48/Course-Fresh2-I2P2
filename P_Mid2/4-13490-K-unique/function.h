#if __cplusplus < 201103L
#error Sorry, but this partial-judged problem requires at least C++11.
#endif

template<typename Iterator>
Iterator k_unique(Iterator, Iterator, int);

/**
TODO:
    0. Download the partial judge code and header as `parJudge.cpp` and `function.h` respectively
    1. Create a file `Main.cpp` and implement the template function
    2. OJ will compile your submission like this: `g++ parJudge.cpp Main.cpp` (If `-o` isn't specified , then the output is `a.out`)
    You can compile like above in local.
 */

#include <utility>

template<typename Iterator>
Iterator k_unique(Iterator first, Iterator last, int k) {
    if (first == last) return last;

    Iterator ans = first;
    int count = 1;
    while (++first != last) {
        if (*ans != *first) {
            *(++ans) = std::move(*first);
            count = 1;
        } else {
            if (++count <= k) *(++ans) = std::move(*first);
        }
    }

    return ++ans;
}


// #include <utility>

// template<typename Iterator>
// Iterator k_unique(Iterator first, Iterator last, int k) {
//     if (first == last) return last;

//     Iterator ans = first;
//     int count = 1;
//     while (++first != last) {
//         if (*ans != *first) {
//             if (++ans != first) *ans = std::move(*first);
//             count = 1;
//         } else {
//             if ((++count <= k) && (++ans != first)) *ans = std::move(*first);
//         }
//     }

//     return ++ans;
// }