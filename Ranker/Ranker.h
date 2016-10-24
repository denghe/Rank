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

		// ����������鲢����ʵ�ʸ���. num Ϊ�����������. ����� id ��Ӧ�������� num / 2 ��������.
		int FillRanks(Int64 id, Int64 score, int num, array<Int64>^ outIDs, array<int>^ outRanks);
		int GetRank(Int64 score);
	protected:
		void *ranker;
	};
}
