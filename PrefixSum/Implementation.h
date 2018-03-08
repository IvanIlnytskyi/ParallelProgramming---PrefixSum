#pragma once
#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>  
#include <chrono>


using namespace std;
using namespace std::chrono;


void printArr(std::vector<int>& arr)
{
	for (int& item : arr)
	{
		cout << item << " ";
	}
	cout << endl;
}

std::vector<int>  create_test_array(size_t capacity)
{
	std::vector<int> vec(capacity, 1);
	vec.insert(vec.begin(), 0);
	return vec;
}

void seqPrefixSum(std::vector<int>& arr)
{
	for (size_t i = 1; i < arr.size(); ++i)
	{
		arr[i] += arr[i - 1];
	}
}

void summator(int level, int num, int proc, std::vector<int>& arr)
{
	int lower_bound = proc * num;
	int upper_bound = proc * (num + 1);
	for (int sum_index = lower_bound + pow(2, level) - 1; sum_index < upper_bound; sum_index += pow(2, level))
	{
		arr[sum_index] += arr[sum_index - pow(2, level - 1)];
	}
}

void down_summator(int level, int num, int proc, std::vector<int>& arr)
{
	int lower_bound = proc * num;
	int upper_bound = proc * (num + 1);
	for (int sum_index = lower_bound + pow(2, level) - 1; sum_index < upper_bound; sum_index += pow(2, level))
	{
		int temp_val = arr[sum_index];
		arr[sum_index] += arr[sum_index - pow(2, level - 1)];
		arr[sum_index - pow(2, (level - 1))] = temp_val;
	}
}

void parPrefixSum(std::vector<int>& arr)
{
	const int max_cores = 4;
	size_t length = arr.size();
	size_t depth = log2(length);
	for (size_t level = 1; level < depth + 1; level++) {
		int proc = pow(2, level);
		int core_number = length / proc;
		if (core_number > max_cores)
		{
			core_number = max_cores;
			proc = length / core_number;
		}

		std::thread * t = new thread[core_number];
		for (int i = 0; i < core_number; i++)
		{
			t[i] = std::thread(summator, level, i, proc, std::ref(arr));
		}
		for (int i = 0; i < core_number; ++i) {
			t[i].join();
		}
	}

	arr[length - 1] = arr[length - 2];
	arr[length - 2] = 0;

	for (size_t level = depth; level > 0; level--) {
		int proc = pow(2, level);
		int core_number = length / proc;
		if (core_number > max_cores)
		{
			core_number = max_cores;
			proc = length / core_number;
		}
		std::thread * t = new thread[core_number];
		for (int i = 0; i < core_number; i++)
		{
			//Add code here!
			//Modify!!!      
			int start = 0; int end = 0; int step = 0; int step1 = 1;
			t[i] = std::thread(down_summator, level, i, proc, std::ref(arr));
		}
		for (int i = 0; i < core_number; ++i) {
			t[i].join();
		}
	}
}

