#ifndef __RIYA_GPU_ARRAY__
#define __RIYA_GPU_ARRAY__

#include<amp.h>
#include<utility>

template<class T,std::size_t dim>
concurrency::array<T,dim>* create_array(concurrency::accelerator& accel,std::size_t size){
	return new concurrency::array<T,dim>(size,accel.get_default_view());
}

/*
template<class T,std::size_t dim>
void access_array(concurrency::array<T,dim>& vGArray,std::function<void(concurrency::array<T,dim>&)> function){
	concurrency::array_view<T,dim> vGArrayView = vGArray;
	function(vGArray);
}
*/

template<class T,int dim,class F>
void access_array(concurrency::array<T,dim>& vGArray,F&& function){
	concurrency::array_view<T,dim> vGArrayView = vGArray;
	function(vGArrayView);
}

template<class F>
void parallel_calculation(concurrency::accelerator& accel,int nums_thread,F&& function){
	concurrency::extent<1> ex;
	ex[0] = nums_thread;
	parallel_for_each(
		accel.get_default_view(),
		ex,
		function
	);
}
#endif
