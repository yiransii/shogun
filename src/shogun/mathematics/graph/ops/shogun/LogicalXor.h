/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Gil Hoben
 */

#ifndef SHOGUN_LOGICAL_XOR_SHOGUN_H_
#define SHOGUN_LOGICAL_XOR_SHOGUN_H_

#include <shogun/mathematics/graph/nodes/LogicalXor.h>
#include <shogun/mathematics/graph/ops/abstract/BinaryOperator.h>

namespace shogun
{
	namespace graph
	{
		namespace op
		{
			IGNORE_IN_CLASSLIST class LogicalXorShogun
			    : public ShogunBinaryOperator<LogicalXorShogun>
			{
			public:
				friend class ShogunBinaryOperator<LogicalXorShogun>;

				LogicalXorShogun(const std::shared_ptr<node::Node>& node)
				    : ShogunBinaryOperator(node)
				{
				}

				std::string_view get_operator_name() const final
				{
					return "LogicalXor";
				}

			protected:
				template <typename T>
				void kernel_implementation(
				    void* input1, void* input2, void* output, const size_t size)
				{
					std::transform(
					    static_cast<const T*>(input1),
					    static_cast<const T*>(input1) + size,
					    static_cast<const T*>(input2), static_cast<T*>(output),
					    [](const T& lhs, const T& rhs) {
						    return (!lhs != !rhs);
					    });
				}

				template <typename T>
				void kernel_scalar_implementation(
				    void* input1, void* input2, void* output, const size_t size,
				    const bool scalar_first)
				{
					if (scalar_first)
					{
						std::transform(
						    static_cast<const T*>(input2),
						    static_cast<const T*>(input2) + size,
						    static_cast<T*>(output), [&input1](const T& val) {
							    return !val !=
							           !(*static_cast<const T*>(input1));
						    });
					}
					else
					{
						std::transform(
						    static_cast<const T*>(input1),
						    static_cast<const T*>(input1) + size,
						    static_cast<T*>(output), [&input2](const T& val) {
							    return !val !=
							           !(*static_cast<const T*>(input2));
						    });
					}
				}
			};
		} // namespace op
	}     // namespace graph
} // namespace shogun

#endif