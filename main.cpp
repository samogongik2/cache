#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
using namespace std;

class LFU_cache{
public:
    LFU_cache(int size_cache) : size_cache(size_cache) {}

    int get(int key){
        if (data.find(key) != data.end()){
            return 1;
        }
        return 0;
    }
    int put(int key, int element){
        if (size_cache == 0){
            cout << "нулевой размер кэша" << endl;
            return -1;
        }
        if (data.find(key) != data.end()){

            data[key].first = element;
            int old_count = data[key].second;
            auto old_count_it = std::find(arr_count.begin(), arr_count.end(), old_count);
            arr_count.erase(old_count_it);
            int new_count = old_count + 1;
            data[key].second = new_count;
            arr_count.push_back(new_count);

            list_key[old_count].remove(key);
            if (list_key[old_count].empty()){
                list_key.erase(old_count);
            }
            list_key[new_count].push_back(key);

        }

        else if (data.size() < size_cache){
            data[key] = {element, 1};
            list_key[1].push_back(key);
            arr_count.push_back(1);
        }

         else {
            auto min_it = arr_count.begin();

            for (auto elem_it = arr_count.begin(); elem_it != arr_count.end(); elem_it++){
                if (*elem_it < *min_it){
                    min_it = elem_it;
                }
            }

            int min_count = *min_it;
            arr_count.erase(min_it);
            int key_min_used_element = list_key[min_count].front();

            data.erase(key_min_used_element);
            list_key[min_count].pop_front();
            if (list_key[min_count].empty()){
                list_key.erase(min_count);
            }
            data[key] = { element, 1 };
            arr_count.push_back(1);
            list_key[1].push_back(key);
        }
    }

private:
    int size_cache;
    unordered_map<int, pair <int,int>> data;
    unordered_map <int, list<int>> list_key;
    list <int> arr_count;
};

int main()
{
   int size_cache = 0, quanity_element = 0, kol = 0;

   cin >> size_cache >> quanity_element;
   LFU_cache cache(size_cache);

   for (int i = 0; i < quanity_element; i++){
        int element, key;
        cin >> element;
        key = element;
        kol += cache.get(key);
        cache.put(key, element);
   }

   cout << kol;
}
