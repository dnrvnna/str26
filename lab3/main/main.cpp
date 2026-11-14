#include <thread>
#include <mutex>
#include <string>
#include <iostream>

std::mutex m;

int coins;
int Bob_coins = 0;
int Tom_coins = 0;
bool leave_last;

void coins_sharing(std::string name, int& their_coins, int& companion_coins) {
	while (true) {
		bool took_coin = false;

		m.lock();
		const int stop_condition = leave_last ? 1 : 0;

		
		if (coins > stop_condition && their_coins <= companion_coins) {
			--coins;
			++their_coins;
			
			took_coin = true;

			std::cout << name << " : " << their_coins << " " << companion_coins << std::endl;
			std::cout << "Осталось монет: " << coins << std::endl;
		}
		
		m.unlock();

		if (coins <= stop_condition) {
			break;
		}

		if (!took_coin) {
			std::this_thread::yield();
		}
	}
	

}

int main() {
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите количество монет: ";
	std::cin >> coins;
	leave_last = coins % 2 == 0 ? false : true;
	std::thread Bob(coins_sharing, "Боб", std::ref(Bob_coins), std::ref(Tom_coins));
	std::thread Tom(coins_sharing, "Том", std::ref(Tom_coins), std::ref(Bob_coins));
	Bob.join();
	Tom.join();
	std::cout << "Боб собрал монет: " << Bob_coins << std::endl;
	std::cout << "Том собрал монет: " << Tom_coins << std::endl;
	return 0;
}