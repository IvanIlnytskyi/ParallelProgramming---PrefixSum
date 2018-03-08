#include "Implementation.h"
#include <fstream>
using namespace std;
void main()
{
	ofstream results("results.txt");
	results << "power\tseq\tpar\n";
	for (size_t i = 5; i <= 20; ++i)
	{
		results << i << '\t';
		size_t size = pow(2, i);
		vector<int> vec_seq = create_test_array(size);
		vector<int> vec_par = create_test_array(size);
		high_resolution_clock::time_point seq_start = high_resolution_clock::now();
		seqPrefixSum(vec_seq);
		high_resolution_clock::time_point seq_end = high_resolution_clock::now();

		results << duration_cast<microseconds>(seq_end - seq_start).count() << '\t';
		cout << "seqPrefixSum execution time " << duration_cast<microseconds>(seq_end - seq_start).count() << endl;

		high_resolution_clock::time_point par_start = high_resolution_clock::now();
		parPrefixSum(vec_seq);
		high_resolution_clock::time_point par_end = high_resolution_clock::now();

		cout << "parPrefixSum execution time " << duration_cast<microseconds>(par_end - par_start).count() << endl;
		results << duration_cast<microseconds>(par_end - par_start).count() << '\n';
	}
	system("Pause");
}
