#include <iostream>
#include <vector>
#include <random>

int shellsort(std::vector<int> &v) {
    size_t i, j, k;
    int t;

    for (k = v.size() / 2; k > 0; k /= 2) {
        for (i = k; i < v.size(); ++i) {
            t = v[i];

            for (j = i; j >= k; j -= k) {
                if (t < v[j-k]) {
                    v[j] = v[j-k];
                }
                else {
                    break;
                }
            }

            v[j] = t;
        }
    }

    return 0;
}


void generateRandomVector(std::vector<int> &v) {
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<size_t> distribution_size(5,30);
    const size_t SIZE = distribution_size(random_engine);

    for (size_t i = 0; i < SIZE; ++i) {
        std::uniform_int_distribution<int> distribution_number(-50, 50);
        v.push_back(distribution_number(random_engine));
    }
}


void print(const std::vector<int> &v) {
    for (const auto &i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> v;

    for (int i = 0; i < 8; ++i) {
        std::cout << "BEFORE SHELLSORT:\t";
        generateRandomVector(v);
        print(v);
        shellsort(v);
        std::cout << "AFTER SHELLSORT:\t";
        print(v);
        std::cout << std::endl;
        v.clear();
    }

    return 0;
}
