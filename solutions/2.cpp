#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    
    size_t t;
    fin >> t;
    for (size_t i = 0; i < t; i++) {
        size_t n;
        int64_t p;
        fin >> n >> p;
        int64_t ex = -1;
        size_t s1 = 0, s2 = 0;
        vector<int64_t> cp(n);
        for (size_t j = 0; j < n; j++) {
            fin >> cp[j];
            if (j) cp[j] += cp[j - 1];
        }
        size_t l = 0, r = 0;
        int64_t sum = cp[0];

        while (r < n) {
            sum = cp[r];
            if (l) sum -= cp[l - 1];
            if (sum >= p) {
                if (ex > sum || ex == -1) {
                    ex = sum;
                    s1 = l;
                    s2 = r;
                }
                l++;
            } else {
                r++;
            }
        }
        fout << "Case #" << i + 1 << ": " << s1 << " " << s2 << '\n';
    }
    return 0;
}
