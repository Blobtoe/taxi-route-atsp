#include "adjacency_matrix.hpp"
#include "path.hpp"
#include <vector>

namespace tsp
{
	class held_karp {
	
	public:

		held_karp() = delete;
		held_karp(const Adjacency_Matrix& matrix);

		Path run();

	private:
		
		struct visited_mask {
			
			int mask_;

			visited_mask(int mask)
				: mask_{ mask }
			{};

			bool operator==(const visited_mask& rhs) { return (mask_ == rhs.mask_); };
			bool operator!=(const visited_mask& rhs) { return !(*this == rhs); };
			
			static int sum_masks(const visited_mask& rhs, const visited_mask& lhs) 
				{ return lhs.mask_|rhs.mask_; };

			static int and_masks(const visited_mask& rhs, const visited_mask &lhs)
			{ return lhs.mask_ & rhs.mask_; }

			static visited_mask int_to_mask(int number) 
				{ return visited_mask(1 << number); };
			
		};

		Adjacency_Matrix matrix_;
		std::vector<std::vector<int>> operations_;
		std::vector<std::vector<int>> travel_vec_;
		visited_mask full_mask_;

		void init_matrix();
		int h_k(visited_mask mask, int city);

		Path get_path(int cost);
	};
}