#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace xxlib
{
	public ref class Ranker
	{
	public:
		Ranker();
		~Ranker();

		void Add(Int64 id, Int64 score);
		void Update(Int64 id, Int64 oldScore, Int64 newScore);

		// 填充两个数组并返回实际个数. num 为填充行数限制. 传入的 id 对应的数据在 num / 2 的数据行.
		int FillRanks(Int64 id, Int64 score, int num, array<Int64>^ outIDs, array<int>^ outRanks);
		int GetRank(Int64 score);
	protected:
		void *ranker;
	};
}
