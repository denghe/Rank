#include "Stdafx.h"

namespace xxlib
{
	Ranker::Ranker()
	{
		ranker = Ranker_Alloc();
	}

	Ranker::~Ranker()
	{
		Ranker_Free(ranker);
	}

	void Ranker::Add(Int64 id, Int64 score)
	{
		Ranker_Add(ranker, id, score);
	}

	void Ranker::Update(Int64 id, Int64 oldScore, Int64 newScore)
	{
		Ranker_Update(ranker, id, oldScore, newScore);
	}

	int Ranker::FillRanks(Int64 id, Int64 score, int num, array<Int64>^ outIDs, array<int>^ outRanks)
	{
		if (num > outIDs->Length || num > outRanks->Length)
		{
			throw gcnew Exception("outIDs or outRanks's Length is not enough!");
		}
		pin_ptr<Int64> outIDs_pin_ptr = &outIDs[0];
		long long* outIDs_ptr = outIDs_pin_ptr;

		pin_ptr<int> outRanks_pin_ptr = &outRanks[0];
		int* outRanks_ptr = outRanks_pin_ptr;

		return Ranker_FillRanks(ranker, id, score, num, outIDs_ptr, outRanks_ptr);
	}

	int Ranker::GetRank(Int64 score)
	{
		return Ranker_GetRank(ranker, score);
	}
}
