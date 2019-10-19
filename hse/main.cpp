#include <iostream>
#include <cstring>

struct player {
	int num;
	int efficiency;
};

void OutputAnswer (int max_sum, int counter_player, player* res_team);

void GetInput (int* nn, player** player_array);

int  CompareByNum (const player* t1, const player* t2);

int  CompareByEff (const player* t1, const player* t2);

void MergeSort (player* start_p, player* end_p, int (*comp) (const player*, const player*));

void MergeArrays (player* start_p, player* mid_p, player* end_p, int (*comp) (const player*,

				  const player*));

int GetMaxEffectiveValue (int* res_left, int* res_right, player* player_sorted, int nn);

int BuildMostEffectiveSolidaryTeam (const player* player_array, int nn, int* max_sum,
									int* counter_player, player** res_team);

int main() {
	int nn = 0;
	struct player* player_array = nullptr;
	int max_sum = 0, counter_player = 0;
	player* res_team = nullptr;

	GetInput (&nn, &player_array);

	BuildMostEffectiveSolidaryTeam (player_array, nn, &max_sum, &counter_player, &res_team);

	OutputAnswer (max_sum, counter_player, res_team);

	system("pause");
	return 0;
}

int CompareByNum (const player* t1, const player* t2) {
	return t1->num - t2->num;
}

int CompareByEff (const player* t1, const player* t2) {
	return t1->efficiency - t2->efficiency;
}

void MergeSort (player* start_p, player* end_p, int (*comp) (const player*, const player*)) {
	int cur_size = end_p - start_p;

	if (cur_size == 1) {
		if (comp (start_p, end_p) < 0) {
			player* tmp = start_p;
			start_p = end_p;
			end_p = tmp;
		}

		return;
	}

	int mid = cur_size / 2;
	MergeSort (start_p, start_p + mid, comp);
	MergeSort (start_p + mid, end_p, comp);
	MergeArrays (start_p, start_p + mid, end_p, comp);
}

void MergeArrays (player* start_p, player* mid_p, player* end_p,
				  int (*comp) (const player*, const player*)) {
	int cur_size = end_p - start_p;

	int left = 0, right = 0;

	player* tmp = new player[cur_size];

	for (int ii = 0; ii < cur_size; ++ii) {
		if (start_p + left == mid_p) {
			tmp[ii] = mid_p[right++];
		} else if (mid_p + right == end_p) {
			tmp[ii] = start_p[left++];
		} else if (comp (start_p + left, mid_p + right) > 0) {
			tmp[ii] = mid_p[right++];
		} else {
			tmp[ii] = start_p[left++];
		}
	}

	for (int i = 0; i < cur_size; ++i) {
		start_p[i] = tmp[i];
	}

	delete [] tmp;
}

int GetMaxEffectiveValue (int* res_left, int* res_right, player* player_sorted, int nn) {
	int left = 0;
	int right = 0;

	int cur_sum = 0;
	int max_sum = 0;

	while (right < nn) {
		while (player_sorted[left]  .efficiency +
				player_sorted[left + 1].efficiency >= player_sorted[right].efficiency) {
			cur_sum += player_sorted[right++].efficiency;

			if (right == nn) {
				break;
			}
		}

		if (cur_sum > max_sum) {
			max_sum = cur_sum;
			*res_left  = left;
			*res_right = right;
		}

		while (player_sorted[left]    .efficiency +
				player_sorted[left + 1].efficiency < player_sorted[right].efficiency) {
			cur_sum -= player_sorted[left++].efficiency;
		}
	}

	if (player_sorted[nn - 1].efficiency > max_sum) {
		max_sum = player_sorted[nn - 1].efficiency;
		*res_left  = nn - 1;
		*res_right = nn;
	}

	return max_sum;
}

int BuildMostEffectiveSolidaryTeam (const player* player_array, int nn, int* max_sum,
									int* counter_player, player** res_team) {

	struct player* player_sorted = new player[nn];

	std::memcpy (player_sorted, player_array, nn * sizeof (player));

	MergeSort (player_sorted, player_sorted + nn, &CompareByEff);

	int res_left  = 0;
	int res_right = 0;

	*max_sum = GetMaxEffectiveValue (&res_left, &res_right, player_sorted, nn);

	*counter_player = res_right - res_left;

	*res_team = new player[*counter_player];

	for (int i = 0; i < *counter_player; ++i) {
		(*res_team) [i].num = player_sorted[res_left + i].num;
		(*res_team) [i].efficiency = player_sorted[res_left + i].efficiency;
	}

	MergeSort (*res_team, (*res_team) + *counter_player, &CompareByNum);

	delete [] player_sorted;

	return 0;
}

void OutputAnswer (int max_sum, int counter_player, player* res_team) {
	std::cout << max_sum << std::endl;

	for (int i = 0; i < counter_player; ++i) {
		std::cout << res_team[i].num << " ";
	}
}

void GetInput (int* nn, player** player_array) {
	std::cin >> *nn;

	*player_array = new player[*nn];

	for (int i = 0; i < *nn; ++i) {
		std::cin >> (*player_array) [i].efficiency;
		(*player_array) [i].num = i + 1;
	}
}
