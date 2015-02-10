#include <iostream>
#include <stdlib.h>
#include <vector>
#include <functional>
#include <string>
#include <queue>
#include <time.h>
#include <set>
#include <math.h>
using namespace std;

int p = 1000003; //smallest prime > 1 million
int num_distinct_v1(vector<int> nums, float error) 
{   
    srand(time(NULL));
    int a = rand() % p;

    int t = 96 / (error * error);
    
    priority_queue<int> t_smallest;
    set<int> t_smallest_set;

    for(int i = 0; i < nums.size(); i++) {
        int hash_val = (a * nums[i]) % p;
        if(t_smallest_set.count(hash_val) > 0) {
            continue;
        }
        else if(t_smallest.size() < t) {
            t_smallest.push(hash_val);
            t_smallest_set.insert(hash_val);
        }
        else {
            size_t largest_val = t_smallest.top();
            if(hash_val < largest_val) {
                t_smallest.pop();
                t_smallest.push(hash_val);
                t_smallest_set.erase(largest_val);
                t_smallest_set.insert(hash_val);
            }
        }
    }
    int t_smallest_elt = t_smallest.top();
    return t * p/ t_smallest_elt;
}

int num_distinct_v2(vector<int> nums, int error) 
{
    int limit = 576 / (error * error);
    srand(time(NULL));
    int a = rand() % p;
    int t = 0;
    int aux = 0;
    
    set<int> hashed_to_zero;

    for(int i = 0; i < nums.size(); i++) {
       if(hashed_to_zero.size() > limit) {
            aux += 1;
            aux *= 2;
            aux -= 1;
            i--;
            set<int> new_hashed_to_zero;
            for(set<int>::iterator it = hashed_to_zero.begin(); it != hashed_to_zero.end(); it++) {
                int rehash_val = (a * (*it)) % p;
                rehash_val = rehash_val & aux;
                if(rehash_val == 0) {
                    new_hashed_to_zero.insert(*it);
                }
            }
            hashed_to_zero = new_hashed_to_zero;
        }
        else {
            int hash_val = (a * nums[i]) % p;
            hash_val = hash_val & aux;
            if (hash_val == 0) {
                hashed_to_zero.insert(nums[i]);
            }
        }
    }
    aux += 1;
    aux /= 2;
    return hashed_to_zero.size() * pow(2, aux);
}

int main(int argc, char** argv) 
{
    
    srand(time(NULL));
    vector<int> nums;
    set<int> nums_test;
    for(int i = 0; i < 100000; i++) {
        int j = (rand() % 800);
        j /= 3;
        j *= 3;
        nums.push_back(j);
        nums_test.insert(j);
    }
    std::cout << "smallest hash: " << num_distinct_v1(nums, 1) << '\n';
    cout << "last t bits: " << num_distinct_v2(nums, 1) << '\n';
    cout << "actual set size : " << nums_test.size() << '\n';
}

