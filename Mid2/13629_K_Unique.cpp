#include <utility>

template<typename Iterator>
Iterator k_unique(Iterator start, Iterator end, int k) {
    if (start == end) return end;
    Iterator ans = start;
    int count = 1;
    while (++start != end) {
        if (*start != *ans) {
            *(++ans) = std::move(*start);
            count = 1;
        } else {
            if (++count <= k) *(++ans) = std::move(*start);
        }
    }
    return ++ans;
}