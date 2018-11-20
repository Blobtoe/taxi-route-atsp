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
		
		struct bit_mask {
			
			int mask_;

			bit_mask(int mask)
				: mask_{ mask }
			{};

			bool operator==(const bit_mask& rhs) { return (mask_ == rhs.mask_); };
			bool operator!=(const bit_mask& rhs) { return !(*this == rhs); };
			
			static int sum_masks(const bit_mask& rhs, const bit_mask& lhs) 
				{ return lhs.mask_|rhs.mask_; };

			static int and_masks(const bit_mask& rhs, const bit_mask &lhs)
			{ return lhs.mask_ & rhs.mask_; }

			static bit_mask int_to_mask(int number) 
				{ return bit_mask(1 << number); };
			
		};

		Adjacency_Matrix matrix_;
		std::vector<std::vector<int>> operations_;
		std::vector<std::vector<int>> travel_vec_;
		bit_mask full_mask_;

		void init_matrix();
		int h_k(bit_mask mask, int city);

		Path get_path(int cost);
	};
}