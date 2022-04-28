
#include <iostream>
#include <exception>
#include <random>
#include <functional>
#include <thread>
#include <concepts>

// anonymous space
namespace
{
	// ------------------------------------------ manual seeder
	namespace manual { decltype(auto) seeder(unsigned seed_arg) { return seed_arg; }; }

	// ------------------------------------------ automatic seeder (if hardware supports, true random seed will be generated.
	//                                            if not, pseudo-random seed will be generated)
	namespace automatic {
		decltype(auto) seeder()
		{
			std::random_device rng;
			if (rng.entropy())
				return rng();
			else
			{
				auto another_thread{ std::thread{} };
				std::hash<std::thread::id> hasher;
				auto another_thread_hashed_id{ hasher(another_thread.get_id()) };
				another_thread.join();
				auto this_thread_now{ std::chrono::system_clock::now() };
				auto this_thread_now_time_t{ std::chrono::system_clock::to_time_t(this_thread_now) };
				return static_cast<unsigned>(another_thread_hashed_id)
					^ static_cast<unsigned>(this_thread_now_time_t % 10'000'000'000L);
			}
		}
	}

	// ------------------------------------------ loguniform  namespace
	namespace loguniform
	{
		// -------------------------------------- loguniform  distribution parameters assertion
		template<std::floating_point T>
		decltype(auto) parameter_assertion(T minval, T maxval)
		{
			// parameter checking (both parameters must be greater than zero, 
			// because, there is no value for negative logarithms)
			if (minval <= 0.0f)
				throw std::runtime_error("ERROR: minimum value parameter in log-uniform distribution function "
					"must be greater than zero (there is no value for zero-negative logarithms)");
			if (maxval <= 0.0f)
				throw std::runtime_error("ERROR: maximum value parameter in log-uniform distribution function "
					"must be greater than zero (there is no value for zero-negative logarithms)");
		}

		// -------------------------------------- loguniform  simulator
		template<std::floating_point T>
		decltype(auto) simulator(T minval, T maxval)
		{
			std::uniform_real_distribution<T> parametrized_loguniform_distribution(minval, maxval);
			return [parametrized_loguniform_distribution](auto& random_number_generator_arg) mutable {
				return exp(parametrized_loguniform_distribution(random_number_generator_arg));
			};
		}

		// -------------------------------------- loguniform  distributor
		template<std::floating_point T>
		decltype(auto) distributor(T minval, T maxval, size_t number_of_simulations_arg, size_t seed_arg) {
			std::vector<T> samples(number_of_simulations_arg, (T)0);
			std::mt19937 rng{};
			rng.seed(seed_arg);
			auto rnd{ simulator(minval, maxval) };
			for (auto& v : samples)
				v = rnd(rng);
			return samples;
		}
	}
}

// entry point
auto main()->int
{
	try
	{
		auto samples{ loguniform::distributor(1.5, 20.06, 1'00, automatic::seeder()) };
		for (const auto& s : samples)
			std::cout << s << std::endl;
		return EXIT_SUCCESS;
	}
	catch (const std::exception& xxx)
	{
		std::cerr << xxx.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "UNCAUGHT EXCEPTION DETECTED" << std::endl;
		return EXIT_FAILURE;
	}
}
