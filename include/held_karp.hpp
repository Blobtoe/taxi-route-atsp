#include "adjacency_matrix.hpp"
#include "path.hpp"
#include <vector>

namespace tsp
{
	class held_karp {
	
	public:
		held_karp(const Adjacency_Matrix& matrix);
		held_karp(const held_karp&) = default;
		held_karp& operator=(const held_karp& d) = default;
		~held_karp() = default;

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
		std::vector<std::vector<std::pair<int, int>>> saved_ops_;
		visited_mask full_mask_;

		void init_matrix();
		int h_k(visited_mask mask, int city);

		Path get_path(int cost);
	};
}