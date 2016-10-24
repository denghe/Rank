#pragma once
void* Ranker_Alloc();
void Ranker_Free(void *ranker);
void Ranker_Add(void *ranker, long long id, long long score);
void Ranker_Update(void *ranker, long long id, long long oldScore, long long newScore);
int Ranker_FillRanks(void *ranker, long long id, long long score, int num, long long* outIds, int* outRanks);
int Ranker_GetRank(void *ranker, long long score);
