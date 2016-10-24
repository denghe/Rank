#pragma once
#define WIN32_LEAN_AND_MEAN
#include "bpptree_map.h"
#include "bind_second.h"
#include <functional>

// ��������
template<typename SCORE, typename ID>
struct RankerCore
{
	typedef bpptree_multimap<SCORE, ID, std::greater<SCORE>> RankDict;
	typedef bind_second<typename RankDict> BoundScore;
	typedef typename RankDict::iterator RankDictIter;

	// ���
	void Add(ID const &id, SCORE const &score)
	{
		rd.emplace(score, id);
	}

	// ����
	void Update(ID const &id, SCORE const &oldScore, SCORE const &newScore)
	{
		if (oldScore == newScore) return;
		auto range = rd.equal_range(oldScore);
		if (range.first != range.second)
		{
			auto it = std::lower_bound(BoundScore(range.first), BoundScore(range.second), id).it;
			if (it != rd.end() && it->second == id)
			{
				rd.erase(it);
			}
		}
		range = rd.equal_range(newScore);
		if (range.first != range.second)
		{
			auto it = std::upper_bound(BoundScore(range.first), BoundScore(range.second), id).it;
			rd.emplace_hint(it, newScore, id);
		}
		else
		{
			rd.emplace(newScore, id);
		}
	}

	// ���� id, score ��ѯ num ��Χ�е����� �����ص�����. num �������ʵ����������
	typename RankDict::iterator GetRanks(ID const &id, SCORE const &score, size_t &num)
	{
		auto range = rd.equal_range(score);
		auto it = range.first;
		if (range.first != range.second)
		{
			it = lower_bound(BoundScore(range.first), BoundScore(range.second), id).it;
		}
		auto frontNums = rd.rank(it); // it - rd.cbegin()
		auto rearNums = rd.size() - frontNums;
		if (frontNums + rearNums >= num)
		{
			// �ƶ� it ȷ�� num �����㹻. 
			if (frontNums < (num >> 1))
			{
				it -= frontNums;
			}
			else
			{
				it -= (num >> 1);
			}
		}
		else
		{
			it = rd.begin();
			num = frontNums + rearNums;
		}
		return it;
	}

	// �� Rank
	size_t GetRank(SCORE score)
	{
		return rd.lower_rank(score) + 1;
	}

protected:
	RankDict rd;
};
