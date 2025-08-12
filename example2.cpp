// g++ -g -o example2 example2.cpp -L//home/tobiasxu/dev/light-runtime/thirdparty/cnpy/build -lcnpy -lz --std=c++11
// export LD_LIBRARY_PATH=/home/tobiasxu/dev/light-runtime/thirdparty/cnpy/build:$LD_LIBRARY_PATH

#include"cnpy.h"
#include<complex>
#include<cstdlib>
#include<iostream>
#include<map>
#include<string>

const int Nx = 128;
const int Ny = 64;
const int Nz = 32;

int main()
{
    //test empty save
    std::vector<int64_t> npy1;
    cnpy::npz_save("out.npz","item/ubf_finder_lt_v2_tags_v1_p|values",&npy1[0], {npy1.size()},"a" );
    //test int64 save
    std::vector<int64_t> npy2{1, 1, 10};
    cnpy::npz_save("out.npz","item/ubf_mp_lt_v2_cat2_v1_p|dense_shape", &npy2[0], {npy2.size()}, "a");
    //test int save
    std::vector<int> myint{1, 2, 3, 4, 5};
    cnpy::npz_save("out.npz","myint", &myint[0], {myint.size()}, "a");
    //test string save
    std::vector<std::string> my_strs;
    my_strs.push_back("hello");
    my_strs.push_back("1231234");
    my_strs.push_back("whosyourdady");
    my_strs.push_back("super mario!");
    std::vector<size_t> str_lens;
    for(const auto& str : my_strs) {
      str_lens.push_back(str.size());
    }
    std::cout<< str_lens[2] <<std::endl;
    std::vector<char> continuous_buffer;
    for (const auto& str : my_strs) {
    continuous_buffer.insert(continuous_buffer.end(), str.begin(), str.end());
    }
    cnpy::npz_save_string("out.npz","mystring",continuous_buffer.data(), str_lens,"a" );

    //test fp16 save
    cnpy::npz_t cnpy_npz_obj = cnpy::npz_load("fp16_array.npz");
    auto npz_array = cnpy_npz_obj["fp16_data"];
    std::vector<std::vector<size_t>> shapes;
    shapes.emplace_back(npz_array.shape.begin(), npz_array.shape.end());
    void* data = npz_array.data<void>();
    cnpy::npz_save_fp16("out.npz","myfp16",data,shapes[0], "a");


}
