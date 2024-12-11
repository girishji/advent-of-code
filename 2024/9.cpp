#include <bits/stdc++.h>
using namespace std;

// Task 1: 6461289671426
// Task 2: 6488291456470

struct block_t {
    int id;
    int size {0};
    int free {0};
    friend ostream& operator<<(ostream& os, const block_t& obj) {
        os << obj.id << ": " << obj.size << " - " << obj.free;
        return os;
    }
};

int main() {
    // freopen("./tmp.txt", "r", stdin);
    freopen("./9.txt", "r", stdin);
    list<block_t> disk;
    int id = 0;
    bool free = false;
    for (char ch; cin >> ch; ) {
        int sz = ch - '0';
        if (free) {
            disk.back().free = sz;
        } else {
            block_t block {id, sz, 0};
            disk.push_back(block);
            ++id;
        }
        free = !free;
    }
    list<block_t> saved(disk);
    for (auto be = disk.begin(), en = prev(disk.end()); be != en; ) {
        if (be->free == 0) {
            ++be;
        } else {
            if (en->size > be->free) {
                block_t block {en->id, be->free, 0};
                en->size -= be->free;
                be->free = 0;
                disk.insert(next(be), block);  // works even if at end()
            } else {
                block_t block {en->id, en->size, be->free - en->size};
                be->free = 0;
                en = disk.erase(en);  // returns iterator to next item
                en = prev(en);
                disk.insert(next(be), block);
            }
        }
    }

    auto chksum = [&disk]() -> long long {
        int i = 0;
        long long chksum = 0;
        for (const auto& b : disk) {
            for (int j = 0; j < b.size; j++) {
                chksum += i++ * b.id;
            }
            i += b.free;
        }
        return chksum;
    };
    cout << chksum() << endl;

    // Part 2
    disk = saved;
    for (auto it = prev(disk.end()); it != disk.end(); it--) {
        for (auto dst = disk.begin(); dst != it; dst++) {
            if (it->size <= dst->free) {
                block_t block {it->id, it->size, dst->free - it->size};
                dst->free = 0;
                disk.insert(next(dst), block);
                const auto& prev_block = prev(it);
                prev_block->free += it->free + it->size;
                it->size = 0;
                it->free = 0;
                break;
            }
        }
    }

    // for (const auto& el : disk) { cout << el << " "; }; cout << endl;
    cout << chksum() << endl;
}

