#pragma warning(disable:4996)
#include "Ranker.h"
#include "RankerCore.h"

typedef RankerCore<int64_t, int64_t> R;

void* Ranker_Alloc()
{
	return new RankerCore<int64_t, int64_t>();
}
void Ranker_Free(void *p)
{
	delete (R*)p;
}
void Ranker_Add(void *p, int64_t id, int64_t score)
{
	auto ranker = (R*)p;
	ranker->Add(id, score);
}
void Ranker_Update(void *p, int64_t id, int64_t oldScore, int64_t newScore)
{
	auto ranker = (R*)p;
	ranker->Update(id, oldScore, newScore);
}
int Ranker_FillRanks(void *p, int64_t id, int64_t score, int num, long long *outIds, int* outRanks)
{
	auto ranker = (R*)p;
	size_t n = num;
	auto iter = ranker->GetRanks(id, score, n);
	auto lastScore = iter->first;
	auto rank = (int)ranker->GetRank(iter->first);
	for (size_t i = 0; i < n; i++)
	{
		if (iter->first != lastScore)
		{
			lastScore = iter->first;
			++rank;
		}
		outIds[i] = iter->second;
		outRanks[i] = rank;
		++iter;
	}
	return (int)n;
}
int Ranker_GetRank(void *p, int64_t score)
{
	auto ranker = (R*)p;
	return (int)ranker->GetRank(score);
}
